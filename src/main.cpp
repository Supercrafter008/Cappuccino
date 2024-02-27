#include <whb/proc.h>
#include <whb/gfx.h>
#include <gx2/draw.h>
#include <gx2/registers.h>
#include <gx2/swap.h>
#include <sndcore2/core.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <gfd.h>
#include <vpad/input.h>
#include <sysapp/launch.h>
#include <nn/nim/nim_cpp.h>


#include "screen/ScreenManager.h"
#include "screen/TestScreen.h"

#include "utils/odm.h"
#include "utils/TitleUtils.h"
#include "input/VPADInput.h"
#include "gfx/Shader.h"
#include "gfx/Texture.h"


int main(int argc, char const* argv[])
{
    WHBProcInit();
    WHBGfxInit();
    AXInit();
    ODM::Open();
    ODM::StopMotor();
    nim::Prepare();

    ScreenManager* screenManager = ScreenManager::Get();
    screenManager->Push(new TestScreen());
    screenManager->SetActiveScreen(L"TestScreen");

    while (WHBProcIsRunning()) {
        VPAD::Update();
        screenManager->Update();
        screenManager->Render();
    }

    nim::Destroy();
    ODM::Close();
    AXQuit();
    WHBGfxShutdown();
    WHBProcShutdown();

    return EXIT_SUCCESS;
}
