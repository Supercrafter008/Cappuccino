#include  "TestScreen.h"

#include <whb/gfx.h>
#include <whb/log.h>
#include <gx2/registers.h>
#include <gx2/clear.h>
#include <vpad/input.h>
#include <sysapp/launch.h>
#include <coreinit/launch.h>
#include <coreinit/filesystem_fsa.h>
#include <whb/proc.h>
#include <coreinit/launch.h>
#include <sys/iosupport.h>

#include <mocha/mocha.h>
#include <mocha/fsa.h>
#include <coreinit/filesystem_fsa.h>
#include <coreinit/dynload.h>
#include <nn/acp/title.h>
#include <coreinit/mcp.h>
#include <coreinit/memdefaultheap.h>

#include <nn/nim/nim_cpp.h>
#include <nn/vctl/vctl_cpp.h>

#include "gfx/Texture.h"
#include "coregui/GuiImage.h"
#include "coregui/GuiText.h"
#include "gui/wiiu/GuiDiscIcon.h"
#include "coregui/GuiButton.h"
#include "coregui/GuiRect.h"
#include "utils/odm.h"
#include "utils/TitleUtils.h"
#include "UpdateScreen.h"
#include "ScreenManager.h"

#include <dirent.h>
#include <iostream>
#include <malloc.h>

#include <coreinit/bsp.h>

GuiText* text;
GuiDiscIcon* discIcon;
FSAClientHandle handle;



TestScreen::TestScreen(){
    m_Name = L"TestScreen";


    m_TvFrame = new GuiFrame();
    m_TvFrame->SetScale({WHBGfxGetTVColourBuffer()->surface.width, WHBGfxGetTVColourBuffer()->surface.height});
    
    m_DrcFrame = m_TvFrame;

    text = new GuiText("Disc Loader");
    text->SetFontSize(72);
    text->SetPos({(m_TvFrame->GetScale().x / 2) - (text->GetTextSize().x / 2), 20, 0});
    


    discIcon = new GuiDiscIcon();
    discIcon->SetPos({(m_TvFrame->GetScale().x / 2) - (discIcon->GetScale().x / 2), (m_TvFrame->GetScale().y / 2) - (discIcon->GetScale().y / 2), 0});

    m_DrcFrame->AddElement(text);
    m_DrcFrame->AddElement(discIcon);

}

TestScreen::~TestScreen(){
    delete text;
    delete discIcon;

}

void TestScreen::Update(){
    int32_t handle = MCP_Open();
    uint32_t outCount;
    MCP_TitleList(handle, &outCount, nullptr, 0);
    m_Titles = new MCPTitleListType[outCount];
    MCP_TitleList(handle, &outCount, m_Titles, sizeof(MCPTitleListType) * outCount);
    MCP_Close(handle);
}
