#pragma once
#include "Screen.h"

#include "coregui/GuiFrame.h"
#include "coregui/GuiProgressBar.h"
#include "coregui/GuiText.h"
#include "gfx/Texture.h"
#include "utils/TitleUtils.h"
#include "coreinit/mcp.h"

#include <string>


class UpdateScreen : public Screen{
    public:
    UpdateScreen(Texture* gameIcon, MCPTitleListType* type, std::string gameName);
    ~UpdateScreen();

    void Update();
    void Render(bool isDrc);

    private:

    MCPTitleListType* m_Title;
    bool m_UpdateDone = false;
    bool m_UpdateStarted = false;

    GuiText* m_Status = nullptr;
    GuiText* m_Progress = nullptr;
    GuiProgressBar* m_ProgressBar = nullptr;
};