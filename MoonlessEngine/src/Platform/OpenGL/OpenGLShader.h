#pragma once

#include <Moonless/Renderer/Shader.h>

namespace Moonless
{

    class OpenGLShader : public Shader {
    public:
        using GLenum = unsigned int;

        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);

        ~OpenGLShader()override;

        void Bind() const override;

        void Unbind() const override;

        void UploadUniformInt(const std::string& name, int value);
        void UploadUniformFloat(const std::string& name, float value);
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

    private:
        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
        
    private:
        uint32_t m_RendererID;
    };

}
