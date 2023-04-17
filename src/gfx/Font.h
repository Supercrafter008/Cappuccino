#pragma once

#include <wut_types.h>

#include <glm/glm.hpp>
#include <gx2/texture.h>
#include <gx2/sampler.h>
#include "Texture.h"
#include <string>
#include <map>
#include <ft2build.h>
#include "Buffer.h"
#include FT_FREETYPE_H

struct GlyphInfo {
	glm::vec2 texPos, size, offset;
	uint8_t advance;
};

class Font{
public:
    Font(std::wstring chars);
    Font(const char* filename, std::wstring chars);
    ~Font();

    void GetTextDrawInfo(std::wstring text, Buffer* posBuffer, Buffer* texCoordsBuffer);

    void Bind();
    glm::ivec2 GetTextureSize() { return m_FontAtlas->GetTextureSize(); };

    glm::vec2 GetTextSize(std::wstring text, float fontSize);


private:
    void GenTextureAtlas(uint8_t* data, uint32_t size, std::wstring chars);
    uint16_t CalculateTextureAtlasSize(std::wstring chars);
    std::map<wchar_t, uint16_t> m_CharcodeMap;

    GlyphInfo* m_GlyphInfos;
    Texture* m_FontAtlas;

};