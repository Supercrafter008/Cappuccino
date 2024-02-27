#pragma once

#include <wut_types.h>

#include <glm/glm.hpp>
#include <gx2/texture.h>
#include <gx2/sampler.h>

#include "gfx/Texture.h"
#include "GuiElement.h"
#include "GuiText.h"
#include "GuiRect.h"

class GuiButton : public GuiElement{
public:
    GuiButton(std::wstring text);
    ~GuiButton();

    bool Pressed();

    void Draw(bool isDrc) override;

    void SetText(std::wstring text);
    void SetTextSize(uint32_t textSize);

    GuiRect* GetRect() { return m_Rect; };

    virtual void SetPos(glm::vec3 pos) override;
    virtual void SetScale(glm::vec2 scale) override;

private:

    GuiText* m_Text = nullptr;
    GuiRect* m_Rect = nullptr;
};