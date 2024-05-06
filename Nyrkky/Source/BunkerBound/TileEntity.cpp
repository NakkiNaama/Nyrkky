#include "TileEntity.h"
#include "GameData.h"

TileEntity::TileEntity(std::string name, Event event, int posx, int posy, std::vector<std::shared_ptr<TileRenderData>> data, bool collision)
	: _name(name)
{
	//std::cout << "eff: " << _effect << std::endl;
	_event.Type = event.Type;
	_event.Effect = event.Effect;

	_collision = collision;
	for (auto& d : data)
	{
		_data.push_back(d);
	}

	if (_data.size() > 0)
	{
		PosX = posx;
		PosY = posy;
		Render = std::make_shared<GenericObjectRenderData>(_data.front());

		Render->Init(PosX, PosY);
	}
	else std::cerr << "TileEntity had empty data parameter" << std::endl;

	//Initalize(shader, posx, posy, eventType, data, collision);
}

void TileEntity::Tick(float DeltaTime)
{

}

/*
void TileEntity::Initalize(Shader* shader, int posx, int posy, EventType eventType, std::vector<std::shared_ptr<TileRenderData>> data, bool collision)
{
	_collision = collision;
	for (auto& d : data)
	{
		_data.push_back(d);
	}
	if (_data.size() > 0)
	{
		_eventType = eventType;
		PosX = posx;
		PosY = posy;
		Render = std::make_shared<GenericObjectRenderer>(_data.front());
		usedShader = shader;
		Render->Init(usedShader, PosX, PosY);
	}
	else std::cerr << "TileEntity had empty data parameter" << std::endl;
}
*/

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
			Render->SetData(_data[1]);
			_collision = false;
		}
		else
		{
			_event.State = 0;
			Render->SetData(_data[0]);
			_collision = true;
		}
		break;

	case EventChest: 
		_event.Type = EventNone;
		Render->SetData(_data[1]);
		/*
		GameData::GetStory()->SetNode(0);
		GameData::SetDialogVisible(true);
		*/
		break;

	case EventTeleport:
		Render->SetData(_data[0]);
		//std::cout << _effect << " ddd" << std::endl;
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
	//else std::cout << "entity render failed! nullptr!" << std::endl;
}


