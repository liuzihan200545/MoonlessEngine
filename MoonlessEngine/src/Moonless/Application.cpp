#include "mlpch.h"

#include "Application.h"

#include <GLFW/glfw3.h>

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

#include <GLFW/glfw3.h>

Moonless::Application::Application() {
    m_window = std::unique_ptr<Window>(Window::Create());
    m_window->SetEventCallback([this](Event& e)
    {
        this->OnEvent(e);
    });
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

void Moonless::Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e)->bool
    {
        this->m_running = false;
        return true;
    });

    ML_CORE_TRACE(e);
}

