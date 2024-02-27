#pragma once

#include <wut_types.h>

#include <glm/glm.hpp>
#include <gx2/texture.h>
#include <gx2/sampler.h>
#include <string>


struct TextureConfig{
    GX2SurfaceFormat format;
    GX2TileMode tileMode = GX2_TILE_MODE_LINEAR_ALIGNED;
    GX2SurfaceUse use = GX2_SURFACE_USE_TEXTURE;
    GX2TexXYFilterMode filterMode = GX2_TEX_XY_FILTER_MODE_POINT;
    GX2TexClampMode clampMode = GX2_TEX_CLAMP_MODE_CLAMP;
    glm::ivec2 size;
};

class Texture{
public:
    Texture(TextureConfig config);
    ~Texture();

    static Texture* LoadFromFile(std::string filename);
    static Texture* LoadFromMemory(uint8_t* data, TextureConfig config);
    
    void SetPixel(glm::ivec2 loc, uint32_t pixel);
    void Flush();

    glm::ivec2 GetTextureSize() { return m_Size; };
    GX2Surface* GetTextureSurface() { return &m_Texture->surface; };
    void Bind();

private:
    int8_t m_BytesPerPixel;

    glm::ivec2 m_Size = {0,0};
    GX2Texture* m_Texture;
    GX2Sampler* m_Sampler;
};