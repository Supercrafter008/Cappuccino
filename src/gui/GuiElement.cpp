#include "GuiElement.h"
#include "GuiFrame.h"


GuiElement::GuiElement(){
    m_Pos = {0.0f, 0.0f, 0.0f};
    m_Scale = {1.0f, 1.0f};
    m_Color = {255.0f, 255.0f, 255.0f, 255.0f};

}


void GuiElement::SetPos(glm::vec3 pos){
    if(m_Parent != nullptr){
        m_Pos = pos + m_Parent->m_Pos;
        return;
    }
    m_Pos = pos;
}

void GuiElement::SetScale(glm::vec2 scale){
    m_Scale = scale;
}

void GuiElement::SetColor(glm::vec4 color){
    m_Color = color;
}
