#pragma once

class IndexBuffer
{
private:
	unsigned int _RendererID = 0;
	unsigned int _count = 0;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int GetCount() const {
		return _count;
	}


};





