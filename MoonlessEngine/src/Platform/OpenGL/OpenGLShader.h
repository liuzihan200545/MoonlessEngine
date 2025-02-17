#pragma once

#include <Moonless/Renderer/Shader.h>
#include <glm/glm.hpp>

namespace Moonless
{

    class OpenGLShader : public Shader {
    public:
        using GLenum = unsigned int;

        OpenGLShader(const std::string& filepath);
        OpenGLShader(const std::string& name,const std::string& vertexSrc, const std::string& fragmentSrc);

        ~OpenGLShader()override;

        const std::string& GetName() const override { return m_Name; }

        void Bind() const override;

        void Unbind() const override;

        void UploadUniformInt(const std::string& name, int value) override;
        void UploadUniformFloat(const std::string& name, float value) override;
        void UploadUniformFloat2(const std::string& name, const glm::vec2& value) override;
        void UploadUniformFloat3(const std::string& name, const glm::vec3& value) override;
        void UploadUniformFloat4(const std::string& name, const glm::vec4& value) override;
        void UploadUniformMat3(const std::string& name, const glm::mat3& matrix) override;
        void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) override;

        void UploadUniformIntArray(const std::string& name, int* values, uint32_t count) override;

    private:
        std::string ReadFile(const std::string& filepath);
        std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
        void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);
        
    private:
        uint32_t m_RendererID;
        std::string m_Name;
    };

}
