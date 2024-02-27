#include "GuiRenderer.h"

#include <gx2/draw.h>
#include <gx2/state.h>
#include <gx2/event.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


GuiRenderer* GuiRenderer::m_Renderer = nullptr;

GuiRenderer* GuiRenderer::Get(){
    if(m_Renderer == nullptr){
        m_Renderer = new GuiRenderer();
    }
    return m_Renderer;
}

GuiRenderer::GuiRenderer(){

    m_ColorShader =  new Shader("ColorShader.gsh");
    m_ColorShader->AddAttrib("aPosition", 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_ColorShader->AddAttrib("aTexPos", 1, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_ColorShader->Init();

    m_TextureShader =  new Shader("TextureShader.gsh");
    m_TextureShader->AddAttrib("aPosition", 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_TextureShader->AddAttrib("aTexPos", 1, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_TextureShader->Init();


    m_TextShader =  new Shader("TextShader.gsh");
    m_TextShader->AddAttrib("aPosition", 0, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_TextShader->AddAttrib("aTexPos", 1, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_TextShader->Init();

    
    m_PositonBuffer = new Buffer(4, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_TexCoordsBuffer = new Buffer(4, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_TVWidthScale = 1.0f / (float)WHBGfxGetTVColourBuffer()->surface.width;
    m_TVHeightScale = 1.0f / (float)WHBGfxGetTVColourBuffer()->surface.height;

}

GuiRenderer::~GuiRenderer(){
    delete m_ColorShader;
    delete m_TextureShader;
    delete m_TextShader;

    delete m_PositonBuffer;
    delete m_TexCoordsBuffer;
}

void GuiRenderer::Begin(Buffer* posBuffer, Buffer* texPosBuffer){
    customBuffers = true;
    m_CustomPositonBuffer = posBuffer;
    m_CustomTexCoordsBuffer = texPosBuffer;
}

void GuiRenderer::BeginRect(){
    customBuffers = false;
    
    float defaultPos[] = {
        2.0f, 2.0f, 
        2.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 2.0f,
    };

    float defaultTexCoords[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
    };

    m_PositonBuffer->SetData(defaultPos, 4);
    m_TexCoordsBuffer->SetData(defaultTexCoords, 4);
}



void GuiRenderer::SetOffset(const glm::vec3 &offset){
    glm::vec3 vec;
    vec.x = (((offset.x + 1) * m_TVWidthScale) * 2) - 1;
    vec.y = (((offset.y + 1) * m_TVHeightScale) * -2) + 1;
    vec.z = offset.z;
    m_CurrentShader->SetVertexUniform("uOffset", 4, glm::value_ptr(vec));
}

void GuiRenderer::SetScale(const glm::vec2 &scale){
    glm::vec2 vec;
    vec.x = scale.x * m_TVWidthScale;
    vec.y = scale.y * m_TVHeightScale * -1;
    m_CurrentShader->SetVertexUniform("uScale", 4, glm::value_ptr(vec));
}

void GuiRenderer::SetColor(const glm::vec4 &vec){
    glm::vec4 col = vec / 255.0f;
    m_CurrentShader->SetPixelUniform("uColor", 4, glm::value_ptr(col));
}

void GuiRenderer::SetOutlineColor(const glm::vec4 &vec){
    glm::vec4 col = vec / 255.0f;
    m_CurrentShader->SetPixelUniform("uOutlineColor", 4, glm::value_ptr(col));
}


void GuiRenderer::SetColorData(glm::vec2 size, float radius, float thickness){
    glm::vec4 data;
    data.x = size.x;
    data.y = size.y;
    data.z = radius;
    data.w = thickness;
    m_CurrentShader->SetPixelUniform("uData", 4, glm::value_ptr(data));
}


void GuiRenderer::BindBuffers(){

    if(customBuffers){
        m_CustomPositonBuffer->Bind(0);
        m_CustomTexCoordsBuffer->Bind(1);
        return;
    }
    m_PositonBuffer->Bind(0);
    m_TexCoordsBuffer->Bind(1);
}

void GuiRenderer::BindShader(ShaderType type){
    switch(type){
        case SHADER_COLOR:
            m_ColorShader->Bind();
            m_CurrentShader = m_ColorShader;
            break;
        case SHADER_TEXTURE:
            m_TextureShader->Bind();
            m_CurrentShader = m_TextureShader;
            break;
        case SHADER_TEXT:
            m_TextShader->Bind();
            m_CurrentShader = m_TextShader;
            break;

    }
}

void GuiRenderer::Draw(GX2PrimitiveMode primitiveMode){
    if(customBuffers){
        GX2DrawEx(primitiveMode, m_CustomPositonBuffer->Size(), 0, 1);
        return;
    }

    GX2DrawEx(primitiveMode, 4, 0, 1);
}