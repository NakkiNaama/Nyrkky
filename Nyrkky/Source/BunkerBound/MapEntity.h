#pragma once
#include "Entity.h"
#include "Engine/Render/MapRenderData.h"
#include "MapLoader.h"
#include "CharacterEntity.h"


class MapEntity : public Entity
{
public:
	MapEntity(const char* path, int posx, int posy, int State);
	~MapEntity();

	void SpawnTileEntity(std::string entityName, int tile);
	void SpawnCharacterEntity(ECharacter id, int tile);
	void ResetTile(int index, int layer);

	inline int GetTileSize() const { return TileSize; }
	inline int GetGridSize() const { return GridSize; }
	
	std::vector<std::shared_ptr<MapRenderData>> Renders;
	
	
	//void RenderEntity(const Renderer& renderer) override;

	void RenderTileEntities()
	{
		for (auto Entity : _tileEntities)
		{
			Entity->RenderEntity();
		}
	}

	void RenderCharacterEntities()
	{
		for (auto Entity : _characterEntities)
		{
			Entity->RenderEntity();
		}
	}

	void RenderEntity() override;

	void ModifyMapRender(int index, int layer);
	void ChangeTile(int layer, int index, int ID, bool solid);
	void AddTile(int index, int ID);
	void InitalizeTileTypes();

	void SaveCurrentMap();
	
	std::vector<Tile> _tiles;
	std::vector<std::shared_ptr<TileRenderData>> _tileTypes;
	//std::vector<std::shared_ptr<TileRenderData>> _uiRenderData;
	std::vector<std::shared_ptr<TileRenderData>> _characterRenderData;

	std::vector<std::shared_ptr<TileEntity>> _entityTypes;
	std::vector<std::shared_ptr<TileEntity>> _tileEntities;
	std::vector<std::shared_ptr<CharacterEntity>> _characterEntities;
	

	std::shared_ptr<TileEntity> GetTileEntity(int x, int y)
	{
		int entityX, entityY;
		for (auto &entity : _tileEntities)
		{
			entity->GetPosition(entityX, entityY);
			if (entityX == x && entityY == y)
			{
				return entity;
			}
		}
		return nullptr;
	}

	std::shared_ptr<CharacterEntity> GetCharacterEntity(int x, int y)
	{
		int entityX, entityY;
		for (auto& entity : _characterEntities)
		{
			entity->GetPosition(entityX, entityY);
			if (entityX == x && entityY == y)
			{
				return entity;
			}
		}
		return nullptr;
	}

	virtual void Tick(float DeltaTime) override;

	inline void SetActive(bool active)
	{
		Active = active;
	}

protected:
	//std::unique_ptr<MapLoader> mapLoader;
	//Shader* usedShader;

	int GridSize = 12;
	float TileSize = 64;
	bool Active = false;


};

