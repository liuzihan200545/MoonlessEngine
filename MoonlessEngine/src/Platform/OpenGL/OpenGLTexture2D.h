#pragma once

#include "Renderer/Texture.h"
#include <string>

namespace Moonless
{

    class OpenGLTexture2D : public Texture2D {
    public:
        OpenGLTexture2D(const std::string& path);
        ~OpenGLTexture2D() override;

        uint32_t GetHeight() const override {
            return m_Height;
        }
        uint32_t GetWidth() const override {
            return m_Width;
        }
        void Bind(uint32_t slot) const override;
    private:
        std::string m_Path;
        uint32_t m_Width,m_Height;
        uint32_t m_RendererID;
    };

}
