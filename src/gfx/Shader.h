#pragma once

#include <wut_types.h>
#include <whb/gfx.h>
#include "Buffer.h"

#include <vector>
#include <string>

struct UniformLoc{
    std::string name;
    uint32_t index;
};

class Shader{
    public:
    Shader(const char* path);
    ~Shader();

    void AddAttrib(const char* name, uint32_t bufferIndex, GX2AttribFormat format);

    void Bind();

    void SetVertexUniform(std::string name, uint32_t count, const void* data);
    void SetPixelUniform(std::string name, uint32_t count, const void* data);


    void Init();

    private:

    std::vector<UniformLoc> m_UniformCache;

    WHBGfxShaderGroup m_Shader;   
};