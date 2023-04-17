#include  "TestScreen.h"

#include <whb/gfx.h>
#include <whb/log.h>
#include <whb/log_udp.h>
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

#include "gfx/Texture.h"
#include "gui/GuiImage.h"
#include "gui/GuiText.h"
#include "gui/GuiButton.h"
#include "gui/GuiRect.h"
#include "utils/odm.h"

#include <dirent.h>
#include <iostream>
#include <malloc.h>

#include <nn/nim/nim_cpp.h>
#include <coreinit/bsp.h>

GuiImage* image;
GuiButton* drcButton;
FSAClientHandle handle;

Texture* noDisc = nullptr;
Texture* discInserted = nullptr;
Texture* invalidDisc = nullptr;
Texture* WiiDisc = nullptr;
Texture* gameIcon = nullptr;


TestScreen::TestScreen(){
    m_TvFrame = new GuiFrame();
    m_TvFrame->SetScale({WHBGfxGetTVColourBuffer()->surface.width, WHBGfxGetTVColourBuffer()->surface.height});

    m_DrcFrame = new GuiFrame();
    m_DrcFrame->SetScale({WHBGfxGetDRCColourBuffer()->surface.width, WHBGfxGetDRCColourBuffer()->surface.height});
    drcButton = new GuiButton(L"Launch Game");
    GuiText* text = new GuiText(L"TEST");
    drcButton->SetPos({200,200,0});
    drcButton->SetScale({400,200});
    drcButton->SetTextSize(24);
    image = new GuiImage(Texture::LoadFromFile("L.png"));
    image->SetPos({600,200,0});
    text->SetPos({600, 200,0});
    m_DrcFrame->AddElement(image);
    m_DrcFrame->AddElement(drcButton);
    Mocha_InitLibrary();

    std::string str;
    FSAInit();
    FSAClientHandle cl = FSAAddClient(nullptr);
    Mocha_UnlockFSClientEx(cl);

    noDisc = Texture::LoadFromFile("NoDiscPlaceholder.png");
    discInserted = Texture::LoadFromFile("DiscInsertedPlaceholder.png");
    invalidDisc = Texture::LoadFromFile("InvalidDiscPlaceholder.png");
    WiiDisc = Texture::LoadFromFile("WiiDiscPlaceholder.png");
    MochaUtilsStatus stat = Mocha_MountFS("odd01",  "/dev/odd01", "/vol/storage_odd01");
    if(stat == MOCHA_RESULT_ALREADY_EXISTS){
        stat = Mocha_MountFS("odd01",  nullptr, "/vol/storage_odd01");
        if(stat != MOCHA_RESULT_SUCCESS){
            str += std::string(Mocha_GetStatusStr(stat));
            str += " odd01\n";
        }
    }else{
        stat = Mocha_MountFS("odd01",  nullptr, "/vol/storage_odd01");
        str += std::string(Mocha_GetStatusStr(stat));
        str += " odd01\n";
    }

    stat = Mocha_MountFS("odd02",  "/dev/odd02", "/vol/storage_odd02");
    if(stat == MOCHA_RESULT_ALREADY_EXISTS){
        stat = Mocha_MountFS("odd02",  nullptr, "/vol/storage_odd02");
        if(stat != MOCHA_RESULT_SUCCESS){
            str += std::string(Mocha_GetStatusStr(stat));
            str += " odd02\n";
        }
    }else{
        stat = Mocha_MountFS("odd02",  nullptr, "/vol/storage_odd02");
        str += std::string(Mocha_GetStatusStr(stat));
        str += " odd02\n";
    }


    stat = Mocha_MountFS("odd03",  "/dev/odd03", "/vol/storage_odd03");
    if(stat == MOCHA_RESULT_ALREADY_EXISTS){
        stat = Mocha_MountFS("odd03",  nullptr, "/vol/storage_odd03");
        if(stat != MOCHA_RESULT_SUCCESS){
            str += std::string(Mocha_GetStatusStr(stat));
            str += " odd03\n";
        }
    }else{
        stat = Mocha_MountFS("odd03",  nullptr, "/vol/storage_odd03");
        str += std::string(Mocha_GetStatusStr(stat));
        str += " odd03\n";
    }

    stat = Mocha_MountFS("odd04",  "/dev/odd04", "/vol/storage_odd04");
    if(stat == MOCHA_RESULT_ALREADY_EXISTS){
        stat = Mocha_MountFS("odd04",  nullptr, "/vol/storage_odd04");
        if(stat != MOCHA_RESULT_SUCCESS){
            str += std::string(Mocha_GetStatusStr(stat));
            str += " odd04\n";
        }
    }else{
        stat = Mocha_MountFS("odd04",  nullptr, "/vol/storage_odd04");
        str += std::string(Mocha_GetStatusStr(stat));
        str += " odd04\n";
    }


}

