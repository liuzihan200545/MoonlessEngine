#include <Moonless.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Renderer/Texture.h>
#include <Platform/OpenGL/OpenGLTexture2D.h>

using namespace Moonless;

class ExampleLayer : public Layer {
public:
    ExampleLayer() :
	Layer("Example") ,
	m_camera(-1.08f,1.08f,-0.72f,0.72f),
	m_cam_pos({0.0f,0.0f,0.0f}),
	time(static_cast<float>(glfwGetTime()))
	{
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
	    m_Shader.reset(Shader::Create(vertexSrc,fragmentSrc));

	    // object2:
	    m_SquareVA.reset(VertexArray::Create());

	    float squareVertices[5 * 4] = {
	    	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	    };

	    std::shared_ptr<VertexBuffer> square_vb;
	    square_vb.reset(VertexBuffer::Create(squareVertices,sizeof(squareVertices)));

	    square_vb->SetLayout({
	            { ShaderDataType::Float3, "a_Position" },
	    		{ ShaderDataType::Float2, "a_uv"}
	    });
	    
	    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	    
	    std::shared_ptr<IndexBuffer> square_ib;
	    square_ib.reset(IndexBuffer::Create(squareIndices,sizeof(squareIndices)/sizeof(uint32_t)));

	    m_SquareVA->AddVertexBuffer(square_vb);
	    m_SquareVA->SetIndexBuffer(square_ib);

    	

	    std::string blueShaderVertexSrc = R"(
				#version 330 core
			
				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec2 a_TexCoord;
				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;
				out vec2 v_TexCoord;
				void main()
				{
					v_TexCoord = a_TexCoord;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
				}
			)";

	    std::string blueShaderFragmentSrc = R"(
				#version 330 core
			
				layout(location = 0) out vec4 color;
				in vec2 v_TexCoord;
				
				uniform sampler2D u_Texture;
				void main()
				{
					color = texture(u_Texture, v_TexCoord);
				}
			)";
		
		m_BlueShader.reset(Shader::Create(blueShaderVertexSrc,blueShaderFragmentSrc));
    }

    void OnUpdate() override {
		Timestep delta_time = static_cast<float>(glfwGetTime()) - time;

    	time = static_cast<float>(glfwGetTime());

    	ML_CLIENT_INFO("{} ms",delta_time.GetMilliseconds());
    	
    	if(Input::IsKeyPressed(ML_KEY_A))
    	{
    		m_cam_pos.x -= m_cam_speed * delta_time;
    	}
    	else if(Input::IsKeyPressed(ML_KEY_D))
    	{
    		m_cam_pos.x += m_cam_speed * delta_time;
    	}
    	if(Input::IsKeyPressed(ML_KEY_W))
    	{
    		m_cam_pos.y += m_cam_speed * delta_time;
    	}
    	else if(Input::IsKeyPressed(ML_KEY_S))
    	{
    		m_cam_pos.y -= m_cam_speed * delta_time;
    	}

    	if(Input::IsKeyPressed(ML_KEY_LEFT))
    	{
    		m_cam_rot += m_cam_rot_speed * delta_time;
    		ML_CLIENT_INFO("key left clicked!");
    	}
    	else if (Input::IsKeyPressed(ML_KEY_RIGHT))
    	{
    		m_cam_rot -= m_cam_rot_speed * delta_time;
    		ML_CLIENT_INFO("key right clicked!");
    	}

    	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    	
        RenderCommand::SetClearColor({0.1f,0.1f,0.1f,1.0f});
        RenderCommand::Clear();

        m_camera.SetPosition(m_cam_pos);
        m_camera.SetRotation(m_cam_rot);
    	
        Renderer::BeginScene(m_camera);

    	Renderer::Submit(m_Shader,m_VertexArray);

    	m_texture = OpenGLTexture2D::Create("assets/textures/Checkerboard.png");
		//m_texture->Bind(0);
    	std::dynamic_pointer_cast<OpenGLShader>(m_BlueShader)->Bind();
    	std::dynamic_pointer_cast<OpenGLShader>(m_BlueShader)->UploadUniformInt("u_Texture",0);
    	
    	for (int y = 0; y < 20; y++)
    	{
    		for (int x = 0; x < 20; x++)
    		{
    			m_texture->Bind();
    			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
    			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
    			Renderer::Submit(m_BlueShader, m_SquareVA, transform);
    		}
    	}
    	
        Renderer::EndScene();
    }

    void OnEvent(Event& event) override {
		
    }

    void OnImGuiRender() override {
        ImGui::Begin("hello");
    	ImVec2 button_size(100, 50);
    	if (ImGui::Button("Click Me", button_size)) {
    		m_cam_pos = glm::vec3(0.0f,0.0f,0.0f);
    	}
    	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<VertexArray> m_VertexArray;

    std::shared_ptr<Shader> m_BlueShader;
    std::shared_ptr<VertexArray> m_SquareVA;

	std::shared_ptr<Texture2D> m_texture;

	glm::vec3 m_SquareColor = { 0.5f, 0.5f, 0.8f };

    OrthographicCamera m_camera;

	glm::vec3 m_cam_pos;
	float m_cam_rot = 0;
	float m_cam_speed = 1.0f;
	float m_cam_rot_speed = 0.1f;

	Timestep time;
};

class Sandbox : public Moonless::Application {
public:
    Sandbox() {
        ExampleLayer* layer = new ExampleLayer();
        PushLayer(layer);
    }

    ~Sandbox() override {
        
    }
};

Moonless::Application* Moonless::CreateApplication() {
    return new Sandbox();
}
