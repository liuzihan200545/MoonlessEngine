#pragma once

#include "imgui/imgui.h"
#include "glad/glad.h"
#include "Core.h"
#include "LayerStack.h"
#include "Log.h"
#include "Window.h"
#include "imgui/ImguiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"

namespace Moonless
{
    class Application {
    public:
        ML_DLL_API  Application();

        virtual ML_DLL_API  ~Application();

        void ML_DLL_API run();

        void ML_DLL_API OnEvent(Event& e);

        void ML_DLL_API PushLayer(Layer* layer);

        void ML_DLL_API PushOverlay(Layer* layer);

        Window& GetWindow() { return *m_window; }

        static Application& get() { return *m_handle; }

        static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
            switch (type)
            {
            case ShaderDataType::Float:    return GL_FLOAT;
            case ShaderDataType::Float2:   return GL_FLOAT;
            case ShaderDataType::Float3:   return GL_FLOAT;
            case ShaderDataType::Float4:   return GL_FLOAT;
            case ShaderDataType::Mat3:     return GL_FLOAT;
            case ShaderDataType::Mat4:     return GL_FLOAT;
            case ShaderDataType::Int:      return GL_INT;
            case ShaderDataType::Int2:     return GL_INT;
            case ShaderDataType::Int3:     return GL_INT;
            case ShaderDataType::Int4:     return GL_INT;
            case ShaderDataType::Bool:     return GL_BOOL;
            }
		
            ML_CORE_ASSERT(false, "Unknown ShaderDataType!")
            return 0;
        }
        
    private:
        std::unique_ptr<Window> m_window;

        ImguiLayer* m_imgui_layer;

        bool m_running = true;

        LayerStack m_layer_stack;

        static Application* m_handle;
    private:
        unsigned int m_VertexArray;
        std::unique_ptr<Shader> m_shader;

        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
    };

    Application* CreateApplication();
}
