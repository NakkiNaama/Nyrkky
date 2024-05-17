#pragma once
#include "RenderBase.h"
#include "../Renderer.h"
#include "../Shader.h"
#include <memory>
#include "../../MapLoader.h"

class MapRenderData : public RenderBase
{
public:
	MapRenderData(int layer, int ScreenX, int ScreenY, int gridSize, int tileSize);
	~MapRenderData();

	void Init(int PosX, int PosY) override;
	bool Activate(int PosX, int PosY) override;
	void Update(int ScreenX, int ScreenY, int gridSize, int tileSize);

	// contains verticies in the map
	std::vector<float> positions;

protected:
	int windowX;
	int windowY;
	int GridSize;
	float TileSize;
	int _layer = 0;


	void AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex) override;
	void AddIndex(std::vector<unsigned int>& x, float v1, float v2, float v3) override;


};

