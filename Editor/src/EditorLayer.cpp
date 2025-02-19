#include "mlpch.h"
#include "EditorLayer.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

namespace Moonless
{
EditorLayer::EditorLayer() : Layer("Sandbox2D"), m_CameraController(1080.0f / 720.0f){
    
}

EditorLayer::~EditorLayer() {
    
}

void EditorLayer::OnAttach() {
    ML_PROFILE_FUNCTION();
    m_check_board = Texture2D::Create("assets/textures/Checkerboard.png");

    FramebufferSpecification fbSpec;
    fbSpec.Width = 1080;
    fbSpec.Height = 720;
    m_Framebuffer = Framebuffer::Create(fbSpec);
}

void EditorLayer::OnDetach() {
    
   
}

void EditorLayer::OnEvent(Event& event) {
    m_CameraController.OnEvent(event);
}

void EditorLayer::OnUpdate(Timestep ts) {
    ML_PROFILE_FUNCTION();
    Renderer2D::ResetStats();
    this->ts = ts;
	
	if (m_ViewportFocused)
		m_CameraController.OnUpdate(ts);
    
    {
        ML_PROFILE_SCOPE("Render Prepare");
        m_Framebuffer->Bind();
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        RenderCommand::Clear();
    }
    
    {
        ML_PROFILE_SCOPE("Render Draw");
        Renderer2D::BeginScene(m_CameraController.GetCamera());

        Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
        Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
        Renderer2D::DrawQuad({0.0f,0.0f,-0.1},{1.0f,1.0f},m_check_board, 2.0f);
        Renderer2D::DrawRotatedQuad({0.0f,0.0,0.2f},{1.0f,1.0f},45.0f,m_check_board, 3.0f);
        Renderer2D::EndScene();

        Renderer2D::BeginScene(m_CameraController.GetCamera());
        for (float y = -5.0f; y < 5.0f; y += 0.5f)
        {
            for (float x = -5.0f; x < 5.0f; x += 0.5f)
            {
                glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
                Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
            }
        }
        Renderer2D::EndScene();
        m_Framebuffer->Unbind();
    }
}

void EditorLayer::OnImGuiRender() {
    // Note: Switch this to true to enable dockspace
	static bool dockingEnabled = true;
	if (dockingEnabled)
	{
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
				if (ImGui::MenuItem("Exit")) Application::get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();

		ImGui::Begin("ViewPort");

		m_ViewportFocused = ImGui::IsWindowFocused();
		m_ViewportHovered = ImGui::IsWindowHovered();
		Application::get().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);
		
		uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImVec2 viewPortSize = ImGui::GetContentRegionAvail();
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });

		if(m_viewprt_size != *((glm::vec2*)(&viewPortSize)))
		{
			m_Framebuffer->Resize(viewPortSize.x,viewPortSize.y);
			m_viewprt_size = {viewPortSize.x,viewPortSize.y};
			m_CameraController.OnResize(viewPortSize.x, viewPortSize.y);
		}
		
		ML_CORE_WARN("{},{}",viewPortSize.x,viewPortSize.y);
		ImGui::Image((void*)textureID, viewPortSize,{0,1},{1,0});
		ImGui::End();


		ImGui::End();
	}
}

}
