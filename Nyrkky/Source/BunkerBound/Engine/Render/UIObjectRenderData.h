#pragma once
#include "RenderBase.h"
#include "../../MapLoader.h"

class UIObjectRenderData : public RenderBase
{
public:
	UIObjectRenderData(uint32_t arrayID, uint32_t texture, float x, float y, float xSize, float ySize, bool interactable, std::shared_ptr<UIObjectRenderData> highlight = nullptr, int ID = 0);
	~UIObjectRenderData();

	void Init(float x, float y, float xSize, float ySize);
	void Update();

	void Init(int PosX, int PosY) override;
	bool Activate(int PosX, int PosY) override;
	bool Updater();


	bool IsInterable() const { return _interactable; }

	float xStart;
	float yStart;
	float xEnd;
	float yEnd;

	void SetTekstuuri(size_t x)
	{
		tekstuuriID = x;
	}
	void SetHighlight(std::shared_ptr<UIObjectRenderData> highlight)
	{
		_highlight = highlight;
	}
	//const std::shared_ptr<TileRenderData> GetRenderData() const { return _tileRenderData; }
	const std::shared_ptr<UIObjectRenderData> GetHighlight() const { return _highlight; }

	int _ID = 0;

protected:
	void AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex) override;
	void AddIndex(std::vector<unsigned int>& x, float v1, float v2, float v3) override;
	bool _interactable = false;

	//std::shared_ptr<TileRenderData> _tileRenderData;
	size_t tekstuuriID = 0;
	size_t _textureArray = 0;
	std::shared_ptr<UIObjectRenderData> _highlight = nullptr;



};

