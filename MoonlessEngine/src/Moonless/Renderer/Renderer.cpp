#include "mlpch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

Moonless::Renderer::SceneData* Moonless::Renderer::m_SceneData = new Renderer::SceneData;

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
