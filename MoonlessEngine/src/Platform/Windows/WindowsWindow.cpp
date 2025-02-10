#include "mlpch.h"
#include "glad/glad.h"
#include "WindowsWindow.h"
#include "Log.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

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
        m_data.EventCallback = callback_fn;
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
            ML_CORE_ASSERT(success,"Couldn't Initialize GLFW")

            glfwSetErrorCallback([](int error_code, const char* description)
            {
                ML_CORE_ERROR("GLFW ERROR: {0} with {1}",description,error_code);
            });

            m_is_glfw_initialized = true;
        }

        m_window = glfwCreateWindow(m_data.Width,m_data.Height,m_data.Title.c_str(),nullptr,nullptr);
        
        glfwMakeContextCurrent(m_window);

        int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

        ML_CORE_ASSERT(status,"Couldn't Initialize Glad")

        glfwSetWindowUserPointer(m_window,&m_data);

        SetVSync(true);

        // set call back functions
        glfwSetWindowSizeCallback(m_window,[](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.Width = width;
            data.Height = height;
            WindowResizeEvent e(width,height); 
            data.EventCallback(e);
        });
        
        glfwSetWindowCloseCallback(m_window,[](GLFWwindow* window)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            WindowCloseEvent e{}; 
            data.EventCallback(e);
        });

        glfwSetKeyCallback(m_window,[](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
                case GLFW_PRESS:{
                        KeyPressedEvent event(key,0);
                        data.EventCallback(event);
                        break;    
                }
                case GLFW_RELEASE:{
                        KeyReleasedEvent event(key);
                        data.EventCallback(event);
                        break;
                }
                case GLFW_REPEAT:{
                        KeyPressedEvent event(key,1);
                        data.EventCallback(event);
                        break;
                }
                default:{
                        
                }
            }
        });

        glfwSetMouseButtonCallback(m_window,[](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action)
            {
                case GLFW_PRESS:{
                        MouseButtonPressedEvent event(button);
                        data.EventCallback(event);
                        break;    
                }
                case GLFW_RELEASE:{
                        MouseButtonReleasedEvent event(button);
                        data.EventCallback(event);
                        break;
                }
                default:{
                        
                }
            }
        });

        glfwSetScrollCallback(m_window,[](GLFWwindow* window, double xoffset, double yoffset)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            
            MouseScrolledEvent e(static_cast<float>(xoffset),static_cast<float>(yoffset)); 
            data.EventCallback(e);
        });

        glfwSetCursorPosCallback(m_window,[](GLFWwindow* window, double xpos, double ypos)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            
            MouseMovedEvent e(static_cast<float>(xpos),static_cast<float>(ypos)); 
            data.EventCallback(e);
        });

        glfwSetCharCallback(m_window,[](GLFWwindow* window, unsigned int codepoint)
        {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            KeyTypedEvent e(codepoint);
            data.EventCallback(e);
        });
    }

    void WindowsWindow::ShutDown() {
        glfwDestroyWindow(m_window);
    }
}