void TestScreen::Update(){
    static MCPTitleListType* oddTitle = nullptr;

    DiscStatus status = ODM::GetDiscStatus();
    
    switch (status)
    {
    case DISC_NONE:
        if(gameIcon != nullptr){
            delete gameIcon;
            gameIcon = nullptr;
        }
        if(oddTitle != nullptr){
            delete oddTitle;
            oddTitle = nullptr;
        }
        image->SetTexture(noDisc);
        break;
    case DISC_INSERTED:
        image->SetTexture(discInserted);
        break;
    case DISC_WII:
        image->SetTexture(WiiDisc);
        break;
    case DISC_ERROR:
        image->SetTexture(invalidDisc);
        break;
    case DISC_WIIU:
        if(gameIcon == nullptr){
            int32_t handle = MCP_Open();
            uint32_t outCount;
            oddTitle = new MCPTitleListType;
            MCP_TitleListByDeviceType(handle, MCPDeviceType::MCP_DEVICE_TYPE_ODD, &outCount, oddTitle, sizeof(MCPTitleListType));
            MCP_Close(handle);
            gameIcon = Texture::LoadFromFile((std::string(oddTitle->path) + "/meta/iconTex.tga").c_str());
            break;
        }
        image->SetTexture(gameIcon);
        break;
        
    }

    if(drcButton->Pressed()){
        ACPAssignTitlePatch(oddTitle);
        _SYSLaunchTitleByPathFromLauncher(std::string(oddTitle->path).c_str(), 0);        
    }
}


void TestScreen::Render(){
    WHBGfxBeginRender();

    WHBGfxBeginRenderDRC();
    {
        WHBGfxClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        GX2SetDepthOnlyControl(GX2_ENABLE, GX2_ENABLE, GX2_COMPARE_FUNC_LEQUAL);
        GX2SetColorControl(GX2_LOGIC_OP_COPY, 1, GX2_DISABLE, GX2_ENABLE);
        GX2SetBlendControl(GX2_RENDER_TARGET_0, GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA, GX2_BLEND_COMBINE_MODE_ADD, GX2_ENABLE, GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA, GX2_BLEND_COMBINE_MODE_ADD);
        GX2SetCullOnlyControl(GX2_FRONT_FACE_CCW, GX2_DISABLE, GX2_ENABLE);
        m_DrcFrame->Draw(true);
    }
    WHBGfxFinishRenderDRC();

    WHBGfxBeginRenderTV();
    {
        WHBGfxClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        GX2SetDepthOnlyControl(GX2_ENABLE, GX2_ENABLE, GX2_COMPARE_FUNC_LEQUAL);
        GX2SetColorControl(GX2_LOGIC_OP_COPY, 1, GX2_DISABLE, GX2_ENABLE);
        GX2SetBlendControl(GX2_RENDER_TARGET_0, GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA, GX2_BLEND_COMBINE_MODE_ADD, GX2_ENABLE, GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA, GX2_BLEND_COMBINE_MODE_ADD);
        GX2SetCullOnlyControl(GX2_FRONT_FACE_CCW, GX2_DISABLE, GX2_ENABLE);
        m_TvFrame->Draw(false);                
    }
    WHBGfxFinishRenderTV();

    WHBGfxFinishRender();
}