#pragma once

#include <wut_types.h>

#include <glm/glm.hpp>

#include "coregui/GuiElement.h"
#include "gui/wiiu/GuiTitleIcon.h"


class GuiDiscIcon : public GuiTitleIcon{
public:
    GuiDiscIcon();
    ~GuiDiscIcon();

    bool Pressed() {return GuiTitleIcon::Pressed();};
    bool Down()  {return GuiTitleIcon::Down();};
    uint32_t HoldTime()  {return GuiTitleIcon::HoldTime();};

    void Update() override;

private:

    bool m_Ejected = false;
    Texture* m_NoDiscTex = nullptr;
    Texture* m_DiscInsTex = nullptr;
    Texture* m_DiscInvTex = nullptr;
    Texture* m_DiscWiiTex = nullptr;
};