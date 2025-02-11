#include "mlpch.h"

#include "ImguiLayer.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <Application.h>

#include <GLFW/glfw3.h>

Moonless::ImguiLayer::ImguiLayer() : Layer("Imgui Layer") {
    
}

Moonless::ImguiLayer::~ImguiLayer() {
    
}

void Moonless::ImguiLayer::OnAttach() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    Application& app = Application::get();
    GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");

}

void Moonless::ImguiLayer::OnDetach() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Moonless::ImguiLayer::OnImGuiRender() {
    static bool show = true;
    ImGui::ShowDemoWindow(&show);
}

void Moonless::ImguiLayer::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Moonless::ImguiLayer::End() {
    ImGuiIO& io = ImGui::GetIO();
    Application& app = Application::get();
    io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}
