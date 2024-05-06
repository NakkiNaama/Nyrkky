#pragma once

#include <glad/glad.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"


class Renderer {
public:
	void Draw(const VertexArray* va, const IndexBuffer* ib) const;
	void Clear() const;

};







