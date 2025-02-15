#include <Moonless.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Renderer/Texture.h>
#include <Platform/OpenGL/OpenGLTexture2D.h>
#include <Moonless/Core/OrthographicCameraController.h>
// Entry Point
#include "SandBox2D.h"
#include "Moonless/Core/EntryPoint.h"
#include "imgui/imgui.h"

using namespace Moonless;

class ExampleLayer : public Layer {
public:
    ExampleLayer() :
	Layer("Example") , m_CameraController(1080.0f/720.0f,true),
	time(static_cast<float>(glfwGetTime()))
	{
	    float vertices[3 * 7] = {
	        -0.5f, -0.5f, 0.0f, 0.5f,0.5f,0.8f,1.0f,
	         0.5f, -0.5f, 0.0f, 0.5f,0.5f,0.8f,1.0f,
	         0.0f,  0.5f, 0.0f, 0.5f,0.5f,0.8f,1.0f
	    };

	    std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

	    BufferLayout layout = {
	        { ShaderDataType::Float3, "position"},
	        { ShaderDataType::Float4, "color"}
	    };
	    vertexBuffer->SetLayout(layout);
	    
	    unsigned int indices[3] = { 0, 1, 2 };

	    std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	    
	    std::string vertexSrc = R"(
				#version 330 core
				
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec4 a_Color;
				out vec3 v_Position;
	            out vec4 v_Color;
				uniform mat4 u_ViewProjection;

				void main()
				{
					v_Position = a_Position;
	                v_Color = a_Color;
					gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

	    // object2:
	    m_SquareVA = VertexArray::Create();

	    float squareVertices[5 * 4] = {
	    	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	    };

	    std::shared_ptr<VertexBuffer> square_vb = VertexBuffer::Create(squareVertices, sizeof(squareVertices));

	    square_vb->SetLayout({
	            { ShaderDataType::Float3, "a_Position" },
	    		{ ShaderDataType::Float2, "a_uv"}
	    });
	    
	    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	    
	    std::shared_ptr<IndexBuffer> square_ib = IndexBuffer::Create(squareIndices,sizeof(squareIndices)/sizeof(uint32_t));

	    m_SquareVA->AddVertexBuffer(square_vb);
	    m_SquareVA->SetIndexBuffer(square_ib);

	    std::string flatShaderVertexSrc = R"(
				#version 330 core
			
				layout(location = 0) in vec3 a_Position;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec3 v_Position;

				void main()
				{
					v_Position = a_Position;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
				}
			)";

	    std::string flatShaderFragSrc = R"(
				#version 330 core
			
				layout(location = 0) out vec4 color;

				in vec3 v_Position;
				
				uniform vec3 u_Color;

				void main()
				{
					color = vec4(u_Color, 1.0);
				}
			)";
		m_BlueShader = std::make_shared<OpenGLShader>("assets/shaders/flatColor.glsl");
    	auto m_textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		dynamic_pointer_cast<OpenGLShader>(m_textureShader)->UploadUniformInt("u_Texture",0);

    	m_texture = OpenGLTexture2D::Create("assets/textures/Checkerboard.png");
    	m_ChernoLogoTexture = OpenGLTexture2D::Create("assets/textures/ChernoLogo.png");
	}

    void OnUpdate(Timestep ts) override {
    	ML_CLIENT_INFO("{} ms",ts.GetMilliseconds());
    	
    	m_CameraController.OnUpdate(ts);

    	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    	
        RenderCommand::SetClearColor({0.1f,0.1f,0.1f,1.0f});
        RenderCommand::Clear();
        Renderer::BeginScene(m_CameraController.GetCamera());
		
    	std::dynamic_pointer_cast<OpenGLShader>(m_BlueShader)->Bind();
    	std::dynamic_pointer_cast<OpenGLShader>(m_BlueShader)->UploadUniformFloat3("u_Color",m_SquareColor);
    	
    	for (int y = 0; y < 20; y++)
    	{
    		for (int x = 0; x < 20; x++)
    		{
    			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
    			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
    			Renderer::Submit(m_BlueShader, m_SquareVA, transform);
    		}
    	}

    	m_texture->Bind();
    	Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    	m_ChernoLogoTexture->Bind();
    	Renderer::Submit(m_ShaderLibrary.Get("Texture"), m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    	
        Renderer::EndScene();
    }

    void OnEvent(Event& event) override {
		m_CameraController.OnEvent(event);
    }

    void OnImGuiRender() override {
        ImGui::Begin("hello");
    	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    std::shared_ptr<Shader> m_BlueShader;
    std::shared_ptr<VertexArray> m_SquareVA;	

	std::shared_ptr<Texture2D> m_texture;
	std::shared_ptr<Texture2D> m_ChernoLogoTexture;

	ShaderLibrary m_ShaderLibrary;

	glm::vec3 m_SquareColor = { 0.5f, 0.5f, 0.8f };

    OrthographicCameraController m_CameraController;

	Timestep time;
};

class Sandbox : public Moonless::Application {
public:
    Sandbox() {
        /*ExampleLayer* layer = new ExampleLayer();
        PushLayer(layer);*/

    	SandBox2D* layer = new SandBox2D();
    	PushLayer(layer);
    }

    ~Sandbox() override {
        
    }
};

Moonless::Application* Moonless::CreateApplication() {
    return new Sandbox();
}
