#include "GuiDiscIcon.h"

#include <gx2/mem.h>
#include <string>

#include "input/VPADInput.h"

#include "utils/TitleUtils.h"
#include "utils/ODM.h"

GuiDiscIcon::GuiDiscIcon() : GuiTitleIcon(){
    m_NoDiscTex = Texture::LoadFromFile("NoDiscPlaceholder.png");
    m_DiscInsTex = Texture::LoadFromFile("DiscInsertedPlaceholder.png");
    m_DiscInvTex = Texture::LoadFromFile("InvalidDiscPlaceholder.png");
    m_DiscWiiTex = Texture::LoadFromFile("WiiDiscPlaceholder.png");
}

GuiDiscIcon::~GuiDiscIcon(){
    if(m_NoDiscTex) delete m_NoDiscTex;
    if(m_DiscInsTex) delete m_DiscInsTex;
    if(m_DiscInvTex) delete m_DiscInvTex;
    if(m_DiscWiiTex) delete m_DiscWiiTex;
}


void GuiDiscIcon::Update(){
    DiscStatus status = ODM::GetDiscStatus();

    switch (status)
    {
    case DISC_NONE:
        if(m_Ejected){
            SetTitle(nullptr);
            m_Ejected = false;
        }
        SetTexture(m_NoDiscTex);
        break;
    case DISC_INSERTED:
        SetTexture(m_DiscInsTex);
        break;
    case DISC_WII:
        SetTexture(m_DiscWiiTex);
        break;
    case DISC_ERROR:
        SetTexture(m_DiscInvTex);
        break;
    case DISC_WIIU:
        if(IsEmpty()){
            int32_t handle = MCP_Open();
            uint32_t outCount;
            MCPTitleListType* title = new MCPTitleListType;
            MCP_TitleListByAppAndDeviceType(handle, MCPAppType::MCP_APP_TYPE_GAME, MCPDeviceType::MCP_DEVICE_TYPE_ODD, &outCount, title, sizeof(MCPTitleListType));
            MCP_Close(handle);
            if(outCount != 0){
                SetTitle(title);
                m_Ejected = true;
            }
        }
        break;
    }

    GuiTitleIcon::Update();
}
