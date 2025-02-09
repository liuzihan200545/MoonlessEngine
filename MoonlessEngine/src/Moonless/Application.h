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

    private:
        std::unique_ptr<Window> m_window;

        bool m_running;

        LayerStack m_layer_stack;
    };

    Application* CreateApplication();
}
