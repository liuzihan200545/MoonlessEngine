#pragma once

#include "Moonless/Core/Window.h"
#include <GLFW/glfw3.h>
#include "Moonless/Renderer/GraphicsContext.h"

namespace Moonless
{
    class WindowsWindow : public Window{
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        unsigned int GetWidth() const override {
            return m_data.Width;
        }
        unsigned int GetHeight() const override {
            return m_data.Height;
        }

        void SetEventCallback(const EventCallbackFn& callback_fn) override;
        void SetVSync(bool enabled) override;
        bool IsVSync() const override {
            return m_data.VSync;
        }

        void* GetNativeWindow() override {
            return m_window;
        }
    private:
        virtual void Init(const WindowProps& props);
        virtual void ShutDown();
    private:
        GLFWwindow* m_window;

        std::unique_ptr<GraphicsContext> m_context;
        
        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };

        WindowData m_data;
    };
}
