#include  "ScreenManager.h"

#include <whb/gfx.h>
#include <gx2/registers.h>
#include <gx2/clear.h>

#include "coregui/GuiImage.h"
#include "coregui/GuiText.h"

ScreenManager* ScreenManager::s_Manager = nullptr;

ScreenManager* ScreenManager::Get(){
    if(s_Manager == nullptr){
        s_Manager = new ScreenManager();
    }
    return s_Manager;
}

int32_t ScreenManager::Push(Screen* screen){
    int32_t index = m_ScreenStack.size();
    m_ScreenStack.push_back(screen);
    return index;
};

bool ScreenManager::Pop(int32_t index){
    m_ScreenStack.erase(m_ScreenStack.begin() + index);
}

bool ScreenManager::SetActiveScreen(std::wstring name){
    int i = 0;

    for(Screen* screen : m_ScreenStack){
        if(screen->GetName() == name){
            m_ActiveScreenIndex = i;
            Render();
            return true;
        }
        i++;
    }

    return false;
}

void ScreenManager::Update(){
    if(m_ScreenStack.size() != 0){
        m_ScreenStack[m_ActiveScreenIndex]->Update();

        if(m_ScreenStack[m_ActiveScreenIndex]->m_DrcFrame != nullptr){
            m_ScreenStack[m_ActiveScreenIndex]->m_DrcFrame->Update();
        }

        if(m_ScreenStack[m_ActiveScreenIndex]->m_TvFrame != nullptr && m_ScreenStack[m_ActiveScreenIndex]->m_TvFrame != m_ScreenStack[m_ActiveScreenIndex]->m_DrcFrame){
            //m_ScreenStack[m_ActiveScreenIndex]->m_TvFrame->Update();
        }
    }

}


void ScreenManager::Render(){
    if(m_ScreenStack.size() != 0){
        WHBGfxBeginRender();

        WHBGfxBeginRenderDRC();
        {
            WHBGfxClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            GX2SetDepthOnlyControl(GX2_ENABLE, GX2_ENABLE, GX2_COMPARE_FUNC_LEQUAL);
            GX2SetColorControl(GX2_LOGIC_OP_COPY, 1, GX2_DISABLE, GX2_ENABLE);
            GX2SetBlendControl(GX2_RENDER_TARGET_0, GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA, GX2_BLEND_COMBINE_MODE_ADD, GX2_ENABLE, GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA, GX2_BLEND_COMBINE_MODE_ADD);
            GX2SetCullOnlyControl(GX2_FRONT_FACE_CCW, GX2_DISABLE, GX2_ENABLE);
            if(m_ScreenStack[m_ActiveScreenIndex]->m_DrcFrame != nullptr){
                m_ScreenStack[m_ActiveScreenIndex]->m_DrcFrame->Draw(true);
            }
        }
        WHBGfxFinishRenderDRC();

        WHBGfxBeginRenderTV();
        {
            WHBGfxClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            GX2SetDepthOnlyControl(GX2_ENABLE, GX2_ENABLE, GX2_COMPARE_FUNC_LEQUAL);
            GX2SetColorControl(GX2_LOGIC_OP_COPY, 1, GX2_DISABLE, GX2_ENABLE);
            GX2SetBlendControl(GX2_RENDER_TARGET_0, GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA, GX2_BLEND_COMBINE_MODE_ADD, GX2_ENABLE, GX2_BLEND_MODE_SRC_ALPHA, GX2_BLEND_MODE_INV_SRC_ALPHA, GX2_BLEND_COMBINE_MODE_ADD);
            GX2SetCullOnlyControl(GX2_FRONT_FACE_CCW, GX2_DISABLE, GX2_ENABLE);
            if(m_ScreenStack[m_ActiveScreenIndex]->m_TvFrame != nullptr){
                m_ScreenStack[m_ActiveScreenIndex]->m_TvFrame->Draw(false);
            }
           
        }
        WHBGfxFinishRenderTV();

        WHBGfxFinishRender();
    }

}