#pragma once
#include "Renderer.h"

class Texture
{
public:
	Texture(std::string path, bool flipTexture = false);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind();



private:
	uint32_t _rendererID;
	std::string _filePath;
	unsigned char* _localBuffer;
	int _width;
	int _height;
	int _BPP;

};




