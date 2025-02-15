#include "mlpch.h"
#include "Moonless/Renderer/VertexArray.h"
#include "Moonless/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Moonless
{
    std::shared_ptr<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexArray>();
        }
        ML_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
