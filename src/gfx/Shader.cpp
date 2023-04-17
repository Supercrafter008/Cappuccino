#include "Shader.h"

#include <gfd.h>
#include "resources/Resources.h"
#include <gx2/mem.h>

Shader::Shader(const char* filename){
    WHBGfxLoadGFDShaderGroup(&m_Shader, 0, Resources::GetFile(filename));
    WHBGfxInitFetchShader(&m_Shader);
}

Shader::~Shader(){
    WHBGfxFreeShaderGroup(&m_Shader);
}

void Shader::AddAttrib(const char* name, uint32_t buffer, GX2AttribFormat format){
    WHBGfxInitShaderAttribute(&m_Shader, name, buffer, 0, format);
}

void Shader::Bind(){
    GX2SetFetchShader(&m_Shader.fetchShader);
    GX2SetVertexShader(m_Shader.vertexShader);
    GX2SetPixelShader(m_Shader.pixelShader);
}

void Shader::SetVertexUniform(std::string name, uint32_t count, const void* data){
    for(uint32_t i = 0; i < m_Shader.vertexShader->uniformVarCount; i++){
        if(name.compare(m_Shader.vertexShader->uniformVars[i].name) == 0){
            GX2SetVertexUniformReg(m_Shader.vertexShader->uniformVars[i].offset, count, data);
            break;
        }
    }
}

void Shader::SetPixelUniform(std::string name, uint32_t count, const void* data){
    for(uint32_t i = 0; i < m_Shader.pixelShader->uniformVarCount; i++){
        if(name.compare(m_Shader.pixelShader->uniformVars[i].name) == 0){
            GX2SetPixelUniformReg(m_Shader.pixelShader->uniformVars[i].offset, count, data);
            break;
        }
    }
    
}

void Shader::Init(){
    WHBGfxInitFetchShader(&m_Shader);
}
