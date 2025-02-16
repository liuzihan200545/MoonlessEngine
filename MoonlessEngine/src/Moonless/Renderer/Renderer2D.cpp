#include "mlpch.h"
#include "Moonless/Renderer/Renderer2D.h"

#include <glm/ext/matrix_transform.hpp>

namespace Moonless
{

    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        // TODO: texid
    };

    struct Renderer2DData
    {
        const uint32_t MaxQuads = 10000;
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;
        
        std::shared_ptr<VertexArray> QuadVertexArray;
        std::shared_ptr<VertexBuffer> QuadVertexBuffer;
        std::shared_ptr<Texture2D> WhiteTexture;
        std::shared_ptr<Shader> TextureShader;

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;
    };

    static Renderer2DData s_Data;


    void Renderer2D::Init() {
        ML_PROFILE_FUNCTION();
        
        s_Data.QuadVertexArray = VertexArray::Create();

        s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));

        s_Data.QuadVertexBuffer -> SetLayout({
            { ShaderDataType::Float3,"a_Position"},
            {ShaderDataType::Float4,"a_Color"},
            { ShaderDataType::Float2, "a_TexCoord" }
        });
        
        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
        
        s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

        uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

        uint32_t offset = 0;
        for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        std::shared_ptr<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices,s_Data.MaxIndices);
        s_Data.QuadVertexArray->SetIndexBuffer(quadIB);
        delete[] quadIndices;

        s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->UploadUniformInt("u_Texture", 0);

        s_Data.WhiteTexture = Texture2D::Create(1,1);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
    }

    void Renderer2D::Shutdown() {
        ML_PROFILE_FUNCTION();
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera) {
        ML_PROFILE_FUNCTION();

        s_Data.TextureShader->Bind();
        s_Data.TextureShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    }

    void Renderer2D::EndScene() {
        ML_PROFILE_FUNCTION();

        uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Flush() {
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
        ML_PROFILE_FUNCTION();

        DrawQuad({position.x,position.y,0},size,color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
        ML_PROFILE_FUNCTION();

        s_Data.QuadVertexBufferPtr->Position = position;
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;

        s_Data.TextureShader->UploadUniformFloat4("u_Color", color);
        s_Data.WhiteTexture->Bind();

        /*glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data.TextureShader->UploadUniformMat4("u_Transform", transform);
        s_Data.TextureShader->UploadUniformFloat("u_Tiling_Factor",1.0f);
        s_Data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color) {
        /*ML_PROFILE_FUNCTION();

        DrawQuad({position.x,position.y,0.0f},size,texture,tiling_factor,tint_color);*/
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color) {
        /*ML_PROFILE_FUNCTION();

        s_Data.TextureShader->UploadUniformFloat4("u_Color", tint_color);
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data.TextureShader->UploadUniformMat4("u_Transform", transform);
        s_Data.TextureShader->UploadUniformFloat("u_Tiling_Factor",tiling_factor);

        s_Data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
        /*DrawRotatedQuad({position.x,position.y,0.0f},size,rotation,color);*/
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color) {
        /*ML_PROFILE_FUNCTION();

        s_Data.TextureShader->UploadUniformFloat4("u_Color", color);
        s_Data.WhiteTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                            * glm::rotate(glm::mat4(1.0f),rotation, {0.0f,0.0f,1.0f})
                            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data.TextureShader->UploadUniformMat4("u_Transform", transform);
        s_Data.TextureShader->UploadUniformFloat("u_Tiling_Factor",1.0f);
        s_Data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation,
        const std::shared_ptr<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
    {
        /*DrawRotatedQuad({position.x,position.y,0.0f},size,rotation,texture,tiling_factor,tint_color);
    */
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation,
        const std::shared_ptr<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
    {
        /*ML_PROFILE_FUNCTION();

        s_Data.TextureShader->UploadUniformFloat4("u_Color", tint_color);
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
                            * glm::rotate(glm::mat4(1.0f),rotation, {0.0f,0.0f,1.0f})
                            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        
        s_Data.TextureShader->UploadUniformMat4("u_Transform", transform);
        s_Data.TextureShader->UploadUniformFloat("u_Tiling_Factor",tiling_factor);

        s_Data.QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray);*/
    }
}
