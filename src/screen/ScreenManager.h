#pragma once

#include "Screen.h"

#include <vector>


class ScreenManager{
    public:
    ScreenManager() {};

    static ScreenManager* Get();

    int32_t Push(Screen* screen);
    bool Pop(int32_t index);

    bool SetActiveScreen(std::wstring name);

    void Update();
    void Render();

    private:
    static ScreenManager* s_Manager;

    int32_t m_ActiveScreenIndex = 0;

    std::vector<Screen*> m_ScreenStack;
};