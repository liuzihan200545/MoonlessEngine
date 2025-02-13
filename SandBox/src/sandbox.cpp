#include <Moonless.h>
#include <GLFW/glfw3.h>

using namespace Moonless;

class ExampleLayer : public Layer {
public:
    ExampleLayer() : Layer("Example") ,  m_camera(-1.08f,1.08f,-0.72f,0.72f)
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

				uniform mat4 u_ViewProjection;

				void main()
				{
					v_Position = a_Position;
					gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

    void OnUpdate() override {
        RenderCommand::SetClearColor({0.1f,0.1f,0.1f,1.0f});
        RenderCommand::Clear();

        m_camera.SetPosition({0.0f,0.0f,0.0f});
        m_camera.SetRotation(0.0f);
    	
        Renderer::BeginScene(m_camera);
    	
        Renderer::Submit(m_Shader,m_VertexArray);
        Renderer::Submit(m_BlueShader,m_SquareVA);
    	
        Renderer::EndScene();
    }

    void OnEvent(Moonless::Event& event) override {
        
    }

    void OnImGuiRender() override {
        /*ImGui::Begin("hello");
        ImGui::End();*/
    }

    std::shared_ptr<Shader> m_Shader;
    std::shared_ptr<VertexArray> m_VertexArray;

    std::shared_ptr<Shader> m_BlueShader;
    std::shared_ptr<VertexArray> m_SquareVA;

    OrthographicCamera m_camera;
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
