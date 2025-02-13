#include "mlpch.h"
#include "Shader.h"
#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Moonless {

Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
    switch (RendererAPI::GetAPI())
    {
        case RendererAPI::API::OpenGL:
        {
            return new OpenGLShader(vertexSrc,fragmentSrc);           
        }
        
    }
}

}
