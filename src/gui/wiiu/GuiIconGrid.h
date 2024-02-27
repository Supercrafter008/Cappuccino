#pragma once

#include <wut_types.h>

#include <glm/glm.hpp>

#include "coregui/GuiElement.h"
#include "gui/wiiu/GuiTitleIcon.h"
#include "gui/wiiu/GuiDiscIcon.h"

#include <array>


class GuiIconGrid : public GuiElement{
public:
    GuiIconGrid();
    ~GuiIconGrid();

    void SetTitle(MCPTitleListType* title, uint8_t index);

    void Update() override;
    void Draw(bool isDrc) override;

private:
    std::array<GuiTitleIcon, 15> m_TitleIcons;
};