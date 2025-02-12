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
#include "Renderer/VertexArray.h"

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
        
    private:
        std::unique_ptr<Window> m_window;

        ImguiLayer* m_imgui_layer;

        bool m_running = true;

        LayerStack m_layer_stack;

        static Application* m_handle;
    private:
        std::shared_ptr<Shader> m_Shader;
        std::shared_ptr<VertexArray> m_VertexArray;

        std::shared_ptr<Shader> m_BlueShader;
        std::shared_ptr<VertexArray> m_SquareVA;
    };

    Application* CreateApplication();
}
