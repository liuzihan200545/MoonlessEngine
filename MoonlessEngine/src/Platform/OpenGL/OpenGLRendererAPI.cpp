#include "mlpch.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "glad/glad.h"

namespace Moonless
{

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        ML_PROFILE_FUNCTION();

        glClearColor(color.r, color.g, color.b, color.a);
    }
    void OpenGLRendererAPI::Clear()
    {
        ML_PROFILE_FUNCTION();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
    {
        ML_PROFILE_FUNCTION();

        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::Init() {
        ML_PROFILE_FUNCTION();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
        ML_PROFILE_FUNCTION();

        glViewport(x,y,width,height);
    }
}
