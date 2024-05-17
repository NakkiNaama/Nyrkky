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
	Item(EItem id, std::string name, uint32_t textureID)
		:ID(id), Name(name), TextureID(textureID)
	{}

	EItem ID;
	std::string Name;
	uint32_t TextureID;

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

