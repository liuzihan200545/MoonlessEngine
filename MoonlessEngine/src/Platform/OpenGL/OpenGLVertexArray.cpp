#include "mlpch.h"
#include "glad/glad.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

Moonless::OpenGLVertexArray::OpenGLVertexArray() {
    ML_PROFILE_FUNCTION();

    glCreateVertexArrays(1, &m_RendererID);
}

Moonless::OpenGLVertexArray::~OpenGLVertexArray() {
    ML_PROFILE_FUNCTION();

    glDeleteVertexArrays(1, &m_RendererID);
}

void Moonless::OpenGLVertexArray::Bind() const {
    ML_PROFILE_FUNCTION();

    glBindVertexArray(m_RendererID);
}

void Moonless::OpenGLVertexArray::Unbind() const {
    ML_PROFILE_FUNCTION();

    glBindVertexArray(0);
}

void Moonless::OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
    ML_PROFILE_FUNCTION();

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
    ML_PROFILE_FUNCTION();

    this->Bind();
    indexBuffer->Bind();
    m_index_buffers = indexBuffer;
}
