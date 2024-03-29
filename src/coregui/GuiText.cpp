#include "GuiText.h"

#include "GuiRenderer.h"
#include <coreinit/memory.h>


static Font* defaultFont = nullptr;

GuiText::GuiText(std::string text) : GuiElement(){
    if(!defaultFont){
        defaultFont = new Font(L" 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ;,.:-_!?\"+*%&/()=®\uE000\uE001\uE002\uE003\uE004\uE005\uE078\uE079\uE080\uE081\uE082\uE083\uE084\uE085\uE086\uE087\uE088\uE089");
    }
    m_DefaultFont = true;
    m_Font = defaultFont;
    SetText(text);
}

GuiText::GuiText(std::string text, Font* font) : GuiElement(){
	m_Font = font;
    SetText(text);
}


GuiText::GuiText(std::wstring text) : GuiElement(){
    if(!defaultFont){
        defaultFont = new Font(L" 0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ;,.:-_!?\"+*%&/()=®\uE000\uE001\uE002\uE003\uE004\uE005\uE078\uE079\uE080\uE081\uE082\uE083\uE084\uE085\uE086\uE087\uE088\uE089");
    }
    m_DefaultFont = true;
    m_Font = defaultFont;
    SetText(text);
}


GuiText::GuiText(std::wstring text, Font* font) : GuiElement(){
	m_Font = font;
    SetText(text);
}

GuiText::~GuiText(){
    if(m_PosBuffer) delete m_PosBuffer;
    if(m_TexCoordsBuffer) delete m_TexCoordsBuffer;
    if(!m_DefaultFont) delete m_Font;
}

void GuiText::SetText(std::wstring text){
    if(m_PosBuffer) delete m_PosBuffer;
    if(m_TexCoordsBuffer) delete m_TexCoordsBuffer;
    m_PosBuffer = new Buffer(text.size() * 4, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_TexCoordsBuffer = new Buffer(text.size() * 4, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_Font->GetTextDrawInfo(text, m_PosBuffer, m_TexCoordsBuffer);
    m_Text = text;
}

void GuiText::SetText(std::string text){
    size_t len        = text.size() + 1;
    wchar_t *strWChar = (wchar_t*)malloc(sizeof(wchar_t) * len);
    size_t bt = mbstowcs(strWChar, text.c_str(), len);
    if (bt < --len) {
        strWChar[bt] = 0;
    }

    SetText(std::wstring(strWChar));
    //delete strWChar;
}


void GuiText::SetFontSize(uint32_t textSize){
    //float tvWidthScale = 1.0f / (float)WHBGfxGetTVColourBuffer()->surface.width;
    //float tvHeightScale = 1.0f / (float)WHBGfxGetTVColourBuffer()->surface.height;

    m_FontSize = textSize / 72.0f;
}

void GuiText::Draw(bool isDrc){
    GuiRenderer* renderer = GuiRenderer::Get();
    renderer->Begin(m_PosBuffer, m_TexCoordsBuffer);
    renderer->BindShader(SHADER_TEXT);
    renderer->BindBuffers();

    renderer->SetOffset(m_Pos);
    renderer->SetScale({m_FontSize,m_FontSize});
    renderer->SetColor(m_Color);

    m_Font->Bind();
    renderer->Draw();
}