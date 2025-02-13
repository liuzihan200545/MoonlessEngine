#include "mlpch.h"
#include "Texture.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Moonless
{

std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path) {
    switch (RendererAPI::GetAPI())
    {
    case RendererAPI::API::OpenGL:
        {
            return std::make_shared<OpenGLTexture2D>(path);
        }
    case RendererAPI::API::None:
        {
            ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!")
        }
    }
}

}
