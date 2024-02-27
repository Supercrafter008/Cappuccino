#pragma once
#include <nn/nim/nim_cpp.h>
#include <nn/vctl/vctl_cpp.h>
#include <coreinit/mcp.h>

enum UpdateStatus {
    PREPARING_DOWNLOAD = 0x0,
    DOWNLOADING = 0x1000000,
    DOWNLOAD_DONE = 0x2000000,
    PREPARING_INSTALL = 0x3000000,
    INSTALLING = 0x4000000,
    INSTALL_DONE = 0x5000000
};

struct UpdateInfo {
    float totalDownloadBytes;
    float downloadedBytes;
    float totalInstallBytes;
    float installedBytes;
    uint32_t totalFileCount;
    uint32_t fileCount;
    UpdateStatus status;
};

class nim{
    public:
    static void Prepare();
    static void Destroy();

    static bool CheckUpdate(uint32_t titleId);
    static bool Start();

    static void Cancel();


    static UpdateInfo Update();

    
    private:

    static nn::nim::TitlePackageTask* s_CurrentTask;
    static nn::vctl::UpdateInfo* s_LastInfo;
    static uint64_t s_CurrentTaskID;

};

class Title{
    public:
    static void StartTitle(MCPTitleListType* title);
};

