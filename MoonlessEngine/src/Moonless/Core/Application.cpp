#include "mlpch.h"
#include "Moonless/Core/Application.h"

#include "Moonless/Events/Event.h"
#include "Moonless/Events/ApplicationEvent.h"
#include "Moonless/Core/Log.h"
#include "Moonless/Core/Input.h"
#include "Moonless/Core/KeyCodes.h"
#include "Moonless/Renderer/Renderer.h"
#include <GLFW/glfw3.h>

Moonless::Application* Moonless::Application::m_handle = nullptr;

Moonless::Application::Application(){
    ML_CORE_ASSERT(!m_handle,"Application already exists.")
    
    m_handle = this;
    
    m_window.reset(Window::Create());
    m_window->SetEventCallback([this](Event& e)
    {
        this->OnEvent(e);
    });

    m_window->SetVSync(true);

    Renderer::Init();

    m_imgui_layer = new ImguiLayer();
    PushOverlay(m_imgui_layer);
}

Moonless::Application::~Application() {
    ML_CORE_INFO("Moonless Engine exit.");
}

void Moonless::Application::run() {
    while (m_running)
    {
        Timestep ts = static_cast<float>(glfwGetTime()) - time;

        time = static_cast<float>(glfwGetTime());
        
        if(Input::IsKeyPressed(ML_KEY_ESCAPE))
        {
            this->m_running = false;
        }
        
        if(!m_Minimized)
        {
            for (Layer* layer:m_layer_stack)
            {
                layer->OnUpdate(ts);
            }
        }

        m_imgui_layer->Begin();

        for(Layer* layer : m_layer_stack)
        {
            layer->OnImGuiRender();
        }
        
        m_imgui_layer->End();
        
        m_window->OnUpdate();
    }
}

void Moonless::Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);

    dispatcher.Dispatch<WindowCloseEvent>([&](WindowCloseEvent& e)->bool
    {
        return this->OnWindowClose(e);
    });

    dispatcher.Dispatch<WindowResizeEvent>([&](WindowResizeEvent& e)->bool
    {
        return this->OnWindowResize(e);
    });

    for(auto it = m_layer_stack.rbegin();it!=m_layer_stack.rend();++it)
    {
        (*it)->OnEvent(e);
        if(e.Handled)
        {
            break;
        }
    }

    ML_CORE_TRACE(e);
}

void Moonless::Application::PushLayer(Layer* layer) {
    m_layer_stack.PushLayer(layer);
    layer->OnAttach();
}

void Moonless::Application::PushOverlay(Layer* layer) {
    m_layer_stack.PushOverlay(layer);
    layer->OnAttach();
}

bool Moonless::Application::OnWindowClose(WindowCloseEvent& e) {
    this->m_running = false;
    return true;
}

bool Moonless::Application::OnWindowResize(WindowResizeEvent& e) {
    if (e.GetWidth() == 0 || e.GetHeight() == 0)
    {
        m_Minimized = true;
        return false;
    }
    m_Minimized = false;
    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
    return false;
}



