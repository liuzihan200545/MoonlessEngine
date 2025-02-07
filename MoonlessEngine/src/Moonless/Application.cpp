#include "mlpch.h"

#include "Application.h"

#include <GLFW/glfw3.h>

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

#include <GLFW/glfw3.h>

Moonless::Application::Application() {
    
}

Moonless::Application::~Application() {
    
}

void Moonless::Application::run() {
    WindowResizeEvent e(1080,720);
    AppUpdateEvent e1{};
    ML_CORE_ERROR(e);
    ML_CORE_TRACE(e1);

    glfwInit();

    auto window = glfwCreateWindow(1080,720,"Hello Moonless Engine",nullptr,nullptr);
}
