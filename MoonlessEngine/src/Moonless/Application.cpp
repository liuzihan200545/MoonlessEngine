#include "mlpch.h"
#include "glad/glad.h"
#include "Application.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

#include "Input.h"


Moonless::Application* Moonless::Application::m_handle = nullptr;

Moonless::Application::Application() {
    ML_CORE_ASSERT(!m_handle,"Application already exists.")
    
    m_handle = this;
    
    m_window = std::unique_ptr<Window>(Window::Create());
    m_window->SetEventCallback([this](Event& e)
    {
        this->OnEvent(e);
    });

    m_imgui_layer = new ImguiLayer();
    PushOverlay(m_imgui_layer);

    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);
    
    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    
    unsigned int indices[3] = { 0, 1, 2 };

    m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

    std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";
    std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";
    m_shader.reset(new Shader(vertexSrc, fragmentSrc));
}

Moonless::Application::~Application() {
    
}

void Moonless::Application::run() {
    while (m_running)
    {
        glClearColor(0.1f,0.1f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_shader->Bind();
        glBindVertexArray(m_VertexArray);
        
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount() , GL_UNSIGNED_INT, nullptr);

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


