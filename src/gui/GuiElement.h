#pragma once

#include <glm/glm.hpp>

class GuiFrame;

class GuiElement{
    public:
    GuiElement();
    virtual void Draw(bool isDrc) {};

    virtual void SetPos(glm::vec3 pos);
    virtual void SetScale(glm::vec2 scale);
    virtual void SetColor(glm::vec4 color);

    glm::vec3 GetPos() { return m_Pos; };
    glm::vec2 GetScale() { return m_Scale; };
    glm::vec4  GetColor() { return m_Color; };

    GuiElement* m_Parent = nullptr;

    protected:

    glm::vec3 m_Pos;
    glm::vec2 m_Scale;
    glm::vec4 m_Color;

};