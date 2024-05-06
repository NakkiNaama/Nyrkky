#pragma once
#include "Entity.h"
#include "Engine/Render/CharacterRenderData.h"

enum ECharacter
{
	Arisu,
	Emily
};

class CharacterEntity : public Entity
{
public:
	CharacterEntity(std::string name, ECharacter id, Event event, int posx, int posy, std::string texturePath);

	CharacterEntity(const CharacterEntity& other)
	{
		ID = other.ID;
		PosX = other.PosX;
		PosY = other.PosY;
		_name = other._name;
		_texturePath = other._texturePath;
		_event = other._event;
		//_eventType = other._eventType;
		//_data = other._data;
		//std::cout << "data size: " << _data.size() << std::endl;

		//_collision = other._collision;
		Render = std::make_unique<CharacterRenderData>(PosX, PosY, _texturePath);
		Render->Init(PosX, PosY);
		//std::cout << "copy finished" << std::endl;
	}

	std::shared_ptr<CharacterEntity> clone() const
	{
		return std::make_shared<CharacterEntity>(*this);
	}

	void RenderEntity() override;

	void Move(Direction direction, int x, int y);
	void SetPosition(int x, int y);
	Direction GetLastMovementDirection()
	{
		return _lastMovement;
	}

	virtual void Tick(float DeltaTime) override;
	virtual void ActivateEvent() override;

	virtual EventType GetEventType() override
	{
		return _event.Type;
	}

	Direction currentDir = Direction::DirNone;

	std::unique_ptr<CharacterRenderData> Render;

	void MoveCharacter(Direction direction);

	float _moveTimer = 0;

	inline std::string GetName() const
	{
		return _name;
	}

	ECharacter ID;

protected:
	Direction _lastMovement = Direction::Backwards;
	std::string _name = "Nameless";
	std::string _texturePath;


};



