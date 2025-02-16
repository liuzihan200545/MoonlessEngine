#include "SandBox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include "mlpch.h"

SandBox2D::SandBox2D() : Layer("Sandbox2D"), m_CameraController(1080.0f / 720.0f){
    
}

SandBox2D::~SandBox2D() {
    
}

void SandBox2D::OnAttach() {
    m_check_board = Texture2D::Create("assets/textures/Checkerboard.png");
}

void SandBox2D::OnDetach() {
    
}

void SandBox2D::OnEvent(Moonless::Event& event) {
    m_CameraController.OnEvent(event);
}

void SandBox2D::OnUpdate(Moonless::Timestep ts) {
    ML_PROFILE_FUNCTION();

    ML_CORE_ERROR("FRAME TIME:{}",ts.GetMilliseconds());
    
    this->ts = ts;
    {
        ML_PROFILE_SCOPE("CameraController OnUpdate");
        m_CameraController.OnUpdate(ts);
    }
    
    {
        ML_PROFILE_SCOPE("Render Prepare");
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();
    }
    
    {
        ML_PROFILE_SCOPE("Render Draw");
        Renderer2D::BeginScene(m_CameraController.GetCamera());

        Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
        Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_check_board);
    
        Renderer2D::EndScene();
    }
    
}

void SandBox2D::OnImGuiRender() {
    ImGui::Begin("SandBox2D");

    ImGui::ColorEdit4("edit color",glm::value_ptr(m_SquareColor));

    ImGui::Text(fmt::format("frame time {} ms", ts.GetMilliseconds()).c_str());
    
    ImGui::End();
}
