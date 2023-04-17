#pragma once

#include "GuiElement.h"
#include <vector>



class GuiFrame : public GuiElement{
    public:
        GuiFrame();

        void Draw(bool isDrc);

        void AddElement(GuiElement* element);
        void RemoveElement(GuiElement* element);


        void ClearElements();
    private:
        
        std::vector<GuiElement*> m_Elements;
};