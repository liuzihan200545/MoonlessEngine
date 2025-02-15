#include "mlpch.h"
#include "Moonless/Renderer/Renderer.h"

#include "Moonless/Renderer/RenderCommand.h"
#include "Moonless/Renderer/Renderer2D.h"
#include "Platform/OpenGL/OpenGLShader.h"

std::unique_ptr<Moonless::Renderer::SceneData> Moonless::Renderer::m_SceneData = std::make_unique<SceneData>();

void Moonless::Renderer::BeginScene(OrthographicCamera& camera) {
    m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Moonless::Renderer::EndScene() {
    
}

void Moonless::Renderer::Submit(const std::shared_ptr<Shader>& shader,
    const std::shared_ptr<VertexArray>& vertexArray,const glm::mat4& transform) {
    shader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection",m_SceneData->ViewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform",transform);
    
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}

void Moonless::Renderer::Init() {
    RenderCommand::Init();
    Renderer2D::Init();
}

void Moonless::Renderer::OnWindowResize(uint32_t width, uint32_t height) {
    RenderCommand::SetViewport(0, 0, width, height);
}
