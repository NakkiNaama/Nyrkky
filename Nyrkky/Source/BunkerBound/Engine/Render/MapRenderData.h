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

	// contains types of tiles in the game
	std::vector<std::shared_ptr<TileRenderData>> _tileTypes;
	// contains invidual tiles in the game
	std::vector<TileRenderData> _tiles;

	// contains vertexes in the map
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

