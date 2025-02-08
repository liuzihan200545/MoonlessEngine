#include "mlpch.h"
#include "WindowsWindow.h"

#include "Log.h"

namespace Moonless
{

    static bool m_is_glfw_initialized = false;

    Window* Window::Create(const WindowProps& props) {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props) {
        Init(props);
    }

    WindowsWindow::~WindowsWindow() {
        ShutDown();
    }

    void WindowsWindow::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_window);
    }

    void WindowsWindow::SetEventCallback(const EventCallbackFn& callback_fn) {
        
    }

    void WindowsWindow::SetVSync(bool enabled) {
        if(enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }

        m_data.VSync = enabled;
    }

    void WindowsWindow::Init(const WindowProps& props) {
        m_data.Title = props.Title;
        m_data.Width = props.Width;
        m_data.Height = props.Height;

        ML_CORE_INFO("Creating Window {0}({1},{2})",props.Title,props.Width,props.Height);

        if(!m_is_glfw_initialized)
        {
            int success = glfwInit();
            ML_CORE_ASSERT(success,"Couldn't Initialize GLFW");

            m_is_glfw_initialized = false;
        }

        m_window = glfwCreateWindow(m_data.Width,m_data.Height,m_data.Title.c_str(),nullptr,nullptr);
        
        glfwMakeContextCurrent(m_window);

        glfwSetWindowUserPointer(m_window,&m_data);

        SetVSync(true);
    }

    void WindowsWindow::ShutDown() {
        glfwDestroyWindow(m_window);
    }
}
