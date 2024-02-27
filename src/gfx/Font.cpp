#include "Font.h"

#include "resources/Resources.h"
#include <coreinit/memory.h>
#include <string.h>

#define FONT_SIZE 72

static FT_Library s_Ft;

Font::Font(std::wstring chars){
    void* data;
    uint32_t size;
    OSGetSharedData(OS_SHAREDDATATYPE_FONT_STANDARD, 0, &data, &size);
    GenTextureAtlas((uint8_t*)data, size, chars);
    //free(data);
}

Font::Font(const char* path, std::wstring chars){
    const uint8_t* data = Resources::GetFile(path);
    GenTextureAtlas((uint8_t*)data, Resources::GetFileSize(path), chars);
}

Font::~Font(){
    delete[] m_GlyphInfos;
    delete m_FontAtlas;

}

void Font::GenTextureAtlas(uint8_t* data, uint32_t size, std::wstring chars){
    FT_Init_FreeType(&s_Ft);
    FT_Face face;

	FT_New_Memory_Face(s_Ft, (FT_Byte*)data, size, 0, &face);
    FT_Set_Pixel_Sizes(face, 0, FONT_SIZE);
    FT_Select_Charmap(face, FT_ENCODING_UNICODE);

	uint16_t textureSize = CalculateTextureAtlasSize(chars);
    m_GlyphInfos = new GlyphInfo[chars.size()];

    TextureConfig config;
    config.format = GX2_SURFACE_FORMAT_UNORM_R8;
    config.size = {textureSize, textureSize};
    config.filterMode = GX2_TEX_XY_FILTER_MODE_LINEAR;

    m_FontAtlas = new Texture(config);

	uint16_t pen_x = 0, pen_y = 0;
    uint16_t i = 0;
    uint16_t rowHeight = 0;
    for(wchar_t charcode : chars){
        FT_Load_Char(face, charcode, FT_LOAD_DEFAULT);
        FT_Render_Glyph(face->glyph, FT_RENDER_MODE_SDF);
        FT_Bitmap* bmp = &face->glyph->bitmap;
        if(bmp->rows > rowHeight){
            rowHeight = bmp->rows;
        }

		if(pen_x + bmp->width >= textureSize){
			pen_x = 0;
			pen_y += rowHeight;
		}

		for(uint16_t row = 0; row < bmp->rows; ++row){
			for(uint16_t col = 0; col < bmp->width; ++col){
                m_FontAtlas->SetPixel({pen_x + col, pen_y + row}, bmp->buffer[row * bmp->pitch + col]);
			}
		}
        m_CharcodeMap[charcode] = i;
        m_GlyphInfos[i].texPos = {pen_x, pen_y};
		m_GlyphInfos[i].size = {bmp->width, bmp->rows};

        m_GlyphInfos[i].offset = {face->glyph->bitmap_left, face->glyph->bitmap_top};
		m_GlyphInfos[i].advance = face->glyph->advance.x >> 6;
        pen_x += bmp->width + 1;

        i++;
    }

	FT_Done_Face(face);
    FT_Done_FreeType(s_Ft);

    m_FontAtlas->Flush();

}

void Font::GetTextDrawInfo(std::wstring text, Buffer* posBuffer, Buffer* texCoordsBuffer){

    float* vertexPositions = new float[text.size() * 8];
    float* texturePositions = new float[text.size() * 8];
    int i = 0;
    float xPos = 0, yPos = 0;
    for(wchar_t charcode : text){
        float x = xPos + (m_GlyphInfos[m_CharcodeMap[charcode]].offset.x) * 2;
        float y = yPos + (FONT_SIZE - m_GlyphInfos[m_CharcodeMap[charcode]].offset.y) * 2;
        //veretx
        vertexPositions[i] = x + (m_GlyphInfos[m_CharcodeMap[charcode]].size.x * 2);
        vertexPositions[i + 1] = y + (m_GlyphInfos[m_CharcodeMap[charcode]].size.y * 2);

        vertexPositions[i + 2] = x + (m_GlyphInfos[m_CharcodeMap[charcode]].size.x * 2);
        vertexPositions[i + 3] = y;

        vertexPositions[i + 4] = x;
        vertexPositions[i + 5] = y;

        vertexPositions[i + 6] = x;
        vertexPositions[i + 7] = y + (m_GlyphInfos[m_CharcodeMap[charcode]].size.y * 2);
        

        xPos += (m_GlyphInfos[m_CharcodeMap[charcode]].advance * 2);

        //texture
        texturePositions[i] = (m_GlyphInfos[m_CharcodeMap[charcode]].texPos.x + m_GlyphInfos[m_CharcodeMap[charcode]].size.x) / m_FontAtlas->GetTextureSize().x;
        texturePositions[i + 1] =  (m_GlyphInfos[m_CharcodeMap[charcode]].texPos.y + m_GlyphInfos[m_CharcodeMap[charcode]].size.y) / m_FontAtlas->GetTextureSize().y;

        texturePositions[i + 2] = (m_GlyphInfos[m_CharcodeMap[charcode]].texPos.x + m_GlyphInfos[m_CharcodeMap[charcode]].size.x) / m_FontAtlas->GetTextureSize().x;
        texturePositions[i + 3] = (m_GlyphInfos[m_CharcodeMap[charcode]].texPos.y) / m_FontAtlas->GetTextureSize().x;

        texturePositions[i + 4] = (m_GlyphInfos[m_CharcodeMap[charcode]].texPos.x) / m_FontAtlas->GetTextureSize().x;
        texturePositions[i + 5] = (m_GlyphInfos[m_CharcodeMap[charcode]].texPos.y) / m_FontAtlas->GetTextureSize().x;

        texturePositions[i + 6] = (m_GlyphInfos[m_CharcodeMap[charcode]].texPos.x) / m_FontAtlas->GetTextureSize().x;
        texturePositions[i + 7] = (m_GlyphInfos[m_CharcodeMap[charcode]].texPos.y + m_GlyphInfos[m_CharcodeMap[charcode]].size.y) / m_FontAtlas->GetTextureSize().x;



        i+=8;
    }

    posBuffer->SetData(vertexPositions,text.size() * 4);
    texCoordsBuffer->SetData(texturePositions,text.size() * 4);
    delete[] vertexPositions;
    delete[] texturePositions;
}

glm::vec2 Font::GetTextSize(std::wstring text, float fontSize){
    glm::vec2 size(0);
    int i = 0;
    wchar_t lastCode;
    for(wchar_t charcode : text){
        if(i == 0){
            size.x += m_GlyphInfos[m_CharcodeMap[charcode]].offset.x;
        }
        if(size.y < (FONT_SIZE - m_GlyphInfos[m_CharcodeMap[charcode]].offset.y) + m_GlyphInfos[m_CharcodeMap[charcode]].size.y){
            size.y = (FONT_SIZE - m_GlyphInfos[m_CharcodeMap[charcode]].offset.y) + m_GlyphInfos[m_CharcodeMap[charcode]].size.y;
        }
        size.x += m_GlyphInfos[m_CharcodeMap[charcode]].advance;
        lastCode = charcode;
    }
    size.x += m_GlyphInfos[m_CharcodeMap[lastCode]].offset.x + m_GlyphInfos[m_CharcodeMap[lastCode]].size.x;

    return fontSize * size;
}

uint16_t Font::CalculateTextureAtlasSize(std::wstring chars){
    //aprox
    return (uint16_t)ceil(sqrt(chars.length()) * ((double)FONT_SIZE + 6));
}

void Font::Bind(){
    m_FontAtlas->Bind();
}