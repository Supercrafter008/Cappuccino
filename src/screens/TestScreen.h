#include "gui/GuiFrame.h"

class TestScreen{
    public:
    TestScreen();

    void Update();
    void Render();

    bool running = true;

    private:
    GuiFrame* m_TvFrame;
    GuiFrame* m_DrcFrame;
};