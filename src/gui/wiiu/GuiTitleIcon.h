#pragma once

#include <wut_types.h>

#include <glm/glm.hpp>
#include <gx2/texture.h>
#include <gx2/sampler.h>

#include "gfx/Texture.h"
#include "coregui/GuiElement.h"
#include "coregui/GuiRect.h"
#include "coregui/GuiImage.h"

#include <coreinit/mcp.h>

class GuiTitleIcon : public GuiElement{
public:
    GuiTitleIcon();
    ~GuiTitleIcon();

    void SetTitle(MCPTitleListType* title);
    void SetTexture(Texture* tex);

    bool IsEmpty() { return m_TitleListType == nullptr;};

    bool Pressed();
    bool Down();
    uint32_t HoldTime();

    void Update() override;
    void Draw(bool isDrc) override;


    virtual void SetPos(glm::vec3 pos) override;
    virtual void SetScale(glm::vec2 scale) override;

private:
    uint32_t m_LastFrameHoldTime = 0;
    uint32_t m_HoldTime = 0;


    MCPTitleListType* m_TitleListType = nullptr;
    GuiRect* m_Background = nullptr;
    GuiImage* m_GameIcon = nullptr;
    Texture* m_GameTex = nullptr;
};