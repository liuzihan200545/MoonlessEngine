#include "mlpch.h"
#include "Moonless/Renderer/Shader.h"
#include "Moonless/Renderer/Renderer.h"
#include "Moonless/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Moonless {

std::shared_ptr<Shader> Shader::Create(const std::string& shaerName,const std::string& vertexSrc, const std::string& fragmentSrc) {
    switch (Renderer::GetAPI())
    {
        case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(shaerName,vertexSrc,fragmentSrc);           
        case RendererAPI::API::None:    ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    }
    ML_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:    ML_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(filepath);
    }
    ML_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
}

void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
{
    ML_CORE_ASSERT(!Exists(name), "Shader already exists!");
    m_Shaders[name] = shader;
}

void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
{
    auto& name = shader->GetName();
    Add(name, shader);
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath)
{
    auto shader = Shader::Create(filepath);
    Add(shader);
    return shader;
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
    auto shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
}

std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
{
    ML_CORE_ASSERT(Exists(name), "Shader not found!");
    return m_Shaders[name];
}

bool ShaderLibrary::Exists(const std::string& name) const
{
    return m_Shaders.find(name) != m_Shaders.end();
}


}
