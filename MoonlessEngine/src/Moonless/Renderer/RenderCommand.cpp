#include "mlpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Moonless
{

    std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = std::make_unique<OpenGLRendererAPI>();

}
