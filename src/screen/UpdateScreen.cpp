#include  "UpdateScreen.h"

#include <whb/gfx.h>
#include <gx2/registers.h>
#include <gx2/clear.h>

#include "coregui/GuiImage.h"
#include "coregui/GuiText.h"

#include "coregui/GuiProgressBar.h"
#include "screen/ScreenManager.h"

UpdateScreen::UpdateScreen(Texture* gIcon, MCPTitleListType* title, std::string gName){
    m_Name = L"UpdateScreen";

    m_Title = title;

    m_TvFrame = new GuiFrame();
    m_TvFrame->SetScale({WHBGfxGetTVColourBuffer()->surface.width, WHBGfxGetTVColourBuffer()->surface.height});

    m_DrcFrame = new GuiFrame();
    m_DrcFrame->SetScale({WHBGfxGetDRCColourBuffer()->surface.width, WHBGfxGetDRCColourBuffer()->surface.height});
    
    GuiImage* gameIcon = new GuiImage(gIcon);
    m_TvFrame->AddElement(gameIcon);
    m_DrcFrame->AddElement(gameIcon);
    gameIcon->SetPos({(m_TvFrame->GetScale().x / 2) - (gameIcon->GetScale().x / 2), ((m_TvFrame->GetScale().y / 2) - (gameIcon->GetScale().y / 2)) - 275, 0});
    

    GuiText* gameName = new GuiText(gName);
    m_TvFrame->AddElement(gameName);
    m_DrcFrame->AddElement(gameName);
    gameName->SetFontSize(38);
    gameName->SetPos({(m_TvFrame->GetScale().x / 2) - (gameName->GetTextSize().x / 2), ((m_TvFrame->GetScale().y / 2) - (gameName->GetTextSize().y / 2)) - 135, 0});
    

    m_Status = new GuiText("Preparing");
    m_TvFrame->AddElement(m_Status);
    m_DrcFrame->AddElement(m_Status);
    m_Status->SetFontSize(32);
    m_Status->SetPos({(m_TvFrame->GetScale().x / 2) - (m_Status->GetTextSize().x / 2), ((m_TvFrame->GetScale().y / 2) - (m_Status->GetTextSize().y / 2)) - 25, 0});
    


}

UpdateScreen::~UpdateScreen(){
    m_TvFrame->ClearElements();
    m_DrcFrame->ClearElements();
}

void UpdateScreen::Update(){
    if(!m_UpdateStarted){
        nim::Start();
        m_UpdateStarted = true;
    }
    if(m_UpdateDone){
        Title::StartTitle(m_Title);
        return;
    };
    UpdateInfo info = nim::Update();
    switch(info.status){
        case UpdateStatus::PREPARING_DOWNLOAD:
            m_Status->SetText("Preparing Download");
            m_Status->SetPos({(m_TvFrame->GetScale().x / 2) - (m_Status->GetTextSize().x / 2), ((m_TvFrame->GetScale().y / 2) - (m_Status->GetTextSize().y / 2)) - 25, 0});
            break;
        case UpdateStatus::DOWNLOADING:
            m_Status->SetText("Downloading");
            m_Status->SetPos({(m_TvFrame->GetScale().x / 2) - (m_Status->GetTextSize().x / 2), ((m_TvFrame->GetScale().y / 2) - (m_Status->GetTextSize().y / 2)) - 25, 0});
            if(m_ProgressBar == nullptr){
                m_ProgressBar = new GuiProgressBar();
                m_ProgressBar->SetOutlineThickness(6);
                m_ProgressBar->SetScale({900, 70});
                m_ProgressBar->SetPos({((m_TvFrame->GetScale().x / 2) - (m_ProgressBar->GetScale().x / 2)), ((m_TvFrame->GetScale().y / 2) - (m_ProgressBar->GetScale().y / 2)) + 135, 0});
                m_TvFrame->AddElement(m_ProgressBar);
                m_DrcFrame->AddElement(m_ProgressBar);
            }
            m_ProgressBar->SetMaxValue(info.totalDownloadBytes * 100);
            m_ProgressBar->SetValue(info.downloadedBytes * 100);
            break;
        case UpdateStatus::DOWNLOAD_DONE:
            m_Status->SetText("Download Finished");
            m_Status->SetPos({(m_TvFrame->GetScale().x / 2) - (m_Status->GetTextSize().x / 2), ((m_TvFrame->GetScale().y / 2) - (m_Status->GetTextSize().y / 2)) - 25, 0});
            if(m_ProgressBar != nullptr){
                m_TvFrame->RemoveElement(m_ProgressBar);
                m_DrcFrame->RemoveElement(m_ProgressBar);
                delete m_ProgressBar;
                m_ProgressBar = nullptr;
            }
            break;
        case UpdateStatus::PREPARING_INSTALL:
            m_Status->SetText("Preparing Install");
            m_Status->SetPos({(m_TvFrame->GetScale().x / 2) - (m_Status->GetTextSize().x / 2), ((m_TvFrame->GetScale().y / 2) - (m_Status->GetTextSize().y / 2)) - 25, 0});
            break;
        case UpdateStatus::INSTALLING:
            m_Status->SetText("Installing");
            m_Status->SetPos({(m_TvFrame->GetScale().x / 2) - (m_Status->GetTextSize().x / 2), ((m_TvFrame->GetScale().y / 2) - (m_Status->GetTextSize().y / 2)) - 25, 0});
            if(m_ProgressBar == nullptr){
                m_ProgressBar = new GuiProgressBar();
                m_ProgressBar->SetOutlineThickness(6);
                m_ProgressBar->SetScale({800, 70});
                m_ProgressBar->SetPos({(m_TvFrame->GetScale().x / 2) - (m_ProgressBar->GetScale().x / 2), ((m_TvFrame->GetScale().y / 2) - (m_ProgressBar->GetScale().y / 2)) + 135, 0});
                m_TvFrame->AddElement(m_ProgressBar);
                m_DrcFrame->AddElement(m_ProgressBar);
                
            }
            m_ProgressBar->SetMaxValue(info.totalInstallBytes * 100);
            m_ProgressBar->SetValue(info.installedBytes * 100);
            break;
        case UpdateStatus::INSTALL_DONE:
            m_UpdateDone = true;
            m_Status->SetText("Launching Game");
            m_Status->SetPos({(m_TvFrame->GetScale().x / 2) - (m_Status->GetTextSize().x / 2), ((m_TvFrame->GetScale().y / 2) - (m_Status->GetTextSize().y / 2)) - 25, 0});
            if(m_ProgressBar != nullptr){
                m_TvFrame->RemoveElement(m_ProgressBar);
                m_DrcFrame->RemoveElement(m_ProgressBar);
                delete m_ProgressBar;
                m_ProgressBar = nullptr;
            }
            break;
        
    }

}
