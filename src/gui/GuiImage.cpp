#include "GuiImage.h"

#include "GuiRenderer.h"
#include "GuiFrame.h"
#include <gx2/mem.h>

static Texture* invalidTexture;

GuiImage::GuiImage(Texture* texture) : GuiElement(){
    SetTexture(texture);
}

GuiImage::~GuiImage(){
    if(m_Texture) delete m_Texture;
}

void GuiImage::SetTexture(Texture* texture){
    if(texture == nullptr){
        if(invalidTexture == nullptr){
            invalidTexture = Texture::LoadFromFile("TexturePlaceholder.png");
        }
        texture = invalidTexture;
    }
    m_Texture = texture;
    SetScale({1,1});
}

void GuiImage::SetScale(glm::vec2 scale){
    m_Scale = (glm::vec2)m_Texture->GetTextureSize() * scale;
}

void GuiImage::Draw(bool isDrc){
    GuiRenderer* renderer = GuiRenderer::Get();
    renderer->BeginRect();
    renderer->BindShader(SHADER_TEXTURE);
    renderer->BindBuffers();
    
    renderer->SetOffset(m_Pos, isDrc);
    renderer->SetScale(m_Scale, isDrc);
    renderer->SetColor(m_Color);

    m_Texture->Bind();
    renderer->Draw();
}