#pragma once
#include "Entity.h"
#include "Engine/Render/Text.h"

class TextEntity : public Entity
{
public:
	TextEntity(int posx, int posy, int fontSize);

	~TextEntity();
	std::unique_ptr<Text> text = nullptr;

	void RenderEntity()
	{
		text->RenderText("noobi", PosX, PosY, view);
	}

	glm::mat4 view = glm::mat4(1.0f);
protected:

};

