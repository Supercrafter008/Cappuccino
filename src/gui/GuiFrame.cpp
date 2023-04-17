#include "GuiFrame.h"


#include <algorithm>

GuiFrame::GuiFrame() : GuiElement(){
    m_Parent = nullptr;
}

void GuiFrame::AddElement(GuiElement* element){
    element->m_Parent = this;
    m_Elements.push_back(element);
}

void GuiFrame::RemoveElement(GuiElement* element){
    auto i = std::find(m_Elements.begin(), m_Elements.end(), element);
    if(i != m_Elements.end()){
        m_Elements.erase(i);
    }
}


void GuiFrame::ClearElements(){
    for(GuiElement* element : m_Elements){
        delete element;
    }
    m_Elements.clear();
}

void GuiFrame::Draw(bool isDrc){
    for(GuiElement* element : m_Elements){
        element->Draw(isDrc);
    }
}