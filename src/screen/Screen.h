#pragma once
#include "coregui/GuiFrame.h"

#include <string>

class Screen{
    public:
    Screen() {};

    std::wstring GetName() { return m_Name; };

    virtual void Update() {};

    protected:
    std::wstring m_Name;

    GuiFrame* m_TvFrame;
    GuiFrame* m_DrcFrame;

    friend class ScreenManager;
};