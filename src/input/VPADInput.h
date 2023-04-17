#include <vpad/input.h>
#include <glm/glm.hpp>


class VPAD{
    public:
    static void Update();
    static glm::vec2 GetTouchPos();

    static bool ButtonPressed(VPADButtons button);
    static bool ButtonDown(VPADButtons button);

    private:
    static bool m_Connected;
    static VPADStatus m_Status;
};