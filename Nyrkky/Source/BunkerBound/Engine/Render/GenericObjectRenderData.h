#pragma once
#include "RenderBase.h"
#include "../TileTypeList.h"

class GenericObjectRenderData : public RenderBase
{
public:
	GenericObjectRenderData();
	~GenericObjectRenderData();

	void Init(int PosX, int PosY) override;
	bool Activate(int PosX, int PosY) override;

	void SetTexture(size_t texID)
	{
		_texID = texID;
	}

protected:
	void AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex) override;
	void AddIndex(std::vector<unsigned int>& x, float v1, float v2, float v3) override;

	size_t _texID;
};

