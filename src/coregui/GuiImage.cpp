#include "GuiImage.h"

#include "GuiRenderer.h"
#include "GuiFrame.h"
#include <gx2/mem.h>

static Texture* invalidTexture;

GuiImage::GuiImage(Texture* texture) : GuiElement(){
    SetTexture(texture);
}

GuiImage::~GuiImage(){

}

void GuiImage::SetTexture(Texture* texture){
    if(texture == nullptr){
        if(invalidTexture == nullptr){
            invalidTexture = Texture::LoadFromFile("TexturePlaceholder.png");
        }
        texture = invalidTexture;
    }
    m_Texture = texture;
    SetScale(texture->GetTextureSize());
}

void GuiImage::SetScale(glm::vec2 scale){
    m_Scale = scale;
}

void GuiImage::Draw(bool isDrc){
    GuiRenderer* renderer = GuiRenderer::Get();
    renderer->BeginRect();
    renderer->BindShader(SHADER_TEXTURE);
    renderer->BindBuffers();
    
    renderer->SetOffset(m_Pos);
    renderer->SetScale(m_Scale);
    renderer->SetColor(m_Color);

    m_Texture->Bind();
    renderer->Draw();
}