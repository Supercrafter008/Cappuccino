#include "Texture.h"

#include <gx2/surface.h>
#include <gx2/shaders.h>
#include <gx2/mem.h>
#include <coreinit/launch.h>
#include <malloc.h>
#include <coreinit/memdefaultheap.h>
#include <gd.h>


#include "resources/Resources.h"

Texture::Texture(TextureConfig config){
    m_Texture = new GX2Texture;
    memset(m_Texture, 0, sizeof(GX2Texture));
    m_Size = config.size;
    m_Texture->surface.format = config.format;
    m_Texture->surface.width = config.size.x;
    m_Texture->surface.height = config.size.y;
    m_Texture->surface.tileMode = config.tileMode;
    m_Texture->surface.use = config.use;
    m_Texture->surface.dim = GX2_SURFACE_DIM_TEXTURE_2D;
    m_Texture->surface.depth = 1;
    m_Texture->viewNumSlices = 1;
    switch(config.format){
        case GX2_SURFACE_FORMAT_UNORM_R8:
        case GX2_SURFACE_FORMAT_UINT_R8:
        case GX2_SURFACE_FORMAT_SNORM_R8:
        case GX2_SURFACE_FORMAT_SINT_R8:
            m_BytesPerPixel = 1;
            m_Texture->compMap = 0x00;
            break;
        case GX2_SURFACE_FORMAT_UNORM_R8_G8:
        case GX2_SURFACE_FORMAT_UINT_R8_G8:
        case GX2_SURFACE_FORMAT_SNORM_R8_G8:
        case GX2_SURFACE_FORMAT_SINT_R8_G8:
            m_BytesPerPixel = 2;
            m_Texture->compMap = 0x0001;
            break;
        case GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8:
        case GX2_SURFACE_FORMAT_UINT_R8_G8_B8_A8:
        case GX2_SURFACE_FORMAT_SNORM_R8_G8_B8_A8:
        case GX2_SURFACE_FORMAT_SINT_R8_G8_B8_A8:
            m_BytesPerPixel = 4;
            m_Texture->compMap = 0x00010203;
            break;
        default:
            m_BytesPerPixel = 0;
            m_Texture->compMap = 0x0;
    }   
    GX2CalcSurfaceSizeAndAlignment(&m_Texture->surface);
    GX2InitTextureRegs(m_Texture);

    m_Texture->surface.image = memalign( m_Texture->surface.alignment, m_Texture->surface.imageSize);
    m_Sampler = new GX2Sampler;
    GX2InitSampler(m_Sampler, config.clampMode, config.filterMode);
}


Texture::~Texture(){
    if(m_Texture != nullptr){
        if(m_Texture->surface.image){
            free(m_Texture->surface.image);
        }
        delete m_Texture;
    }
    if(m_Sampler != nullptr){
        delete m_Sampler;
    }
}

Texture* Texture::LoadFromFile(const char* path){
    const uint8_t* file = Resources::GetFile(path);
    if(file == nullptr) return nullptr;
    uint32_t filesize = Resources::GetFileSize(path);
    gdImagePtr img;

    if (file[0] == 'B' && file[1] == 'M') {
        img = gdImageCreateFromBmpPtr(filesize, (uint8_t *) file);
    } else if (file[0] == 0x89 && file[1] == 'P' && file[2] == 'N' && file[3] == 'G') {
        img = gdImageCreateFromPngPtr(filesize, (uint8_t *) file);
    }
    else if (file[0] == 0x00) {
        img = gdImageCreateFromTgaPtr(filesize, (uint8_t *) file);
    }

    if (img == 0) {
        return nullptr;
    }

    TextureConfig config;
    config.size = {gdImageSX(img), gdImageSY(img)};
    config.format = GX2_SURFACE_FORMAT_UNORM_R8_G8_B8_A8;
    Texture* tex = new Texture(config);
    
    GX2Surface* surface = tex->GetTextureSurface();


    for (uint32_t y = 0; y < surface->height; ++y) {
        for (uint32_t x = 0; x < surface->width; ++x) {
            uint32_t pixel = gdImageGetPixel(img, x, y);

            uint8_t a = 254 - 2 * ((uint8_t) gdImageAlpha(img, pixel));
            if (a == 254) { a++; }

            uint8_t r = gdImageRed(img, pixel);
            uint8_t g = gdImageGreen(img, pixel);
            uint8_t b = gdImageBlue(img, pixel);

            ((uint32_t*)surface->image)[y * surface->pitch + x] = (r << 24) | (g << 16) | (b << 8) | (a);
        }
    }

    tex->Flush();

    gdImageDestroy(img);

    free((void*)file);

    return tex;
}

Texture* Texture::LoadFromMemory(uint8_t* data, TextureConfig config){
    Texture* tex = new Texture(config);
    
    GX2Surface* surface = tex->GetTextureSurface();

    for (uint32_t y = 0; y < config.size.y; y++) {
        for (uint32_t x = 0; x < config.size.x; x++) {
            for(uint16_t i = 0; i < tex->m_BytesPerPixel; i++){
                ((uint8_t*)surface->image)[y * surface->pitch + x + i] = data[((uint32_t)(y * config.size.x + x + i))];
            }
        }
    }

    tex->Flush();

    return tex;
}

void Texture::SetPixel(glm::ivec2 loc, uint32_t pixel){
    switch(m_BytesPerPixel){
        case 1:
            ((uint8_t*)m_Texture->surface.image)[loc.y * m_Texture->surface.pitch + loc.x] = (uint8_t)pixel;
            break;
        case 2:
            ((uint16_t*)m_Texture->surface.image)[loc.y * m_Texture->surface.pitch + loc.x] = (uint16_t)pixel;
            break;
        case 4:
            ((uint32_t*)m_Texture->surface.image)[loc.y * m_Texture->surface.pitch + loc.x] = (uint32_t)pixel;
    }
}

void Texture::Flush(){
    GX2Invalidate(GX2_INVALIDATE_MODE_CPU_TEXTURE, m_Texture->surface.image, m_Texture->surface.imageSize);
}

void Texture::Bind(){
    if(m_Texture != nullptr){
        GX2SetPixelTexture(m_Texture, 0);
        GX2SetPixelSampler(m_Sampler, 0);
    }
}

