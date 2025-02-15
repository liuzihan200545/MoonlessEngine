#pragma once

#include <Moonless.h>
#include <memory>

using namespace Moonless;

class SandBox2D : public Moonless::Layer{
public:
    SandBox2D();
    ~SandBox2D() override;
    void OnAttach() override;
    void OnDetach() override;
    void OnEvent(Moonless::Event& event) override;
    void OnUpdate(Moonless::Timestep ts) override;
    void OnImGuiRender() override;
private:
    OrthographicCameraController m_CameraController;

    // Temp
    std::shared_ptr<VertexArray> m_SquareVA;
    std::shared_ptr<Shader> m_FlatColorShader;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

    Timestep ts;
    
};
