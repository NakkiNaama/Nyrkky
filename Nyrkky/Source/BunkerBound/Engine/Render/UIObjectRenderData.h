#pragma once
#include "RenderBase.h"
#include "../../MapLoader.h"

class UIObjectRenderData : public RenderBase
{
public:
	UIObjectRenderData(uint32_t arrayID, uint32_t texture, float x, float y, float xSize, float ySize, bool interactable, std::shared_ptr<UIObjectRenderData> highlight = nullptr, int ID = 0);
	~UIObjectRenderData();

	void Init(float x, float y, float xSize, float ySize);

	void Init(int PosX, int PosY) override;
	bool Activate(int PosX, int PosY) override;
	bool Update();


	float xStart;
	float yStart;
	float xEnd;
	float yEnd;

	void SetTexture(uint32_t x)
	{
		_textureID = x;
	}
	void SetHighlight(std::shared_ptr<UIObjectRenderData> highlight)
	{
		_highlight = highlight;
	}

	const std::shared_ptr<UIObjectRenderData> GetHighlight() const { return _highlight; }

	int _ID = 0;

protected:
	void AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex) override;
	void AddIndex(std::vector<unsigned int>& x, int v1, int v2, int v3) override;


	uint32_t _textureID = 0;
	uint32_t _textureArray = 0;
	std::shared_ptr<UIObjectRenderData> _highlight = nullptr;



};

