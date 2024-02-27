#include "GuiTitleIcon.h"

#include <gx2/mem.h>
#include <string>
#include <nn/acp.h>

#include "screen/ScreenManager.h"
#include "screen/UpdateScreen.h"

#include "input/VPADInput.h"

#include "utils/TitleUtils.h"



GuiTitleIcon::GuiTitleIcon() : GuiElement(){
    m_GameIcon = new GuiImage(nullptr);
    m_GameIcon->m_Parent = this;
    m_Background = new GuiRect({43,43,43,255});
    m_Background->m_Parent = this;
    m_Background->SetScale({m_GameIcon->GetScale().x + 20, m_GameIcon->GetScale().y + 20});
    m_Scale = m_Background->GetScale();
    SetPos({0,0,0});
}

GuiTitleIcon::~GuiTitleIcon(){
    if(m_GameIcon) delete m_GameIcon;
    if(m_GameTex) delete m_GameTex;
    if(m_Background) delete m_Background;
    if(m_TitleListType) delete m_TitleListType;
}

void GuiTitleIcon::SetTitle(MCPTitleListType* title){
    if(title == nullptr){
        if(m_GameTex) {
            delete m_GameTex;
            m_GameTex = nullptr;
        }
        
        if(m_TitleListType) delete m_TitleListType;
        m_GameIcon->SetTexture(nullptr);
        m_TitleListType = nullptr;
        return;
    }
    if(m_TitleListType) delete m_TitleListType;
    m_TitleListType = title;
}

void GuiTitleIcon::SetTexture(Texture* tex){
    m_GameIcon->SetTexture(tex);
}

bool GuiTitleIcon::Pressed(){
    if(m_HoldTime == 0 && m_LastFrameHoldTime > 5){
        return true;
    }else{
        return false;
    }
}

bool GuiTitleIcon::Down(){
    if(m_HoldTime != 0){
        return true;
    }

    return false;
}

uint32_t GuiTitleIcon::HoldTime(){
    return m_HoldTime;
}

void GuiTitleIcon::Update(){
    glm::vec2 pos = VPAD::GetTouchPos();
    m_LastFrameHoldTime = 0;
    if(pos.x >= m_Pos.x && pos.y >= m_Pos.y && pos.x <= m_Pos.x + m_Scale.x && pos.y <= m_Pos.y + m_Scale.y){
        m_HoldTime++;
    }else{
        m_LastFrameHoldTime = m_HoldTime;
        m_HoldTime = 0;
    }
    if(!IsEmpty()){
        
        if(m_GameTex == nullptr){
            m_GameTex = Texture::LoadFromFile(std::string(m_TitleListType->path) + "/meta/iconTex.tga");
            m_GameIcon->SetTexture(m_GameTex);
        }

        if(Pressed()){
            if(nim::CheckUpdate(m_TitleListType->titleId)){
                ACPMetaXml* meta = (ACPMetaXml*) calloc(1, 0x4000);
                ACPResult res = ACPGetTitleMetaXml(m_TitleListType->titleId, meta);
                std::string name = "Unknown";
                if(res == ACP_RESULT_SUCCESS){
                    name = meta->shortname_en;
                }
                free(meta);
                ScreenManager* sm = ScreenManager::Get();
                sm->Push(new UpdateScreen(m_GameIcon->GetTexture(), m_TitleListType, name));
                sm->SetActiveScreen(L"UpdateScreen");
                
            }else{
                Title::StartTitle(m_TitleListType);
            }
        }
        
    }


}

void GuiTitleIcon::Draw(bool isDrc){
    m_Background->Draw(isDrc);
    m_GameIcon->Draw(isDrc);
}

void GuiTitleIcon::SetPos(glm::vec3 pos){
    m_Pos = pos;
    m_Background->SetPos({0,0,0});
    m_GameIcon->SetPos({10,10,0});
}

void GuiTitleIcon::SetScale(glm::vec2 scale){
    m_Scale = scale;
    m_Background->SetScale(scale);
    m_GameIcon->SetScale(scale);
}


