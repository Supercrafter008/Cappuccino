#pragma once

#include <wut_types.h>

#include <glm/glm.hpp>
#include <gx2/texture.h>
#include <gx2/sampler.h>

#include "gfx/Texture.h"
#include "GuiElement.h"
#include "GuiText.h"
#include "GuiRect.h"

class GuiProgressBar : public GuiElement{
public:
    GuiProgressBar();
    ~GuiProgressBar();

    void Draw(bool isDrc) override;

    void SetMaxValue(uint32_t val);
    void SetValue(uint32_t val);

    void SetOutlineThickness(uint32_t val);

    virtual void SetPos(glm::vec3 pos) override;
    virtual void SetScale(glm::vec2 scale) override;

private:

    uint32_t m_MaxVal = 100;
    uint32_t m_Val = 0;
    uint32_t m_Outline = 1;

    GuiRect* m_FillRect = nullptr;
    GuiRect* m_Rect = nullptr;
};