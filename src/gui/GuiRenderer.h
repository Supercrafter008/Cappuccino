#pragma once

#include "gfx/Shader.h" 
#include "gfx/Buffer.h" 


#include <glm/glm.hpp>

enum ShaderType{
    SHADER_COLOR = 0x0,
    SHADER_TEXTURE = 0x1,
    SHADER_TEXT = 0x2
};

class GuiRenderer{
    public:
        static GuiRenderer* Get();

        void Begin(Buffer* posBuffer, Buffer* texPosBuffer);
        void BeginRect();
        void SetOffset(const glm::vec3 &vec, bool isDrc);
        void SetScale(const glm::vec2 &vec, bool isDrc);
        void SetColor(const glm::vec4 &vec);
        void SetOutlineColor(const glm::vec4 &vec);
        void SetColorData(glm::vec2 size, float radius, float thickness);

        void BindBuffers();
        void BindShader(ShaderType type);
        void Draw(GX2PrimitiveMode primitiveMode = GX2_PRIMITIVE_MODE_QUADS);
    private:

    GuiRenderer();
    ~GuiRenderer();

    float m_DRCWidthScale, m_DRCHeightScale;
    float m_TVWidthScale, m_TVHeightScale;

    Shader* m_ColorShader;
    Shader* m_TextureShader;
    Shader* m_TextShader;

    Shader* m_CurrentShader;

    Buffer* m_PositonBuffer;
    Buffer* m_TexCoordsBuffer;

    Buffer* m_CustomPositonBuffer;
    Buffer* m_CustomTexCoordsBuffer;
    
    bool customBuffers;

    static GuiRenderer* m_Renderer;
};