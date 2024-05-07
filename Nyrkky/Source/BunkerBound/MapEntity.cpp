#include "MapEntity.h"
#include "GameData.h"

MapEntity::MapEntity(const char* path, int posx, int posy, int State)
{

	PosX = posx;
	PosY = posy;
    //GameData::GetMapLoader();

    std::vector<std::string> tileEntityData;
    //MapLoader& loader = GameData::GetMapLoader();
    GridSize = 0;

    //  _tileTypes, _entityTypes, are not in load anymore
    GameData::GetMapLoader()->LoadMap(path, GridSize, _tiles, tileEntityData);
    //_uiRenderData = GameData::GetMapLoader()->_uiRenderData;
    
    _characterRenderData = GameData::GetMapLoader()->_characterRenderData;

    /*
    for (int i = 0; i < tileEntityData.size(); i++)
    {
        if (tileEntityData[i] != "-")
        {
            SpawnTileEntity(tileEntityData[i], i);
        }
    }
    */
    
    if (State == 0) SpawnCharacterEntity(ECharacter::Emily, 3);

    //InitalizeTileTypes();
    //std::vector<TileRenderData> layer0;
    //std::vector<TileRenderData> layer1;

    for (auto &tile : _tiles)
    {
        //layer0.push_back(tile.Data);
        //layer1.push_back(tile.SubData);
    }

    Renders.push_back(std::make_shared<MapRenderData>(0, 0, 0, GridSize, TileSize));
    Renders.back()->Init(0, 0);

    /*
    for (int i = 0; i <= 1; i++) // increase to have more layers
    {
        if (i == 0)
        {
            //int layer, int ScreenX, int ScreenY, int gridSize, int tileSize;
            Renders.push_back(std::make_shared<MapRenderData>(i, PosX, PosY, GridSize, TileSize));
        }
        else {
            Renders.push_back(std::make_shared<MapRenderData>(i, PosX, PosY, GridSize, TileSize));
        }
        Renders.back()->Init(PosX, PosY);
    }
    */

}

MapEntity::~MapEntity()
{
}

void MapEntity::Tick(float DeltaTime)
{
    //std::cout << "ticker" << std::endl;
}

void MapEntity::ChangeTile(int layer, int index, int ID, bool solid)
{
    /*
    std::shared_ptr<TileRenderData> z = GameData::GetMapLoader()->GetTileType(ID);
    if (z != nullptr)
    {   
        bool sub = layer != 0 || _tiles[index].HasSub;

        if (layer == 0)
        {
            TileRenderData subRender = _tiles[index].SubData;
            Tile tempTile = Tile(*z, solid, sub, subRender);
            tempTile.HasSub = sub;
            _tiles[index] = tempTile;
        }
        else
        {
            Tile tempTile = _tiles[index];
            TileRenderData subRender = *(GameData::GetMapLoader()->GetTileType(ID));
            tempTile.SetSolid(solid);
            tempTile.SubData = subRender;
            tempTile.HasSub = true;
            _tiles[index] = tempTile;

        }
        
        ModifyMapRender(index, layer);

    }
    else std::cout << "Change tile failed!" << std::endl;
    */
}

void MapEntity::SaveCurrentMap()
{
    GameData::GetMapLoader()->SaveMapToFile(GridSize, _tiles, _tileEntities);
}

void MapEntity::ModifyMapRender(int index, int layer)
{
    /*
    TileRenderData* newRender;
    if (layer == 0)
    {
        newRender = &_tiles[index].Data;
    }
    else
    {
        newRender = &_tiles[index].SubData;
    }

    if (_tiles.size() > index)
    {
        int tileOffset = index * 4 * 5;

        Renders[layer]->positions[tileOffset + 2] = ((newRender->UV_x) * newRender->SpriteW) / newRender->SheetW;
        Renders[layer]->positions[tileOffset + 3] = ((newRender->UV_y) * newRender->SpriteH) / newRender->SheetH;
        Renders[layer]->positions[tileOffset + 4] = newRender->GetTexID();
        tileOffset += 5;

        Renders[layer]->positions[tileOffset + 2] = ((newRender->UV_x + 1) * newRender->SpriteW) / newRender->SheetW;
        Renders[layer]->positions[tileOffset + 3] = (newRender->UV_y * newRender->SpriteH) / newRender->SheetH;
        Renders[layer]->positions[tileOffset + 4] = newRender->GetTexID();
        tileOffset += 5;

        Renders[layer]->positions[tileOffset + 2] = ((newRender->UV_x) * newRender->SpriteW) / newRender->SheetW;
        Renders[layer]->positions[tileOffset + 3] = ((newRender->UV_y + 1) * newRender->SpriteH) / newRender->SheetH;
        Renders[layer]->positions[tileOffset + 4] = newRender->GetTexID();
        tileOffset += 5;

        Renders[layer]->positions[tileOffset + 2] = ((newRender->UV_x + 1) * newRender->SpriteW) / newRender->SheetW;
        Renders[layer]->positions[tileOffset + 3] = ((newRender->UV_y + 1) * newRender->SpriteH) / newRender->SheetH;
        Renders[layer]->positions[tileOffset + 4] = newRender->GetTexID();
        tileOffset += 5;

        Renders[layer]->GetVB()->Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, Renders[layer]->positions.size() * sizeof(float), Renders[layer]->positions.data());
    }
    else
    {
        std::cout << "change tile out of bounds!" << std::endl;
    }
    */
}

void MapEntity::SpawnTileEntity(std::string entityName, int tile)
{
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
            //_characterEntities.back()->SetName(entityName);
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
        for (auto Render : Renders)
        {
            if (GameData::GetShader() != nullptr && Render != nullptr)
            {
                auto c = Render.get();
                if (c->GetVA() != nullptr && c->GetIB() != nullptr)
                {
                    if (c->Activate(PosX, PosY))
                    {
                        GameData::GetRenderer()->Draw(c->GetVA(), c->GetIB());
                    }
                    else std::cout << "map render activate failed! 0000000000112233445566789987" << std::endl;
                }
                else std::cout << "object render failed! nullptr!" << std::endl;
            }
            else std::cout << "nullptr in mapentity render!" << std::endl;
        }
        RenderTileEntities();
        RenderCharacterEntities();
    }

}

