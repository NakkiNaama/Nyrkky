#include "CharacterEntity.h"
#include <iostream>
#include "GameData.h"

CharacterEntity::CharacterEntity(std::string name, ECharacter id, Event event, int posx, int posy, std::string texturePath)
{
	_name = name;
	_event = event;
	ID = id;
	_texturePath = texturePath;
	Render = std::make_unique<CharacterRenderData>(posx, posy, texturePath); // "../Nyrkky/Resources/Textures/hahmo.png"

	Render->Init(PosX, PosY);

	PosX = posx;
	PosY = posy;
	//Render->UpdatePosition(PosX, PosY);

}

void CharacterEntity::Tick(float DeltaTime)
{
	_moveTimer += DeltaTime;

	if (_moveTimer > 0.1)
	{
		_moveTimer = 0;
		

		switch (currentDir)
		{
		case DirNone:
			break;
		case Forward: MoveCharacter(Direction::Forward);
			break;
		case Right: MoveCharacter(Direction::Right);
			break;
		case Backwards: MoveCharacter(Direction::Backwards);
			break;
		case Left: MoveCharacter(Direction::Left);
			break;

		}
	}
}

void CharacterEntity::ActivateEvent()
{
	switch (_event.Type)
	{
	case EventNone:
		std::cout << "no event on object!" << std::endl;
		break;

	case EventTalk:

		GameData::GetStory()->SetNode(0);
		GameData::SetDialogVisible(true);

		break;


	default:
		std::cout << "interacted with error (character)!" << std::endl;
		break;
	}
}

void CharacterEntity::Move(Direction direction, int x, int y)
{
	_lastMovement = direction;
	PosX += x;
	PosY += y;
}

void CharacterEntity::MoveCharacter(Direction direction) {
	int newX, newY;
	int x = 0, y = 0;
	int mapSize = GameData::GetMap()->GetGridSize();
	GetPosition(newX, newY);

	AddDirectionToCoordinate(direction, x, y);
	newX += x;
	newY += y;

	if (newX >= 0 && newY >= 0 && newX < mapSize && newY <= mapSize)
	{
		int index = newY * GameData::GetMap()->GetGridSize() + newX;

		if (GameData::GetMap()->_tiles.size() > index)
		{
			Tile* tile = &GameData::GetMap()->_tiles[index];
			bool blocked = false;
			if (tile != nullptr && !tile->IsSolid())
			{
				std::shared_ptr<TileEntity> entity = GameData::GetMap()->GetTileEntity(newX, newY);
				
				for (auto &c : GameData::GetMap()->_characterEntities)
				{
					int cx, cy;
					c->GetPosition(cx, cy);
					if (cx == newX && cy == newY)
					{
						blocked = true;
					}
				}
				if (!blocked)
				{
					if (entity == nullptr || !entity->GetCollision())
					{
						Move(direction, x, y);
					}
					else blocked = true;
				}
			}
			if(blocked) Move(direction, 0, 0);;
		}
	}
}

void CharacterEntity::SetPosition(int x, int y)
{
	PosX = x;
	PosY = y;
}


void CharacterEntity::RenderEntity()
{
	auto c = Render.get();
	if (c->GetVA() != nullptr && c->GetIB() != nullptr)
	{
		c->SetDirection(_lastMovement);
		if (c->Activate(PosX, PosY))
		{
			GameData::GetRenderer()->Draw(c->GetVA(), c->GetIB());
		}
		else std::cout << "character render activate failed!" << std::endl;
	}
	else std::cout << "character render failed! nullptr!" << std::endl;
}