#include "mlpch.h"
#include "Buffer.h"

#include "Core.h"
#include "Log.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Moonless {
std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:    ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLVertexBuffer>(vertices, size);
    }
    ML_CORE_ASSERT(false, "Unknown RendererAPI!")
    return nullptr;
}

std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:    ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLIndexBuffer>(indices, size);
    }
    ML_CORE_ASSERT(false, "Unknown RendererAPI!")
    return nullptr;
}
}
