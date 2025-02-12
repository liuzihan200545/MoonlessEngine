#include "mlpch.h"
#include "Renderer.h"

#include "RenderCommand.h"


void Moonless::Renderer::BeginScene() {
    
}

void Moonless::Renderer::EndScene() {
    
}

void Moonless::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}
