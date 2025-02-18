#pragma once

#include <Moonless/Renderer/FrameBuffer.h>

namespace Moonless
{   

class OpenGLFramebuffer : public Framebuffer {
    
public:
    OpenGLFramebuffer(const FramebufferSpecification& spec);
    ~OpenGLFramebuffer();

    void Invalidate();

    void Bind() override;
    void Unbind() override;

    uint32_t GetColorAttachmentRendererID() const override;

    const FramebufferSpecification& GetSpecification() const override;

private:
    uint32_t m_RendererID;
    uint32_t m_ColorAttachment, m_DepthAttachment;
    FramebufferSpecification m_Specification;
};

}
