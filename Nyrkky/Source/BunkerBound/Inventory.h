#pragma once
#include "Basics.h"
#include "Engine/Render/GenericObjectRenderData.h"

enum EItem
{
	EKey,
	EFish,
	EPistol
};

struct Item
{
public:
	Item(EItem id, std::string name, std::shared_ptr<TileRenderData> data)
		:ID(id), Name(name), Data(data)
	{}

	EItem ID;
	std::string Name;
	std::shared_ptr<TileRenderData> Data;
};

class Inventory
{
public:
	Inventory();

	std::vector<Item> GetInventory() const
	{
		return _inventory;
	}


protected:
	std::vector<Item> _itemTypes;
	std::vector<Item> _inventory;

};

