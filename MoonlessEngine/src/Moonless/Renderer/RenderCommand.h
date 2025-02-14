#pragma once

#include "Renderer/RendererAPI.h"

namespace Moonless
{

class RenderCommand
{
    public:
        static void SetClearColor(const glm::vec4& color)
        {
            s_RendererAPI->SetClearColor(color);
        }
        static void Clear()
        {
            s_RendererAPI->Clear();
        }
        static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
        {
            s_RendererAPI->DrawIndexed(vertexArray);
        }
        static void Init() {
            s_RendererAPI->Init();
        }
        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_RendererAPI->SetViewport(x, y, width, height);
        }
    private:
        static std::unique_ptr<RendererAPI> s_RendererAPI;
    };

}
