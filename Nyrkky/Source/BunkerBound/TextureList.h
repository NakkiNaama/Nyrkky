#pragma once
#include "Basics.h"
#include "Engine/TextureArray.h"
#include "GameData.h"

void InitMapTextures()

{
    std::vector<std::string> paths;
    std::string path = "..\\Nyrkky\\Resources\\Textures\\Array\\";

    paths.push_back(path + "error.png");
    paths.push_back(path + "invisible.png");

    paths.push_back(path + "A.png");
    paths.push_back(path + "B.png");
    paths.push_back(path + "C.png");
    paths.push_back(path + "D.png");

    paths.push_back(path + "number_1.png");
    paths.push_back(path + "number_2.png");
    paths.push_back(path + "number_3.png");

    paths.push_back(path + "collisionOff.png");
    paths.push_back(path + "collisionOn.png");
    paths.push_back(path + "ObjectView.png");
    paths.push_back(path + "TerrainView.png");

    paths.push_back(path + "highlight.png");
    paths.push_back(path + "transparent.png");

    paths.push_back(path + "StoneFloor01.png");
    paths.push_back(path + "StoneFloor02.png");

    paths.push_back(path + "chest_closed.png");
    paths.push_back(path + "chest_open.png");
    paths.push_back(path + "ladder.png");
    paths.push_back(path + "door_closed.png");
    paths.push_back(path + "door_open.png");

    std::shared_ptr<TextureArray> AR = TextureManager::GetTextureArray(paths);
    //AR->GetSize();

    for (size_t i = 0; i < paths.size(); ++i) {
        std::string fileName = paths[i].substr(paths[i].find_last_of("\\/") + 1);
        GameData::AddToTextureIndex(fileName, i);
    }

    GameData::SetTextureArray(AR);
    /*
    {
        size_t textureIndex = GameData::GetTextureIndex("StoneFloor01.png");
        std::string textureName = GameData::GetTextureName(textureIndex);

        std::cout << "tex: " << textureIndex << "   " << textureName << std::endl;
    }
    */
}


void InitCharacterTextures()
{

    std::vector<std::string> paths;
    paths.push_back("..\\Nyrkky\\Resources\\Textures\\Characters\\emily-front.png");
    paths.push_back("..\\Nyrkky\\Resources\\Textures\\Characters\\emily-right.png");
    paths.push_back("..\\Nyrkky\\Resources\\Textures\\Characters\\emily-back.png");
    paths.push_back("..\\Nyrkky\\Resources\\Textures\\Characters\\emily-left.png");

    paths.push_back("..\\Nyrkky\\Resources\\Textures\\Characters\\Arisu.png");

    for (size_t i = 0; i < paths.size(); ++i) {
        std::string fileName = paths[i].substr(paths[i].find_last_of("\\/") + 1);
        GameData::AddToCharacterTextureIndex(fileName, i);
    }
    /*
    {
        size_t textureIndex = GameData::GetCharacterTextureIndex("Arisu.png");
        std::string textureName = GameData::GetCharacterTextureName(textureIndex);
        std::cout << "character tex: " << textureIndex << "   " << textureName << std::endl;
    }
    */
    std::shared_ptr<TextureArray> AR = TextureManager::GetTextureArray(paths);

    GameData::SetCharacterTextureArray(AR);
}

void InitTextureArray()
{
    InitMapTextures();
    InitCharacterTextures();

}