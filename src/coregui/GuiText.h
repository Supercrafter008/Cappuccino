#pragma once

#include "GuiImage.h"

#include <string>
#include "gfx/Font.h"


class GuiText : public GuiElement{
public:
    GuiText(std::wstring text);
    GuiText(std::wstring text, Font* Font);
    GuiText(std::string text);
    GuiText(std::string text, Font* Font);
    ~GuiText();

    void SetFontSize(uint32_t size);
    void SetText(std::wstring text);
    void SetText(std::string text);

    void Draw(bool isDrc) override;

    glm::vec2 GetTextSize() { return m_Font->GetTextSize(m_Text, m_FontSize); };

private:
    Buffer* m_PosBuffer = nullptr;
    Buffer* m_TexCoordsBuffer = nullptr;

    Font* m_Font = nullptr;
    std::wstring m_Text;
    float m_FontSize = 1.0f;
    bool m_DefaultFont = false;
};