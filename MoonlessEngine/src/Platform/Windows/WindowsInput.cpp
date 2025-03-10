#include "mlpch.h"
#include "Platform/Windows/WindowsInput.h"
#include "GLFW/glfw3.h"
#include "Moonless/Core/Application.h"

namespace Moonless
{

std::unique_ptr<Input> Input::m_handle = std::make_unique<WindowsInput>();

bool WindowsInput::IsKeyPressedImpl(int keycode) {
    ML_PROFILE_FUNCTION();

    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().GetWindow().GetNativeWindow());

    auto state = glfwGetKey(window,keycode);

    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMouseButtonPressedImpl(int keycode) {
    ML_PROFILE_FUNCTION();

    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().GetWindow().GetNativeWindow());

    auto state = glfwGetMouseButton(window,keycode);

    return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::GetMousePositionImpl() {
    ML_PROFILE_FUNCTION();

    GLFWwindow* window = static_cast<GLFWwindow*>(Application::get().GetWindow().GetNativeWindow());
    double pos_x,pos_y;
    glfwGetCursorPos(window,&pos_x,&pos_y);

    return std::pair{static_cast<float>(pos_x),static_cast<float>(pos_y)};
}

float WindowsInput::GetMousePosXImpl() {
    ML_PROFILE_FUNCTION();

    return GetMousePositionImpl().first;
}

float WindowsInput::GetMousePosYImpl() {
    ML_PROFILE_FUNCTION();

    return GetMousePositionImpl().second;
}
}


