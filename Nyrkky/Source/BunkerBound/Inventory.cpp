#include "Inventory.h"
#include "GameData.h"

Inventory::Inventory()
{
	//GenericObjectRenderData boo();

	_itemTypes.push_back(Item(EKey, "Key", GameData::GetTextureIndex("key.png")));
	_itemTypes.push_back(Item(EFish, "Fish", GameData::GetTextureIndex("fish.png")));
	_itemTypes.push_back(Item(EPistol, "Pistol", GameData::GetTextureIndex("pistol.png")));
	
	
	//_items.push_back(&_itemTypes[0]);
	//_items.push_back(&_itemTypes[1]);
	//_items.push_back(&_itemTypes[2]);
	

}
