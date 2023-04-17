#pragma once

#include <wut_types.h>

#include <glm/glm.hpp>
#include <gx2/texture.h>
#include <gx2/sampler.h>

#include "gfx/Texture.h"
#include "GuiElement.h"

class GuiImage : public GuiElement{
public:
    GuiImage(Texture* texture);
    ~GuiImage();

    void SetScale(glm::vec2 scale) override;

    void SetTexture(Texture* texture);

    void Draw(bool isDrc) override;

private:
    glm::vec2 m_TextScale;

    Texture* m_Texture;
};