#include "mlpch.h"
#include "glad/glad.h"
#include "OpenGLVertexArray.h"

Moonless::OpenGLVertexArray::OpenGLVertexArray() {
    glCreateVertexArrays(1, &m_RendererID);
}

Moonless::OpenGLVertexArray::~OpenGLVertexArray() {
    glDeleteVertexArrays(1, &m_RendererID);
}

void Moonless::OpenGLVertexArray::Bind() const {
    glBindVertexArray(m_RendererID);
}

void Moonless::OpenGLVertexArray::Unbind() const {
    glBindVertexArray(0);
}

void Moonless::OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
    ML_CORE_ASSERT(vertexBuffer->GetLayout().get_elements().size(),"The layout of vertex buffer is empty!");

    this->Bind();
    vertexBuffer->Bind();
    
    const auto& layout = vertexBuffer->GetLayout();
    for (const auto& element : layout)
    {
        glEnableVertexAttribArray(m_VertexBufferIndex);
        glVertexAttribPointer(m_VertexBufferIndex,
            element.GetComponentCount(),
            ShaderDataTypeToOpenGLBaseType(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            layout.getStride(),
            reinterpret_cast<const void *>(element.offset));
        m_VertexBufferIndex++;
    }
    
    m_vertex_buffers.push_back(vertexBuffer);
}

void Moonless::OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
    this->Bind();
    indexBuffer->Bind();
    m_index_buffers = indexBuffer;
}
