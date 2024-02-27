#include "TitleUtils.h"
#include <coreinit/mcp.h>
#include <coreinit/launch.h>
#include <sysapp/launch.h>
#include <nn/acp.h>


nn::vctl::UpdateInfo* nim::s_LastInfo = nullptr;
nn::nim::TitlePackageTask* nim::s_CurrentTask = nullptr;
uint64_t nim::s_CurrentTaskID = 0;

void nim::Prepare(){
    nn::nim::Initialize();
    nn::vctl::Initialize();
}

void nim::Destroy(){
    nn::vctl::Finalize();
    nn::nim::Finalize();
}

bool nim::CheckUpdate(uint32_t titleId){

    if(s_LastInfo != nullptr){
        delete s_LastInfo;
        s_LastInfo = nullptr;
    } 

    s_LastInfo = new nn::vctl::UpdateInfo;

    nn::Result res = nn::vctl::GetUpdateInfo(s_LastInfo, titleId, 0);

    if(res.GetDescription() == 0){
        return true;
    }else{
        return false;
    }
}

bool nim::Start(){
    if(s_LastInfo == nullptr){
        return false;
    }

    int64_t installSize;
    nn::nim::TitlePackageTaskConfig conf;
    conf.titleId = s_LastInfo->titleID;
    conf.titleType = s_LastInfo->updateTitleType;
    conf.titleVersion = s_LastInfo->latestVersion;
    conf.downloadMedia = s_LastInfo->updateMediaType;
    conf.hasTitleUpdate = s_LastInfo->hasUpdateTitle;
    conf.downloadMedia2 = s_LastInfo->updateMediaType;
    conf.oldTitleVersion = s_LastInfo->oldVersion;
    conf.ukn_0x14 = 0;
    conf.ukn_0x15 = 1;
    conf.postDownloadAction = 2;
    conf.ukn_0x17 = 0;

    nn::nim::CalculateTitleInstallSize(&installSize, &conf, 0, 0);

    nn::nim::RegisterTitlePackageTask(&conf, 0, 0);

    uint32_t titleNum = nn::nim::GetNumTitlePackages();
    
    nn::nim::ListTitlePackages(&s_CurrentTaskID, titleNum);

    if(s_CurrentTask != nullptr){
        s_CurrentTask->StopForeground();
        delete s_CurrentTask;
        s_CurrentTask = nullptr;
    }

    s_CurrentTask = new nn::nim::TitlePackageTask;
    s_CurrentTask->Open(s_CurrentTaskID);

    return true;
}

void nim::Cancel(){
    s_CurrentTask->StopForeground();
    s_CurrentTask->Close();
    nn::nim::UnregisterTitlePackageTask(s_CurrentTaskID);
    nn::nim::CancelAll();
}

UpdateInfo nim::Update(){
    UpdateInfo info;

    nn::nim::TitlePackageProgress prog;

    s_CurrentTask->GetProgress(&prog);
    if(prog.state == UpdateStatus::PREPARING_DOWNLOAD){
        s_CurrentTask->StartForeground();
    }else if(prog.state == UpdateStatus::DOWNLOAD_DONE){
        s_CurrentTask->StartInstall();
    }else if(prog.state == UpdateStatus::INSTALL_DONE){
        s_CurrentTask->StopForeground();
        s_CurrentTask->Close();
        nn::nim::UnregisterTitlePackageTask(s_CurrentTaskID);
        nn::nim::CancelAll();
    }

    info.status = (UpdateStatus)prog.state;
    info.fileCount = prog.numInstalledEntries;
    info.totalFileCount = prog.totalNumEntries;
    info.downloadedBytes = prog.downloadedSize / 2000000.0f;
    info.totalDownloadBytes = prog.totalDownloadSize / 2000000.0f;
    info.installedBytes = prog.installedSize / 2000000.0f;
    info.totalInstallBytes =  prog.totalInstallSize / 2000000.0f;

    return info;

}

void Title::StartTitle(MCPTitleListType* titleList){
    ACPAssignTitlePatch(titleList);
    _SYSLaunchTitleByPathFromLauncher(titleList->path, 0);    
}