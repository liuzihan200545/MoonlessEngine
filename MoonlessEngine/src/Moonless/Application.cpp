#include "mlpch.h"

#include "Application.h"

#include <GLFW/glfw3.h>

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

#include <GLFW/glfw3.h>

Moonless::Application::Application() {
    m_window = std::unique_ptr<Window>(Window::Create());
}

Moonless::Application::~Application() {
        
}

void Moonless::Application::run() {
    while (m_running)
    {
        /*glClearColor(0.5f,0.5f,0.8f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);*/
        m_window->OnUpdate();
    }
}
