#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Moonless
{

    class OpenGLContext : public GraphicsContext{
    public:
        OpenGLContext(GLFWwindow* window);

        void Init() override;
        void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };

}
