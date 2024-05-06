#pragma once
#include "Renderer.h"
#include "../GameData.h"

void Renderer::Draw(const VertexArray* va, const IndexBuffer* ib) const
{
    GameData::GetShader()->Bind();
    va->Bind();
    ib->Bind();

    glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}
