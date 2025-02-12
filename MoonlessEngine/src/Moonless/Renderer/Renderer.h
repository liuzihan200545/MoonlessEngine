#pragma once

#include "Renderer/RendererAPI.h"

namespace Moonless {

    class Renderer
    {
        
    public:
        static void BeginScene();
        static void EndScene();
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);
        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
    };

}