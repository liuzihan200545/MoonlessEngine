#include "mlpch.h"
#include <glad/glad.h>
#include "Platform/OpenGL/OpenGLBuffer.h"
// VertexBuffer

Moonless::OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size) {
    ML_PROFILE_FUNCTION();

    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Moonless::OpenGLVertexBuffer::~OpenGLVertexBuffer() {
    ML_PROFILE_FUNCTION();

    glDeleteBuffers(1, &m_RendererID);
}

void Moonless::OpenGLVertexBuffer::Bind() const {
    ML_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void Moonless::OpenGLVertexBuffer::Unbind() const {
    ML_PROFILE_FUNCTION();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// IndexBuffer

Moonless::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count) {
    ML_PROFILE_FUNCTION();

    glCreateBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

Moonless::OpenGLIndexBuffer::~OpenGLIndexBuffer() {
    ML_PROFILE_FUNCTION();

    glDeleteBuffers(1, &m_RendererID);
}

void Moonless::OpenGLIndexBuffer::Bind() const {
    ML_PROFILE_FUNCTION();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void Moonless::OpenGLIndexBuffer::Unbind() const {
    ML_PROFILE_FUNCTION();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
