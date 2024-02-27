#include "GuiProgressBar.h"

#include "GuiRenderer.h"
#include "GuiFrame.h"
#include <gx2/mem.h>

#include "input/VPADInput.h"

GuiProgressBar::GuiProgressBar() : GuiElement(){
    m_FillRect = new GuiRect({43,43,43,255}, {43,43,43,255});
    m_FillRect->SetThickness(0.0);
    m_FillRect->m_Parent = this;
    m_Rect = new GuiRect({98,241,180,255}, {98,241,180,255});
    m_Rect->SetThickness(0.0);
    m_Rect->SetRadius(0.0);
    m_Rect->m_Parent = this;
    m_Scale = m_FillRect->GetScale();

    SetScale({400, 60});
    SetPos({0,0,0});
}

GuiProgressBar::~GuiProgressBar(){
    if(m_FillRect) delete m_FillRect;
    if(m_Rect) delete m_Rect;
}

void GuiProgressBar::SetValue(uint32_t val){
    m_Val = val;
}

void GuiProgressBar::SetMaxValue(uint32_t val){
    m_MaxVal = val;
}

void GuiProgressBar::SetOutlineThickness(uint32_t val){
    m_Outline = val;
    SetScale(m_Scale);
    SetPos(m_Pos);
}


void GuiProgressBar::Draw(bool isDrc){
    m_Rect->SetScale({(m_Scale.x - (m_Outline * 2)) * (m_Val / (float)m_MaxVal), m_Rect->GetScale().y});
    m_Rect->Draw(isDrc);
    m_FillRect->Draw(isDrc);
}

void GuiProgressBar::SetPos(glm::vec3 pos){
    m_Pos = pos;
    m_Rect->SetPos({m_Outline,m_Outline,0});
    m_FillRect->SetPos({0,0,0});
}

void GuiProgressBar::SetScale(glm::vec2 scale){
    m_Scale = scale;
    m_Rect->SetScale({scale.x - (m_Outline * 2), scale.y - (m_Outline * 2)});
    m_FillRect->SetScale(scale);
}


