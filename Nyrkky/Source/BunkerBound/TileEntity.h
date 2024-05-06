#pragma once
#include "Entity.h"
#include "Engine/Render/GenericObjectRenderData.h"
#include "Engine/TileTypeList.h"



class TileEntity : public Entity
{
public:
	TileEntity(std::string name, Event event, int posx, int posy, std::vector<std::shared_ptr<TileRenderData>> data, bool collision);
	~TileEntity();

	TileEntity(const TileEntity& other) 
	{
		PosX = other.PosX;
		PosY = other.PosY;
		_event = other._event;
		_data = other._data;

		//std::cout << "data size: " << _data.size() << std::endl;

		_collision = other._collision;
		Render = std::make_shared<GenericObjectRenderData>(_data.front());
		Render->Init(PosX, PosY);
		//std::cout << "copy finished" << std::endl;
	}
	
	std::shared_ptr<TileRenderData> GetFirstData()
	{
		if (_data.size() > 0)
		{
			return _data.front();
		}
		std::cerr << "map entity first texture nullptr!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<TileEntity> clone() const
	{
		return std::make_shared<TileEntity>(*this);
	}
	
	std::shared_ptr<GenericObjectRenderData> Render;
	
	virtual void ActivateEvent() override;
	


	void SetCollision(bool collision)
	{
		_collision = collision;
	}
	bool GetCollision() const
	{
		return _collision;
	}
	void Initalize(Shader* shader, int posx, int posy, EventType eventType, std::vector<std::shared_ptr<TileRenderData>> data, bool collision);

	inline std::string GetName() const
	{
		return _name;
	}

	void SetName(std::string name)
	{
		_name = name;
	}

	virtual void Tick(float DeltaTime) override;

	void RenderEntity() override;

	virtual EventType GetEventType() override
	{
		return _event.Type;
	}

protected:

	std::vector<std::shared_ptr<TileRenderData>> _data;
	bool _collision = false;

	std::string _name;

private:

};

