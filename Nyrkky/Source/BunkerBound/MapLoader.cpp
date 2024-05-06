#include "MapLoader.h"
#include <fstream>
#include "tinyxml2.h"
#include "GameData.h"

MapLoader::MapLoader()
{
    LoadAtlasTextures();
    //GenerateGenericMap();
    InitalizeTileEntityTypes();
}

bool MapLoader::GenerateGenericMap()
{
    LoadAtlasTextures();

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* root = doc.NewElement("root");
    doc.LinkEndChild(root);

    const char* childName = "error";

    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 32; x++)
        {

            tinyxml2::XMLElement* tile = doc.NewElement("Tile");
            root->LinkEndChild(tile);

            for (int i = 0; i <= 6; i++)
            {
                switch (i)
                {
                case 0: childName = "Name"; break;
                case 1: childName = "AtlasID"; break;
                case 2: childName = "Collision"; break;

                case 3: childName = "HasSub"; break;

                case 4: childName = "SubName"; break;
                case 5: childName = "SubAtlasID"; break;

                case 6: childName = "EntityName"; break;
                }
                tinyxml2::XMLElement* child = doc.NewElement(childName);
                switch (i)
                {
                case 0: child->SetText("RPGpack_sheet_2X.png"); break;
                case 1: child->SetText("145"); break;
                case 2: child->SetText("0"); break;

                case 3: child->SetText("0"); break;

                case 4: child->SetText("-"); break;
                case 5: child->SetText("0"); break;

                case 6: child->SetText("-"); break;
                }

                tile->LinkEndChild(child);
            }
        }
    }

    doc.SaveFile("Maps/generic.xml");

    return true;
}

