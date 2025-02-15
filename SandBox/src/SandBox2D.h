#pragma once

#include <Moonless.h>
#include <memory>

#include "Moonless/Renderer/Texture.h"

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

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

    std::shared_ptr<Texture2D> m_check_board;

    Timestep ts;

    struct ProfileResult
    {
        const char* Name;
        float Time;
    };
    std::vector<ProfileResult> m_ProfileResults;
    
};
