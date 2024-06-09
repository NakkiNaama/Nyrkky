#pragma once
#include <memory>
#include "Basics.h"
#include "Engine/Renderer.h"
#include "Engine/Render/RenderBase.h"
#include "Engine/Shader.h"

enum EventType
{
	EventNone,
	EventTalk,
	EventDoor,
	EventChest,
	EventTeleport
};

struct Event
{
public:
	Event(EventType type, int effect)
	{
		Type = type;
		//State = state;
		Effect = effect;
	}

	EventType Type;

	// Current state of object. For Example is chest or door open or not.
	int State = 0;

	// Changes the effect the of entity.
	//  For example setting this to map index would decide loaded map.
	int Effect = 0;
};

class Entity
{
public:
	Entity();

	void GetPosition(int& x, int& y) const
	{
		x = PosX;
		y = PosY;
	}
	/*
	int GetPositionIndex() const
	{
		return GameData::CoordinateToIndex(PosX, PosY);
	}
	*/

	void SetPosition(int x, int y)
	{
		PosX = x;
		PosY = y;
	}

	virtual void Tick(float DeltaTime);
	virtual void RenderEntity();

	virtual EventType GetEventType()
	{
		return EventType::EventNone;
	}

	virtual void ActivateEvent();

	Event _event;

protected:
	//Shader* usedShader;
	

	int PosX = 0;
	int PosY = 0;
	//std::unique_ptr<RenderBase> Render;
};