void MapLoader::LoadMap(const char* path, int& gridSize, std::vector<Tile> &tiles, std::vector<std::shared_ptr<TileRenderData>>& types, std::vector<std::shared_ptr<TileEntity>>& entityTypes, std::vector<std::string>& tileEntities)
{    
    //std::cout << "load map called" << std::endl;
    tinyxml2::XMLDocument doc;

    std::shared_ptr<TileRenderData> t;

    if (doc.LoadFile(path) == tinyxml2::XML_SUCCESS)
    {
        tinyxml2::XMLElement* root = doc.RootElement();
        if (root)
        {
            for (tinyxml2::XMLElement* child = root->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
            {
                std::string name = child->FirstChildElement("Name")->GetText();
                int AtlasID = std::stoi(child->FirstChildElement("AtlasID")->GetText());
                bool Collision = std::stoi(child->FirstChildElement("Collision")->GetText());

                bool HasSub = std::stoi(child->FirstChildElement("HasSub")->GetText());

                std::string SubName = child->FirstChildElement("SubName")->GetText();
                int SubAtlasID = std::stoi(child->FirstChildElement("SubAtlasID")->GetText());

                tileEntities.push_back(child->FirstChildElement("EntityName")->GetText());


                t = GetTileTypeByName(name, AtlasID);

                if (t != nullptr)
                {
                    if (t->GetTexID() >= 0) 
                    {
                        if (HasSub)
                        {
                            std::shared_ptr<TileRenderData> subRender;
                            subRender = GetTileTypeByName(SubName, SubAtlasID);

                            if (subRender != nullptr)
                            {
                                Tile v = Tile(*t, Collision, HasSub, *subRender);
                                tiles.push_back(v);
                            }
                            else
                            {
                                std::cout << "missing sub map texture!" << std::endl;
                                Tile v = Tile(*t, Collision, HasSub, *_transparent);
                                tiles.push_back(v);
                            }
                        }
                        else 
                        {
                            Tile v = Tile(*t, Collision, HasSub, *_transparent);
                            tiles.push_back(v);
                        }
                    }
                }
                else
                {
                    std::cout << "missing map texture!" << std::endl;
                    Tile v = Tile(*_transparent, false, false, *_transparent);
                    tiles.push_back(v);
                }
                gridSize++;
            }

        }
        else std::cerr << "map xml root could not be found!";

        
        types = _tileTypes;
        entityTypes = _entityTypes;
    }
    else std::cerr << "Map that were to be loaded could not be found!" << std::endl;

    int numColumns = sqrt(gridSize); // Assuming grid is square
    gridSize = gridSize / numColumns;

    std::cout << "new grid size " << gridSize << std::endl;

}

bool MapLoader::SaveMapToFile(int MapSize, const std::vector<Tile>& tiles, const std::vector<std::shared_ptr<TileEntity>> tileEntities)
{
    std::cout << "save map called" << std::endl;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* root = doc.NewElement("root");
    doc.LinkEndChild(root);

    const char* childName = "error";

    int entX, entY;
    
    int index = 0;
    bool finished = false;
    int loop = 0;

    for (auto& tile : tiles)
    {
        tinyxml2::XMLElement* tileElement = doc.NewElement("Tile");
        root->LinkEndChild(tileElement);

        for (int i = 0; i <= 6; i++)
        {
            switch (i)
            {
            case 0: childName = "Name"; break;
            case 1: childName = "AtlasID"; break;
            case 2: childName = "Collision"; break;

            case 3: childName = "HasSub"; break;

            case 4: childName = "SubName"; break;
            case 5: childName = "SubAtlasID"; break;

            case 6: childName = "EntityName"; break;
            }
            tinyxml2::XMLElement* child = doc.NewElement(childName);
            switch (i)
            {
            case 0: child->SetText(tile.Data.GetName().c_str()); break;
            case 1: child->SetText(std::to_string(tile.Data.UV_ID).c_str()); break;
            case 2: child->SetText(std::to_string(tile.IsSolid()).c_str()); break;

            case 3: child->SetText(std::to_string(tile.HasSub).c_str()); break;

            case 4: child->SetText(tile.SubData.GetName().c_str()); break;
            case 5: child->SetText(tile.SubData.UV_ID); break;

            case 6: 
                finished = false;
                for (auto& ent : tileEntities)
                {
                    ent->GetPosition(entX, entY);
                    index = entY * GameData::GetGridSize() + entX;
                    if (index == loop)
                    {
                        child->SetText(ent->GetName().c_str());
                        finished = true;
                        break;
                    }
                }
                if (!finished)
                {
                    child->SetText("-"); 
                }
                break;
            }

            tileElement->LinkEndChild(child);
        }
        loop++;
    }

    doc.SaveFile("Maps/NewMap.xml");

    std::cout << "Map save success." << std::endl;
    return true;
}

void MapLoader::LoadAtlasTextures()
{
    std::cout << "load texture atlas called" << std::endl;
    // If tile has no sub texture   
    std::shared_ptr<Texture> transparent = std::make_shared<Texture>("..\\Nyrkky\\Resources\\Textures\\transparent.png", false);
    _transparent = std::make_shared<TileRenderData>("-", transparent, 64, 64, 64, 64, 0);
    _transparent->SetTextureID(-1);
    /**/

    std::shared_ptr<Texture> texture;
    int ID = 0;

    texture = std::make_shared<Texture>("..\\Nyrkky\\Resources\\Textures\\World\\RPGpack_sheet_2X.png", false);
    for (int i = 0; i <= 254; i++)
    {
        _tileTypes.push_back(std::make_shared<TileRenderData>("RPGpack_sheet_2X.png", texture, 2560, 1664, 128, 128, i));
        _tileTypes.back()->SetTextureID(ID);
    }
    ID++;

    texture = std::make_shared<Texture>("..\\Nyrkky\\Resources\\Textures\\chest_atlas.png", false);
    for (int i = 0; i <= 1; i++)
    {
        _tileTypes.push_back(std::make_shared<TileRenderData>("chest_atlas.png", texture, 128, 64, 64, 64, i));
        _tileTypes.back()->SetTextureID(ID);
    }
    ID++;

    texture = std::make_shared<Texture>("..\\Nyrkky\\Resources\\Textures\\ladder.png", false);
    _tileTypes.push_back(std::make_shared<TileRenderData>("ladder.png", texture, 64, 64, 64, 64, 0));
    _tileTypes.back()->SetTextureID(ID);
    ID++;

    texture = std::make_shared<Texture>("..\\Nyrkky\\Resources\\Textures\\UI\\ui_atlas.png", false);
    for (int i = 0; i <= 36; i++)
    {
        _uiRenderData.push_back(std::make_shared<TileRenderData>("ui_atlas.png", texture, 512, 256, 64, 64, i));
        _uiRenderData.back()->SetTextureID(ID);
    }
    ID++;

    texture = std::make_shared<Texture>("..\\Nyrkky\\Resources\\Textures\\color_atlas.png", false);
    for (int i = 0; i <= 36; i++)
    {
        _uiRenderData.push_back(std::make_shared<TileRenderData>("color_atlas.png", texture, 256, 128, 64, 32, i));
        _uiRenderData.back()->SetTextureID(ID);
    }
    ID++;

    texture = std::make_shared<Texture>("..\\Nyrkky\\Resources\\Textures\\character_atlas.png", false);
    for (int i = 0; i <= 36; i++)
    {
        _characterRenderData.push_back(std::make_shared<TileRenderData>("character_atlas.png", texture, 512, 1024, 512, 1024, i));
        _characterRenderData.back()->SetTextureID(ID);
    }
    ID++;
    
    for (auto &c : _characterRenderData)
    {
        _tileTypes.push_back(c);
    }

    texture = std::make_shared<Texture>("..\\Nyrkky\\Resources\\Textures\\9.png", false);
    _tileTypes.push_back(std::make_shared<TileRenderData>("9.png", texture, 64, 64, 64, 64, 0));
    _tileTypes.back()->SetTextureID(ID);
    ID++;

    texture = std::make_shared<Texture>("..\\Nyrkky\\Resources\\Textures\\10.png", false);
    _tileTypes.push_back(std::make_shared<TileRenderData>("10.png", texture, 64, 64, 64, 64, 0));
    _tileTypes.back()->SetTextureID(ID);
    ID++;
    
    texture = std::make_shared<Texture>("..\\Nyrkky\\Resources\\Textures\\11.png", false);
    _tileTypes.push_back(std::make_shared<TileRenderData>("11.png", texture, 64, 64, 64, 64, 0));
    _tileTypes.back()->SetTextureID(ID);
    ID++;

    texture = std::make_shared<Texture>("..\\Nyrkky\\Resources\\Textures\\12.png", false);
    _tileTypes.push_back(std::make_shared<TileRenderData>("12.png", texture, 64, 64, 64, 64, 0));
    _tileTypes.back()->SetTextureID(ID);
    ID++;

}

void MapLoader::InitalizeTileEntityTypes()
{
    std::cout << "init tile entity types" << std::endl;
    std::vector<std::shared_ptr<TileRenderData>> entityData;
    // Chest
    AddTileType("Chest01", "chest_atlas.png", std::vector<int>{0, 1}, EventChest);
    // Door
    AddTileType("Door01", "RPGpack_sheet_2X.png", std::vector<int>{219, 199}, EventDoor);
    // Ladder
    AddTileType("Ladder", "ladder.png", std::vector<int>{0}, EventTeleport, 1, false);
}

void MapLoader::AddTileType(std::string entityName, std::string textureName, std::vector<int> IDs, EventType eventType, int effect, bool collison)
{
    std::cout << "Add tile type called" << std::endl;
    std::vector<std::shared_ptr<TileRenderData>> entityData;
    for (auto& id : IDs)
    {
        entityData.push_back(GetTileTypeByName(textureName, id));
    }
    Event newEvent = Event(eventType, effect);
    _entityTypes.push_back(std::make_shared<TileEntity>(entityName, newEvent, 0, 0, entityData, collison));
}


