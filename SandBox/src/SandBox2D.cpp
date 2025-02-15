#include "SandBox2D.h"

#include <glm/ext/matrix_transform.hpp>

#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>

SandBox2D::SandBox2D() : Layer("Sandbox2D"), m_CameraController(1080.0f / 720.0f){
    
}

SandBox2D::~SandBox2D() {
    
}

void SandBox2D::OnAttach() {
    m_SquareVA = VertexArray::Create();
    
    float squareVertices[3 * 4] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };

    std::shared_ptr<VertexBuffer> m_SquareVB = VertexBuffer::Create(squareVertices,sizeof(squareVertices));
    m_SquareVB->SetLayout({
        {ShaderDataType::Float3,"a_Position"}
    });

    m_SquareVA->AddVertexBuffer(m_SquareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

    std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices,sizeof(squareIndices)/sizeof(uint32_t));

    m_SquareVA->SetIndexBuffer(squareIB);

    m_FlatColorShader = Shader::Create("assets/shaders/flatColor.glsl");
}

void SandBox2D::OnDetach() {
    
}

void SandBox2D::OnEvent(Moonless::Event& event) {
    m_CameraController.OnEvent(event);
}

void SandBox2D::OnUpdate(Moonless::Timestep ts) {
    this->ts = ts;
    m_CameraController.OnUpdate(ts);
    RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    RenderCommand::Clear();

    Renderer::BeginScene(m_CameraController.GetCamera());
    
    std::dynamic_pointer_cast<OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

    Renderer::Submit(m_FlatColorShader,m_SquareVA,glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    Renderer::EndScene();
}

void SandBox2D::OnImGuiRender() {
    ImGui::Begin("SandBox2D");

    ImGui::ColorEdit4("edit color",glm::value_ptr(m_SquareColor));

    ImGui::Text(fmt::format("frame time {} ms", ts.GetMilliseconds()).c_str());
    
    ImGui::End();
}
