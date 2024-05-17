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
	Item(EItem id, std::string name)
		:ID(id), Name(name)
	{}

	EItem ID;
	std::string Name;

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

