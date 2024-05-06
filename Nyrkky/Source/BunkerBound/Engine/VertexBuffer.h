#pragma once

class VertexBuffer
{
private:
	unsigned int _RendererID;

public:
	VertexBuffer(const void* data, unsigned int size, bool dynamic = false);
	~VertexBuffer();

	void Update(const void* data, unsigned int size);


	void Bind() const;
	void Unbind() const;

};





