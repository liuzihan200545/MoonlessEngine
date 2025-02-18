#pragma once

#include "Moonless.h"
#include "Moonless/Renderer/FrameBuffer.h"

namespace Moonless {

	class EditorLayer : public Layer {
	public:

		EditorLayer();
		~EditorLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnEvent(Event& event) override;
		void OnUpdate(Timestep ts) override;
		void OnImGuiRender() override;
	
	private:
		OrthographicCameraController m_CameraController;

		// Temp

		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

		std::shared_ptr<Texture2D> m_check_board;
		std::shared_ptr<Framebuffer> m_Framebuffer;

		glm::vec2 m_viewprt_size;

		Timestep ts;
	};

}

