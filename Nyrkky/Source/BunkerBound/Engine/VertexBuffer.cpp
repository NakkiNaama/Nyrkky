#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size, bool dynamic) {
    glGenBuffers(1, &_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, _RendererID);
    if(dynamic)  glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    else         glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::Update(const void* data, unsigned int size) {
    //glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}


VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _RendererID);
}

void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
