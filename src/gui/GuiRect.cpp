#include "GuiRect.h"

#include "GuiRenderer.h"
#include "GuiFrame.h"
#include <gx2/mem.h>
#include <gx2/registers.h>
#include <glm/gtc/type_ptr.hpp>


GuiRect::GuiRect(glm::vec4 fillColor, glm::vec4 outlineColor) : GuiElement(){
    m_FillColor = fillColor;
    m_OutlineColor = outlineColor;

    m_PosBuffer = new Buffer(4, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_TexCoordsBuffer = new Buffer(4, GX2_ATTRIB_FORMAT_FLOAT_32_32);

    float defaultPos[] = {
        1.0f, 1.0f, 
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0f,
    };

    float defaultTexCoords[] = {
        1.0f, 1.0,
        1.0f, 0.0f,
        0.0f, 0.0f,
        0.0f, 1.0,
    };

    m_PosBuffer->SetData(defaultPos, 4);
    m_TexCoordsBuffer->SetData(defaultTexCoords, 4);

}

GuiRect::~GuiRect(){
    if(m_PosBuffer) delete m_PosBuffer;
    if(m_TexCoordsBuffer) delete m_TexCoordsBuffer;
}

void GuiRect::SetFillColor(glm::vec4 color){
    m_FillColor = color;
}

void GuiRect::SetOutlineColor(glm::vec4 color){
    m_OutlineColor = color;
}

void GuiRect::SetRadius(float radius){
    m_Radius = radius;
}

void GuiRect::SetThickness(float thickness){
    m_Thickness = thickness;
}

void GuiRect::SetScale(glm::vec2 scale){
    m_Scale = scale;
    m_DataScale.x = m_Scale.x / m_Scale.y;
    if(m_DataScale.x < 1.0f){
        m_DataScale.x = 1.0f;
        m_DataScale.y = m_Scale.y / m_Scale.x;
    }else{
        m_DataScale.y = 1.0f;
    }

    if(m_TexCoordsBuffer) delete m_TexCoordsBuffer;

    float texCoords[] = {
        m_DataScale.x, m_DataScale.y,
        m_DataScale.x, 0.0f,
        0.0f, 0.0f,
        0.0f, m_DataScale.y,
    };
    m_TexCoordsBuffer = new Buffer(4, GX2_ATTRIB_FORMAT_FLOAT_32_32);
    m_TexCoordsBuffer->SetData(texCoords, 4);
}

void GuiRect::Draw(bool isDrc){
    GuiRenderer* renderer = GuiRenderer::Get();
    renderer->Begin(m_PosBuffer, m_TexCoordsBuffer);
    renderer->BindShader(SHADER_COLOR);
    renderer->BindBuffers();
    
    renderer->SetOffset(m_Pos, isDrc);
    renderer->SetScale(m_Scale, isDrc);
    renderer->SetColor(m_FillColor);
    renderer->SetOutlineColor(m_OutlineColor);
    renderer->SetColorData(m_DataScale, m_Radius, m_Thickness);

    renderer->Draw();
}