#pragma once
#include "RenderBase.h"
#include "../TileTypeList.h"

class GenericObjectRenderData : public RenderBase
{
public:
	GenericObjectRenderData(std::shared_ptr<TileRenderData> data);
	~GenericObjectRenderData();

	void Init(int PosX, int PosY) override;
	bool Activate(int PosX, int PosY) override;

	void SetData(std::shared_ptr<TileRenderData> data)
	{
		_data = data;
	}

protected:
	void AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex) override;
	void AddIndex(std::vector<unsigned int>& x, float v1, float v2, float v3) override;

	std::shared_ptr<TileRenderData> _data;

};

