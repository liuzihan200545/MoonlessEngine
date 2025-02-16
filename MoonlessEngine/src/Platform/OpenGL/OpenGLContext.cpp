#include "mlpch.h"
#include <GLFW/glfw3.h>
#include "glad/glad.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Moonless/Core/Log.h"
#include "Moonless/Core/Core.h"
#include <gl/GL.h>

Moonless::OpenGLContext::OpenGLContext(GLFWwindow* window) : m_WindowHandle(window) {
    ML_PROFILE_FUNCTION();

    ML_CORE_ASSERT(m_WindowHandle, "Window handle is null!")
}

void Moonless::OpenGLContext::Init() {
    ML_PROFILE_FUNCTION();

    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ML_CORE_ASSERT(status, "Failed to initialize Glad!")

    ML_CORE_INFO("OpenGL Info:");
    ML_CORE_INFO("Vendor: {0}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    ML_CORE_INFO("Renderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
    ML_CORE_INFO("Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}   

void Moonless::OpenGLContext::SwapBuffers() {
    ML_PROFILE_FUNCTION();

    glfwSwapBuffers(m_WindowHandle);   
}
