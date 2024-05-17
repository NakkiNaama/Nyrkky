#include "MapEntity.h"
#include "GameData.h"

MapEntity::MapEntity(const char* path, int State)
{

    std::cout << "map entity init" << std::endl;
    
	PosX = 0;
	PosY = 0;

    std::vector<std::string> tileEntityData;
    GridSize = 0;

    GameData::GetMapLoader()->LoadMap(path, GridSize, _tiles, tileEntityData);


    
    for (int i = 0; i < tileEntityData.size(); i++)
    {
        if (tileEntityData[i] != "-")
        {
            SpawnTileEntity(tileEntityData[i], i);
        }
    }
    
    
    if (State == 0) SpawnCharacterEntity(ECharacter::Emily, 3);



}

void MapEntity::InitMap(int mapID, bool setActive)
{
    ID = mapID;
    for (int i = 0; i <= 0; i++) // increase to have more layers
    {
        if (i == 0)
        {
            Renders.push_back(std::make_shared<MapRenderData>(i, 0, 0, GridSize, TileSize, mapID));
        }
        else {
            Renders.push_back(std::make_shared<MapRenderData>(i, 0, 0, GridSize, TileSize, mapID));
        }
        Renders[i]->Init(0, 0);
        SetActive(setActive);
    }
    
}

MapEntity::~MapEntity()
{
}

void MapEntity::Tick(float DeltaTime)
{
}

void MapEntity::ChangeTile(int layer, int index, int ID, bool solid)
{
    std::cout << "change tile called! layer: " << layer << std::endl;
    
    if (layer == 0)
    {
        Tile old = _tiles[index];
        std::shared_ptr<SubTile> subTile;


        subTile = std::make_shared<SubTile>(old.GetSubTile()->GetTextureID(), old.GetSubTile()->IsSolid());
        Tile tempTile = Tile(GameData::GetTextureName(ID), solid, old.HasSub, ID, subTile);
        _tiles[index] = tempTile;
    }
    else
    {
        std::shared_ptr<SubTile> newSub = std::make_shared<SubTile>(ID, solid);
        _tiles[index].SetSubTile(newSub);
        _tiles[index].HasSub = true;
    }

    ModifyMapRender(index, layer);

}

void MapEntity::SaveCurrentMap()
{
    GameData::GetMapLoader()->SaveMapToFile(GridSize, _tiles, _tileEntities);
}

void MapEntity::ModifyMapRender(int index, int layer)
{
    if (_tiles.size() > index)
    {

        if (layer == 0)
        {
            int tileOffset = index * 4 * 5;

            Renders[layer]->positions[tileOffset + 4] = _tiles[index].GetTexture();
            tileOffset += 5;

            Renders[layer]->positions[tileOffset + 4] = _tiles[index].GetTexture();
            tileOffset += 5;

            Renders[layer]->positions[tileOffset + 4] = _tiles[index].GetTexture();
            tileOffset += 5;

            Renders[layer]->positions[tileOffset + 4] = _tiles[index].GetTexture();
            tileOffset += 5;

            Renders[layer]->GetVB()->Bind();
            glBufferSubData(GL_ARRAY_BUFFER, 0, Renders[layer]->positions.size() * sizeof(float), Renders[layer]->positions.data());
        }
        else
        {
            int tileOffset = index * 4 * 5;

            Renders[layer]->positions[tileOffset + 4] = _tiles[index].GetSubTile()->GetTextureID();
            tileOffset += 5;

            Renders[layer]->positions[tileOffset + 4] = _tiles[index].GetSubTile()->GetTextureID();
            tileOffset += 5;

            Renders[layer]->positions[tileOffset + 4] = _tiles[index].GetSubTile()->GetTextureID();
            tileOffset += 5;

            Renders[layer]->positions[tileOffset + 4] = _tiles[index].GetSubTile()->GetTextureID();
            tileOffset += 5;

            Renders[layer]->GetVB()->Bind();
            glBufferSubData(GL_ARRAY_BUFFER, 0, Renders[layer]->positions.size() * sizeof(float), Renders[layer]->positions.data());
        }

    }
    else
    {
        std::cout << "change tile out of bounds!" << std::endl;
    }
    
}

void MapEntity::SpawnTileEntity(std::string entityName, int tile)
{
    std::cout << "spawn entity: " << entityName << std::endl;
    bool validSpawn = true;
    int q, e;
    int index;
    for (auto& d : _tileEntities)
    {
        d->GetPosition(q, e);
        index = e * GridSize + q;
        if (index == tile)
        {
            validSpawn = false;
            break;
        }
    }

    if (validSpawn)
    {
        if (entityName.size() > 0)
        {
            std::shared_ptr<TileEntity> type = GameData::GetMapLoader()->GetEntityTypeByName(entityName);
            if (type != nullptr)
            {
                std::shared_ptr<TileEntity> clone = type->clone();
                if (clone != nullptr)
                {
                    int x = tile % GridSize;
                    int y = tile / GridSize;
                    _tileEntities.push_back(clone);
                    _tileEntities.back()->SetPosition(x, y);
                    _tileEntities.back()->SetName(entityName);
                }
                else std::cerr << "spawn tile nullptr" << std::endl;
            }
        }
        else std::cerr << "spawn tile entity called with invalid name" << std::endl;
    }
    else std::cout << "tile already has entity!" << std::endl;
}

void MapEntity::SpawnCharacterEntity(ECharacter id, int tile)
{   
    std::shared_ptr<CharacterEntity> character = GameData::GetCharacters()[id];
    if (character != nullptr)
    {
        std::shared_ptr<CharacterEntity> clone = character->clone();
        if (clone != nullptr)
        {
            int x = tile % GridSize;
            int y = tile / GridSize;
            _characterEntities.push_back(clone);
            _characterEntities.back()->SetPosition(4, GridSize / 2);
            std::cout << _characterEntities.back()->GetName() << " spawned" << std::endl;
        }
        else std::cerr << "spawn character nullptr" << std::endl;
    }  
}

void MapEntity::ResetTile(int index, int layer)
{
    /*
    std::cout << "reset tile" << std::endl;
    std::shared_ptr<TileRenderData> z = GameData::GetMapLoader()->GetTileTypeByName("black.png", 0);
    TileRenderData subRender = *z;

    Tile tempTile = Tile(*z, false, false, subRender);
    _tiles[index] = tempTile;

    ModifyMapRender(index, layer);
    */
}

void MapEntity::RenderEntity()
{
    if (Active)
    {
        //std::cout << "rendering map: " << ID << std::endl;
        for (auto Render : Renders)
        {
            if (GameData::GetShader() != nullptr && Render != nullptr)
            {
                auto c = Render.get();
                if (c->GetVA() != nullptr && c->GetIB() != nullptr)
                {
                    if (c->Activate(PosX, PosY))
                    {
                        //std::cout << Active << std::endl;
                        GameData::GetRenderer()->Draw(c->GetVA(), c->GetIB());
                    }
                    else std::cout << "map render activate failed!" << std::endl;
                }
                else std::cout << "object render failed! nullptr!" << std::endl;
            }
            else std::cout << "nullptr in mapentity render!" << std::endl;
        }
        RenderTileEntities();
        RenderCharacterEntities();
    }
    //else std::cout << "map not active" << std::endl;
}

