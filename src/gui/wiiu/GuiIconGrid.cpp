#include "GuiIconGrid.h"

#include <gx2/mem.h>
#include <string>

#include "input/VPADInput.h"

#include "utils/TitleUtils.h"
#include "utils/ODM.h"

GuiIconGrid::GuiIconGrid() : GuiElement(){
    
}

GuiIconGrid::~GuiIconGrid(){

}


void GuiIconGrid::SetTitle(MCPTitleListType* title, uint8_t index){
    if(index > 16) return;
    if(std::string(title->indexedDevice).find("odd") != std::string::npos){
        m_TitleIcons[index] = GuiDiscIcon();
    }else{
        m_TitleIcons[index] = GuiTitleIcon();
    }
    m_TitleIcons[index].SetTitle(title);
    m_TitleIcons[index].SetPos({})
}

void GuiIconGrid::Update(){
    for(GuiTitleIcon icon : m_TitleIcons){
        icon.Update();
    }
}
