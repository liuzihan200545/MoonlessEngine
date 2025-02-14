#pragma once

#include "Moonless/Core/TimeStep.h"
#include "Moonless/Events/Event.h"
#include "Moonless/Renderer/OrthographicCamera.h"

#include "Moonless/Events/MouseEvent.h"
#include "Moonless/Events/ApplicationEvent.h"

#include <glm/glm.hpp>

namespace Moonless
{

    class OrthographicCameraController {
    public:
        OrthographicCameraController(float m_AspectRatio,bool rotation = false);
        void OnEvent(Event& e);
        void OnUpdate(Timestep ts);
        OrthographicCamera& GetCamera() { return m_Camera; }
        const OrthographicCamera& GetCamera() const { return m_Camera; }
    private:
        bool OnMouseScrolled(MouseScrolledEvent& e);
        bool OnWindowResized(WindowResizeEvent& e);
    private:
        float m_AspectRatio;
        float m_ZoomLevel = 1.0f;
        OrthographicCamera m_Camera;

        bool m_Rotation;

        glm::vec3 m_CameraPosition = {0.0f,0.0f,0.0f};
        float m_CameraRotation = 0.0f;;
        float m_CameraTranslationSpeed = 5.0f, m_CameraRotationSpeed = 180.0f;
    };

}
