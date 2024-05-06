#pragma once
#include "Basics.h"
#include "Engine/TileTypeList.h"
#include "TileEntity.h"
#include <filesystem>

class MapLoader
{
public:
	MapLoader();
	void LoadMap(const char* path, int& gridSize, std::vector<Tile>& tiles, std::vector<std::shared_ptr<TileRenderData>>& types, std::vector<std::shared_ptr<TileEntity>>& entityTypes, std::vector<std::string>& tileEntities);
	
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
	
	std::shared_ptr<TileRenderData> GetTileTypeByName(std::string name, int atlasID) const
	{
		for (auto tile : _tileTypes)
		{
			if (tile->GetName() == name && tile->UV_ID == atlasID)
			{
				return tile;
			}
		}
		return _transparent;
		return nullptr;
	}

	std::shared_ptr<TileRenderData> GetTileType(int textureID) const
	{
		if(_tileTypes.size() > textureID) return _tileTypes[textureID];		
		return _transparent;
	}

	bool SaveMapToFile(int MapSize, const std::vector<Tile>& tiles, const std::vector<std::shared_ptr<TileEntity>> tileEntities);

	std::vector<std::shared_ptr<TileRenderData>> _tileTypes;
	std::vector<std::shared_ptr<TileRenderData>> _uiRenderData;
	std::vector<std::shared_ptr<TileRenderData>> _characterRenderData;

	std::vector<std::shared_ptr<TileEntity>> _entityTypes;

	void LoadAtlasTextures();

	
	void AddTileType(std::string entityName, std::string textureName, std::vector<int> IDs, EventType eventType, int effect = 0, bool collison = true);
	
	
	void InitalizeTileEntityTypes();
	void SpawnTileEntity(int EntityID, int tile);

	Shader* _shader;

protected:
	bool GenerateGenericMap();

	std::shared_ptr<TileRenderData> _transparent;


};

