#include "mlpch.h"
#include "WindowsInput.h"
#include "GLFW/glfw3.h"
#include "Moonless/Application.h"

namespace Moonless
{

Input* Input::m_handle = new WindowsInput(); 

bool WindowsInput::IsKeyPressedImpl(int keycode) {
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().GetWindow().GetNativeWindow());

    auto state = glfwGetKey(window,keycode);

    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMouseButtonPressedImpl(int keycode) {
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().GetWindow().GetNativeWindow());

    auto state = glfwGetMouseButton(window,keycode);

    return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::GetMousePositionImpl() {
    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().GetWindow().GetNativeWindow());
    double pos_x,pos_y;
    glfwGetCursorPos(window,&pos_x,&pos_y);

    return std::pair{static_cast<float>(pos_x),static_cast<float>(pos_y)};
}

float WindowsInput::GetMousePosXImpl() {
    return GetMousePositionImpl().first;
}

float WindowsInput::GetMousePosYImpl() {
    return GetMousePositionImpl().second;
}
}


