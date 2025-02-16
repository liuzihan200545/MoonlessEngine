#include "mlpch.h"
#include "Moonless/Renderer/Renderer2D.h"

#include <glm/ext/matrix_transform.hpp>

namespace Moonless
{

    struct Renderer2DStorage
    {
        std::shared_ptr<VertexArray> QuadVertexArray;
        std::shared_ptr<Texture2D> WhiteTexture;
        std::shared_ptr<Shader> TextureShader;
    };

    static Renderer2DStorage* s_Data;


    void Renderer2D::Init() {
        ML_PROFILE_FUNCTION();

        s_Data = new Renderer2DStorage();
        s_Data->QuadVertexArray = VertexArray::Create();

        float squareVertices[5 * 4] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices,sizeof(squareVertices));

        squareVB->SetLayout({
            { ShaderDataType::Float3,"a_Position"},
            { ShaderDataType::Float2, "a_TexCoord" }
        });
        
        s_Data->QuadVertexArray->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));

        s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

        s_Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->UploadUniformInt("u_Texture", 0);

        s_Data->WhiteTexture = Texture2D::Create(1,1);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));
    }

    void Renderer2D::Shutdown() {
        ML_PROFILE_FUNCTION();

        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera) {
        ML_PROFILE_FUNCTION();

        s_Data->TextureShader->Bind();
        s_Data->TextureShader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene() {
        ML_PROFILE_FUNCTION();

    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
        ML_PROFILE_FUNCTION();

        DrawQuad({position.x,position.y,0},size,color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
        ML_PROFILE_FUNCTION();

        s_Data->TextureShader->UploadUniformFloat4("u_Color", color);
        s_Data->WhiteTexture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->TextureShader->UploadUniformMat4("u_Transform", transform);
        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture) {
        ML_PROFILE_FUNCTION();

        DrawQuad({position.x,position.y,0.0f},size,texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture) {
        ML_PROFILE_FUNCTION();

        s_Data->TextureShader->UploadUniformFloat4("u_Color", glm::vec4(1.0f));
        texture->Bind();

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        s_Data->TextureShader->UploadUniformMat4("u_Transform", transform);

        s_Data->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
    }

}
