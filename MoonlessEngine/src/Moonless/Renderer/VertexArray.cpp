#include "mlpch.h"
#include "VertexArray.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Moonless
{
    VertexArray* VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:    ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
        case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
        }
        ML_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
}
