#pragma once

#include "imgui/imgui.h"
#include "Core.h"
#include "LayerStack.h"
#include "Log.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "imgui/ImguiLayer.h"

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

        bool OnWindowClose(WindowCloseEvent& e);

        bool OnWindowResize(WindowResizeEvent& e);
        
        
    private:
        std::unique_ptr<Window> m_window;

        ImguiLayer* m_imgui_layer;

        bool m_running = true;

        LayerStack m_layer_stack;

        static Application* m_handle;

        bool m_Minimized = false;
    private:
        
    };

    Application* CreateApplication();
}
