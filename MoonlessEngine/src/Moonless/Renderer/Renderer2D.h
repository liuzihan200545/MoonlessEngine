#pragma once

#include <Moonless.h>
#include <Moonless/Renderer/Texture.h>

namespace Moonless
{

class Renderer2D
{
public:
    static void Init();
    static void Shutdown();
    static void BeginScene(const OrthographicCamera& camera);
    static void EndScene();
    static void Flush();
    // Primitives
    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

    static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
    static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

    static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
    static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);

    static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4&  = glm::vec4(1.0f));
    static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));

    struct Statistics
    {
        uint32_t DrawCalls = 0;
        uint32_t QuadCount = 0;
        uint32_t GetTotalVertexCount() { return QuadCount * 4; }
        uint32_t GetTotalIndexCount() { return QuadCount * 6; }
    };
    static void ResetStats();
    static Statistics GetStats();
private:
    static void FlushAndReset();
};

// Stats

}
