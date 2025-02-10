#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Log.h"
#include "Window.h"

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

        bool m_running = true;

        LayerStack m_layer_stack;

        static Application* m_handle;
    };

    Application* CreateApplication();
}
