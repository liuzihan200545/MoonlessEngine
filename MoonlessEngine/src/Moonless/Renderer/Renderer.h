#pragma once

#include "Shader.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/OrthographicCamera.h"
#include <memory>

namespace Moonless {

    class Renderer
    {
        
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();
        static void Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray,const glm::mat4& transform = glm::mat4(1.0f));
        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
        static void Init();
        static void OnWindowResize(uint32_t width, uint32_t height);

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static std::unique_ptr<SceneData> m_SceneData;
    };

}