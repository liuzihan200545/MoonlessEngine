#include "mlpch.h"
#include "Moonless/Core/OrthographicCameraController.h"
#include "Moonless/Core/Log.h"
#include "Moonless/Core/Input.h"
#include "Moonless/Core/KeyCodes.h"

namespace Moonless
{

OrthographicCameraController::OrthographicCameraController(float m_AspectRatio, bool rotation)
    : m_AspectRatio(m_AspectRatio) ,
      m_Camera(OrthographicCamera(-m_AspectRatio * m_ZoomLevel ,m_AspectRatio * m_ZoomLevel,-1.0f * m_ZoomLevel,1.0f * m_ZoomLevel)),
      m_Rotation(rotation){}

void OrthographicCameraController::OnEvent(Event& e) {
    ML_PROFILE_FUNCTION();

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& e)
    {
        return this->OnMouseScrolled(e);
    });
    dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e)
    {
        return this->OnWindowResized(e);    
    });
}

void OrthographicCameraController::OnUpdate(Timestep ts) {
    ML_PROFILE_FUNCTION();

    if (Input::IsKeyPressed(ML_KEY_A))
    {
        m_CameraPosition.x -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        m_CameraPosition.y -= sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    }
    else if (Input::IsKeyPressed(ML_KEY_D))
    {
        m_CameraPosition.x += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        m_CameraPosition.y += sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    }

    if (Input::IsKeyPressed(ML_KEY_W))
    {
        m_CameraPosition.x -= -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        m_CameraPosition.y -= cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    }
    else if (Input::IsKeyPressed(ML_KEY_S))
    {
        m_CameraPosition.x += -sin(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
        m_CameraPosition.y += cos(glm::radians(m_CameraRotation)) * m_CameraTranslationSpeed * ts;
    }

    if (m_Rotation)
    {
        if (Input::IsKeyPressed(ML_KEY_Q))
            m_CameraRotation += m_CameraRotationSpeed * ts;
        if (Input::IsKeyPressed(ML_KEY_E))
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        m_Camera.SetRotation(m_CameraRotation);
    }

    m_Camera.SetPosition(m_CameraPosition);
    
    m_CameraTranslationSpeed = m_ZoomLevel;
}

bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
    ML_PROFILE_FUNCTION();

    m_ZoomLevel -= e.GetYOffset() * 0.25f;
    m_ZoomLevel = std::max(m_ZoomLevel,0.25f);
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel ,m_AspectRatio * m_ZoomLevel,-1.0f * m_ZoomLevel,1.0f * m_ZoomLevel);
    return false;
}

bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) {
    ML_PROFILE_FUNCTION();

    m_AspectRatio = static_cast<float>(e.GetWidth()) / static_cast<float>(e.GetHeight());
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel ,m_AspectRatio * m_ZoomLevel,-1.0f * m_ZoomLevel,1.0f * m_ZoomLevel);
    return false;
}

}
