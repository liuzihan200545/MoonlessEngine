#include "mlpch.h"
#include "Application.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
#include "Input.h"
#include "KeyCodes.h"
#include "Events/KeyEvent.h"

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

    m_imgui_layer = new ImguiLayer();
    PushOverlay(m_imgui_layer);
}

Moonless::Application::~Application() {
    ML_CORE_INFO("Moonless Engine exit.");
}

void Moonless::Application::run() {
    while (m_running)
    {
        if(Input::IsKeyPressed(ML_KEY_ESCAPE))
        {
            this->m_running = false;
        }
        
        for (Layer* layer:m_layer_stack)
        {
            layer->OnUpdate();
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

    dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& e)->bool
    {
        this->m_running = false;
        return true;
    });

    //TODO: Fix viewport resize when window is resized.
    /*dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& e)->bool
    {
        glViewport(0,0,m_window->GetWidth(),m_window->GetHeight());
        return false;
    });*/

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



