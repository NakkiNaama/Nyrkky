#pragma once
#include "RenderBase.h"
#include "../../Basics.h"

class CharacterRenderData : public RenderBase
{
public:
	CharacterRenderData(int ScreenX, int ScreenY, std::string texturePath);
	~CharacterRenderData();
	void Init(int PosX, int PosY) override;
	bool Activate(int PosX, int PosY) override;

	void SetDirection(Direction direction)
	{
		_lastMovement = direction;
	}

protected:
	void AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex) override;
	void AddIndex(std::vector<unsigned int>& x, float v1, float v2, float v3) override;
	std::unique_ptr<Texture> texture;
	Direction _lastMovement = Direction::Backwards;
	std::string _textureLoc;

};



