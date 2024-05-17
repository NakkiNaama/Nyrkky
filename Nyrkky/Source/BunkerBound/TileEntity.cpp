#include "TileEntity.h"
#include "GameData.h"

TileEntity::TileEntity(std::string name, Event event, int posx, int posy, std::vector<uint32_t> textures, bool collision)
	: _name(name), _textures(textures)
{
	_event.Type = event.Type;
	_event.Effect = event.Effect;

	_collision = collision;

}

void TileEntity::Tick(float DeltaTime)
{

}

TileEntity::~TileEntity()
{
}

void TileEntity::ActivateEvent()
{
	switch (_event.Type)
	{
	case EventNone: 
		std::cout << "no event on object!" << std::endl;
		break;

	case EventDoor: 
		std::cout << "interacted with door!" << std::endl;
		if (_event.State == 0)
		{
			_event.State = 1;
			if (_textures.size() > 1) Render->SetTexture(_textures[1]);
			_collision = false;
		}
		else
		{
			_event.State = 0;
			Render->SetTexture(_textures[0]);
			_collision = true;
		}
		break;

	case EventChest: 
		_event.Type = EventNone;
		if (_textures.size() > 1) Render->SetTexture(_textures[1]);

		break;

	case EventTeleport:
		Render->SetTexture(_textures[0]);

		if (GameData::GetMaps().size() > _event.Effect)
		{
			GameData::ChangeMap(_event.Effect);
			return;
		}
		std::cerr << "Event Teleport failed!" << std::endl;
		break;
	default:
		std::cout << "interacted with error!" << std::endl;
		break;
	}

}


void TileEntity::RenderEntity()
{
	if (Render != nullptr)
	{
		auto c = Render.get();
		if (c->GetVA() != nullptr && c->GetIB() != nullptr)
		{
			if (c->Activate(PosX, PosY))
			{
				GameData::GetRenderer()->Draw(c->GetVA(), c->GetIB());
			}
			else std::cout << "object render activate failed!" << std::endl;
		}
		else std::cout << "object render failed! nullptr!" << std::endl;
	}
}


