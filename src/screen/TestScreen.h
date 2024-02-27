#pragma once
#include "Screen.h"

#include "coregui/GuiFrame.h"

class TestScreen : public Screen{
    public:
    TestScreen();
    ~TestScreen();

    void Update();
    void Render(bool isDrc);

};