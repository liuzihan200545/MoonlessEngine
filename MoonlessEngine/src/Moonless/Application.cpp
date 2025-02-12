#include "mlpch.h"
#include "glad/glad.h"
#include "Application.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

#include "Input.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"


Moonless::Application* Moonless::Application::m_handle = nullptr;

Moonless::Application::Application() {
    ML_CORE_ASSERT(!m_handle,"Application already exists.")
    
    m_handle = this;
    
    m_window.reset(Window::Create());
    m_window->SetEventCallback([this](Event& e)
    {
        this->OnEvent(e);
    });

    m_imgui_layer = new ImguiLayer();
    PushOverlay(m_imgui_layer);

    m_VertexArray.reset(VertexArray::Create());
    
    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.5f,0.5f,0.8f,1.0f,
         0.5f, -0.5f, 0.0f, 0.5f,0.5f,0.8f,1.0f,
         0.0f,  0.5f, 0.0f, 0.5f,0.5f,0.8f,1.0f
    };

    std::shared_ptr<VertexBuffer> vertexBuffer;
    vertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));

    BufferLayout layout = {
        { ShaderDataType::Float3, "position"},
        { ShaderDataType::Float4, "color"}
    };
    vertexBuffer->SetLayout(layout);
    
    unsigned int indices[3] = { 0, 1, 2 };

    std::shared_ptr<IndexBuffer> indexBuffer;
    indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

    m_VertexArray->AddVertexBuffer(vertexBuffer);
    m_VertexArray->SetIndexBuffer(indexBuffer);
    
    std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec3 v_Position;
            out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
                v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";
    std::string fragmentSrc = R"(
			#version 330 core

            in vec4 v_Color;
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = v_Color;
			}
		)";
    m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

    // object2:
    m_SquareVA.reset(VertexArray::Create());

    float squareVertices[3 * 4] = {
        -0.1f, -0.1f, 0.0f,
         0.1f, -0.1f, 0.0f,
         0.1f,  0.1f, 0.0f,
        -0.1f,  0.1f, 0.0f
    };

    std::shared_ptr<VertexBuffer> square_vb;
    square_vb.reset(VertexBuffer::Create(squareVertices,sizeof(squareVertices)));

    square_vb->SetLayout({
            { ShaderDataType::Float3, "a_Position" }
    });
    
    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    
    std::shared_ptr<IndexBuffer> square_ib;
    square_ib.reset(IndexBuffer::Create(squareIndices,sizeof(squareIndices)/sizeof(uint32_t)));

    m_SquareVA->AddVertexBuffer(square_vb);
    m_SquareVA->SetIndexBuffer(square_ib);

    std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);	
			}
		)";

    std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

	m_BlueShader = std::make_shared<Shader>(blueShaderVertexSrc,blueShaderFragmentSrc);
}

Moonless::Application::~Application() {
    
}

void Moonless::Application::run() {
    while (m_running)
    {
        RenderCommand::SetClearColor({0.1f,0.1f,0.1f,1.0f});
    	RenderCommand::Clear();

    	Renderer::BeginScene();

    	m_Shader->Bind();
    	Renderer::Submit(m_VertexArray);
    	
		m_BlueShader->Bind();
		Renderer::Submit(m_SquareVA);
    	
    	Renderer::EndScene();
    	
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



