#pragma once

#include "Shader.h"
#include "Renderer/RendererAPI.h"
#include "Renderer/OrthographicCamera.h"

namespace Moonless {

    class Renderer
    {
        
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();
        static void Submit(const std::shared_ptr<Shader>& shader,const std::shared_ptr<VertexArray>& vertexArray);
        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData
        {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
    };

}