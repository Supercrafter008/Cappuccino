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

#include "gfx/Shader.h"
#include "gfx/Texture.h"

#include <sysapp/launch.h>
#include <nn/nim/nim_cpp.h>
#include "input/VPADInput.h"

#include "screens/TestScreen.h"
#include "utils/odm.h"


int main(int argc, char const* argv[])
{
    WHBProcInit();
    WHBGfxInit();
    AXInit();
    nn::nim::Initialize();
    ODM::Open();


    TestScreen screen;



    while (WHBProcIsRunning()) {
        VPAD::Update();
        screen.Update();
        screen.Render();
    }

    ODM::Close();
    nn::nim::Finalize();
    AXQuit();
    WHBGfxShutdown();
    WHBProcShutdown();

    return EXIT_SUCCESS;
}
