#include "VertexArray.h"
#include "Renderer.h"


VertexArray::VertexArray() {
	glGenVertexArrays(1, &_rendererID);
}
VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_rendererID);
}


void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		#pragma warning(disable : 4312)
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		#pragma warning(disable : 4312)
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(_rendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
