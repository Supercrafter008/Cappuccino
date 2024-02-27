#include "GuiButton.h"

#include "GuiRenderer.h"
#include "GuiFrame.h"
#include <gx2/mem.h>

#include "input/VPADInput.h"

GuiButton::GuiButton(std::wstring text) : GuiElement(){
    m_Text = new GuiText(text);
    m_Text->SetFontSize(24);
    m_Text->m_Parent = this;
    m_Rect = new GuiRect({43,43,43,255}, {34,151,194, 255});
    m_Rect->SetThickness(0.0);
    m_Rect->m_Parent = this;
    m_Rect->SetScale({m_Text->GetTextSize().x + 80, m_Text->GetTextSize().y + 40});
    m_Scale = m_Rect->GetScale();
    SetPos({0,0,0});
}

GuiButton::~GuiButton(){
    if(m_Text) delete m_Text;
    if(m_Rect) delete m_Rect;
}

bool GuiButton::Pressed(){
    glm::vec2 pos = VPAD::GetTouchPos();
    if(pos.x >= m_Pos.x && pos.y >= m_Pos.y && pos.x <= m_Pos.x + m_Scale.x && pos.y <= m_Pos.y + m_Scale.y){
        return true;
    }

    return false;
}

void GuiButton::SetText(std::wstring text){
    m_Text->SetText(text);
    if(m_Text->GetTextSize().x > m_Rect->GetScale().x || m_Text->GetTextSize().y > m_Rect->GetScale().y){
        m_Rect->SetScale({m_Text->GetTextSize().x + 80, m_Text->GetTextSize().y + 40});
    }
}

void GuiButton::SetTextSize(uint32_t textSize){
    m_Text->SetFontSize(textSize);
    if(m_Text->GetTextSize().x > m_Rect->GetScale().x || m_Text->GetTextSize().y > m_Rect->GetScale().y){
        m_Rect->SetScale({m_Text->GetTextSize().x + 80, m_Text->GetTextSize().y + 40});
    }
    m_Text->SetPos({(m_Rect->GetScale().x / 2) - (m_Text->GetTextSize().x / 2), (m_Rect->GetScale().y / 2) - (m_Text->GetTextSize().y / 2), 0.0f});
}


void GuiButton::Draw(bool isDrc){
    m_Rect->Draw(isDrc);
    m_Text->Draw(isDrc);
}

void GuiButton::SetPos(glm::vec3 pos){
    m_Pos = pos;
    m_Rect->SetPos({0,0,0});
    m_Text->SetPos({(m_Rect->GetScale().x / 2) - (m_Text->GetTextSize().x / 2), (m_Rect->GetScale().y / 2) - (m_Text->GetTextSize().y / 2), 0.0f});
}

void GuiButton::SetScale(glm::vec2 scale){
    m_Scale = scale;
    m_Rect->SetScale(scale);
    m_Text->SetPos({(m_Rect->GetScale().x / 2) - (m_Text->GetTextSize().x / 2), (m_Rect->GetScale().y / 2) - (m_Text->GetTextSize().y / 2), 0.0f});
}


