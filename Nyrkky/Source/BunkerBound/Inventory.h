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
	/*
	Item(const Item& other)
	{
		ID = other.ID;
		Name = other.Name;
		TextureID = other.TextureID;
	}
	*/
	EItem ID;
	std::string Name;
	uint32_t TextureID;

};

class Inventory
{
public:
	Inventory();

	std::vector<Item*> GetItems() const
	{
		return _items;
	}

	void AddItem(EItem itemID)
	{
		std::cout << "add item" << std::endl;
		for (auto &item : _itemTypes)
		{
			if(item.ID == itemID)
			{ 
				_items.push_back(&item);
				std::cout << item.Name << " added!" << std::endl;
				break;
			}
		}
	}


protected:
	std::vector<Item> _itemTypes;
	std::vector<Item*> _items;

};

