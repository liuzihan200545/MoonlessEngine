#include "mlpch.h"
#include <Moonless/Renderer/FrameBuffer.h>
#include <Moonless/Renderer/Renderer.h>
#include <Platform/OpenGL/OpenGLFramebuffer.h>
#include "Moonless/Renderer/RendererAPI.h"

namespace Moonless  
{

std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) {
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:    ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLFramebuffer>(spec);
    }
        ML_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}

