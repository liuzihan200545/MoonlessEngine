#include "mlpch.h"
#include "glad/glad.h"
#include "OpenGLContext.h"
#include "Log.h"
#include <GLFW/glfw3.h>

Moonless::OpenGLContext::OpenGLContext(GLFWwindow* window) : m_WindowHandle(window) {
    ML_CORE_ASSERT(m_WindowHandle, "Window handle is null!")
}

void Moonless::OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    ML_CORE_ASSERT(status, "Failed to initialize Glad!");
}

void Moonless::OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);   
}
