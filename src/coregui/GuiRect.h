#pragma once

#include <wut_types.h>

#include <glm/glm.hpp>
#include <gx2/texture.h>
#include <gx2/sampler.h>

#include "gfx/Texture.h"
#include "GuiElement.h"
#include "gfx/Buffer.h"

class GuiRect : public GuiElement{
public:
    GuiRect(glm::vec4 fillColor, glm::vec4 outlineColor = glm::vec4{0,0,0,0});
    ~GuiRect();

    void SetScale(glm::vec2 scale) override;
    void Draw(bool isDrc) override;

    void SetFillColor(glm::vec4 fillColor);
    void SetOutlineColor(glm::vec4 OutlineColor);
    void SetRadius(float radius);
    void SetThickness(float thickness);

private:
    glm::vec2 m_DataScale;
    glm::vec4 m_FillColor;
    glm::vec4 m_OutlineColor;
    float m_Radius = 0.1f;
    float m_Thickness = 0.005f;

    Texture* m_Texture = nullptr;
    Buffer* m_PosBuffer = nullptr;
    Buffer* m_TexCoordsBuffer = nullptr;
};