#pragma once
#include "../../Basics.h"
#include "../Renderer.h"
#include "../Shader.h"
#include <memory>

//#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <vector>

#include "../Renderer.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"

#include "../VertexArray.h"

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

class RenderBase
{
public:
	//RenderBase(int ScreenX, int ScreenY, Shader* shader);
	//~RenderBase();

	virtual void Init(int PosX, int PosY) = 0;
	virtual bool Activate(int PosX, int PosY) = 0;

	virtual void AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex) = 0;
	virtual void AddIndex(std::vector<unsigned int>& x, float v1, float v2, float v3) = 0;
	
	VertexArray* GetVA() const { return _va; }
	VertexBuffer* GetVB() const { return _vb; }
	IndexBuffer* GetIB() const { return _ib; }
	VertexBufferLayout* GetLayout() const { return _layout; }

protected:
	void Clean();
	bool _initialized = false;

	//int windowX;
	//int windowY;

	std::vector<Texture*> _textures;
	Shader* _shader;

	VertexArray* _va;
	VertexBuffer* _vb;
	IndexBuffer* _ib;
	VertexBufferLayout* _layout;


};

