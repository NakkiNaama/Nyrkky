#pragma once
#include "Basics.h"
#include "Engine/TileTypeList.h"
#include "TileEntity.h"
#include <filesystem>

class MapLoader
{
public:
	MapLoader();
	void LoadMap(const char* path, int& gridSize, std::vector<Tile>& tiles, std::vector<std::string>& tileEntities);
	
	std::shared_ptr<TileEntity> GetEntityTypeByName(std::string name) const
	{
		for (auto entity : _entityTypes)
		{
			if (entity->GetName() == name)
			{
				return entity;
			}
		}
		return nullptr;
	}

	bool SaveMapToFile(int MapSize, const std::vector<Tile>& tiles, const std::vector<std::shared_ptr<TileEntity>> tileEntities);

	std::vector<std::shared_ptr<TileEntity>> _entityTypes;

	
	void AddTileType(std::string entityName, std::vector<std::string> textureNames, EventType eventType, int effect = 0, bool collison = true);
	
	
	void InitalizeTileEntityTypes();
	void SpawnTileEntity(int EntityID, int tile);

	Shader* _shader;

protected:
	bool GenerateGenericMap();



};

