#include "mlpch.h"
#include "glad/glad.h"
#include "ImguiLayer.h"
#include "imgui.h"
#include <Platform/OpenGL/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <Application.h>
#include <Events/Event.h>
#include <Events/ApplicationEvent.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>

Moonless::ImguiLayer::ImguiLayer() : Layer("Imgui Layer") {
    
}

Moonless::ImguiLayer::~ImguiLayer() {
    
}

void Moonless::ImguiLayer::OnEvent(Event& event) {
    ImGuiIO& io = ImGui::GetIO();

    // KeyBoard Events
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<KeyPressedEvent>([&io](KeyPressedEvent& e)
    {
        io.KeysDown[e.GetKeyCode()] = true;

        io.KeyAlt = (e.GetKeyCode() == GLFW_KEY_LEFT_ALT) || (e.GetKeyCode() == GLFW_KEY_RIGHT_ALT);
        io.KeyCtrl = (e.GetKeyCode() == GLFW_KEY_LEFT_CONTROL) || (e.GetKeyCode() == GLFW_KEY_RIGHT_CONTROL);
        io.KeyShift = (e.GetKeyCode() == GLFW_KEY_LEFT_SHIFT) || (e.GetKeyCode() == GLFW_KEY_RIGHT_SHIFT);
        io.KeySuper = (e.GetKeyCode() == GLFW_KEY_LEFT_SUPER) || (e.GetKeyCode() == GLFW_KEY_RIGHT_SUPER);

        return false;
    });
    
    dispatcher.Dispatch<KeyReleasedEvent>([&io](KeyReleasedEvent& e)
    {
        io.KeysDown[e.GetKeyCode()] = false;

        if (e.GetKeyCode() == GLFW_KEY_LEFT_ALT || e.GetKeyCode() == GLFW_KEY_RIGHT_ALT) io.KeyAlt = false;
        if (e.GetKeyCode() == GLFW_KEY_LEFT_CONTROL || e.GetKeyCode() == GLFW_KEY_RIGHT_CONTROL) io.KeyCtrl = false;
        if (e.GetKeyCode() == GLFW_KEY_LEFT_SHIFT || e.GetKeyCode() == GLFW_KEY_RIGHT_SHIFT) io.KeyShift = false;
        if (e.GetKeyCode() == GLFW_KEY_LEFT_SUPER || e.GetKeyCode() == GLFW_KEY_RIGHT_SUPER) io.KeySuper = false;
        
        return false;
    });

    dispatcher.Dispatch<KeyTypedEvent>([&io](KeyTypedEvent& e)
    {
        int keycode = e.GetKeyCode();
        if(keycode > 0 && keycode < 0x10000)
        {
            io.AddInputCharacter(keycode);
        }
        return false;
    });

    // Mouse Events :
    dispatcher.Dispatch<MouseButtonPressedEvent>([&io](MouseButtonPressedEvent& e)
    {
        io.MouseDown[e.GetMouseButton()] = true;
        return false;
    });

    dispatcher.Dispatch<MouseButtonReleasedEvent>([&io](MouseButtonReleasedEvent& e)
    {
        io.MouseDown[e.GetMouseButton()] = false;
        return false;
    });

    dispatcher.Dispatch<MouseMovedEvent>([&io](MouseMovedEvent& e)
    {
        io.MousePos = ImVec2(e.GetX(),e.GetY());
        return false;
    });

    dispatcher.Dispatch<MouseScrolledEvent>([&io](MouseScrolledEvent& e)
    {
        io.MouseWheel += e.GetYOffset() * io.DisplayFramebufferScale.y;
        io.MouseWheelH += e.GetXOffset() * io.DisplayFramebufferScale.x;
        return false;
    });

    // Application Event
    dispatcher.Dispatch<WindowResizeEvent>([&io](WindowResizeEvent& e)
    {
        // TODO: view port size
        io.DisplaySize = ImVec2(e.GetWidth(),e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f,1.0f);
        glViewport(0,0,e.GetWidth(),e.GetHeight());
        return false;
    });
}

void Moonless::ImguiLayer::OnUpdate() {
    ImGuiIO& io = ImGui::GetIO();

    auto& app = Application::get();
    
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(),app.GetWindow().GetHeight());

    float time = static_cast<float>(glfwGetTime());

    io.DeltaTime = m_time > 0.0f ? time - m_time : 1.0f / 60.0f;
    m_time = time;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    static bool show = true;
    ImGui::ShowDemoWindow(&show);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Moonless::ImguiLayer::OnAttach() {
    ImGui::CreateContext();

    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();

    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
    
    io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
    io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
    io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
    io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
    io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
    io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
    io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
    io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
    
    ImGui_ImplOpenGL3_Init("#version 410");
}

void Moonless::ImguiLayer::OnDetach() {
        
}
