#pragma once
#include <glad/glad.h>
#include "Moonless/Renderer/Texture.h"
#include <string>

namespace Moonless
{

    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(uint32_t width, uint32_t height);
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D() override;

        uint32_t GetHeight() const override {
            return m_Height;
        }
        uint32_t GetWidth() const override {
            return m_Width;
        }
        uint32_t GetRendererID() const override {
            return m_RendererID;
        }
        void Bind(uint32_t slot) const override;
        void SetData(void* data, uint32_t size) override;
        bool operator==(const Texture& other) const override
        {
            return m_RendererID == ((OpenGLTexture2D&)other).m_RendererID;
        }
    private:
        std::string m_Path;
        uint32_t m_Width,m_Height;
        uint32_t m_RendererID;
        GLenum m_InternalFormat, m_DataFormat;
    };

}
