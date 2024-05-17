#pragma once
#include "Entity.h"
#include "Engine/Render/GenericObjectRenderData.h"
#include "Engine/TileTypeList.h"



class TileEntity : public Entity
{
public:
	TileEntity(std::string name, Event event, int posx, int posy, std::vector<uint32_t> textures, bool collision);
	~TileEntity();

	TileEntity(const TileEntity& other) 
	{
		PosX = other.PosX;
		PosY = other.PosY;
		_event = other._event;
		_textures = other._textures;

		_collision = other._collision;
		Render = std::make_shared<GenericObjectRenderData>();
		Render->Init(PosX, PosY);
		Render->SetTexture(_textures[0]);

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

	uint32_t GetFirstTexture() const
	{
		if (_textures.size() > 0)
		{
			return _textures[0];
		}
		return ~0;
	}

	std::vector<uint32_t> GetTextures() const
	{
		return _textures;
	}

protected:

	std::vector<uint32_t> _textures;
	bool _collision = false;

	std::string _name;

private:

};

