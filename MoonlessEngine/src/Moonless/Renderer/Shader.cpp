#include "mlpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Moonless {

Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc,fragmentSrc);           
        case RendererAPI::API::None:    ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    }
    ML_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

Shader* Shader::Create(const std::string& filepath)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:    ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return new OpenGLShader(filepath);
    }
    ML_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

}
