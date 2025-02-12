#include "mlpch.h"
#include "Buffer.h"

#include "Core.h"
#include "Log.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Moonless {
VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:    ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
    }
    ML_CORE_ASSERT(false, "Unknown RendererAPI!")
    return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:    ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return new OpenGLIndexBuffer(indices, size);
    }
    ML_CORE_ASSERT(false, "Unknown RendererAPI!")
    return nullptr;
}
}
