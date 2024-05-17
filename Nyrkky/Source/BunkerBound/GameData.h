#pragma once
#include "MapEntity.h"
#include "UI.h"
#include "Engine/Shader.h"
#include "DialogManager.h"
#include "CharacterEntity.h"
#include "MapLoader.h"
#include "Engine/TextureArray.h"


class GameData
{
public:
	//GameData(GameData&) = delete;

	GameData::GameData()
	{
	}

	static GameData& Get()
	{
		static GameData instance;
		return instance;
	}

	static void AddMap(std::shared_ptr<MapEntity> map)
	{
		GameData::Get().ImpAddMap(map);
	}

	static void InitalizeUI(std::shared_ptr<UI> pui)
	{
		GameData::Get().ImpInitalizeUI(pui);
	}

	static std::shared_ptr<MapEntity> GetMap()
	{
		return Get().ImpGetMap();
	}
	static std::vector<std::shared_ptr<MapEntity>> GetMaps()
	{
		return Get().ImpGetMaps();
	}
	static void ChangeMap(int id)
	{
		Get().ImpSetCurrentMap(id);
	}
	static std::shared_ptr<UI> GetUI()
	{
		return Get().ImpGetUI();
	}
	
	static glm::mat4 GetProj()
	{
		return Get().ImpGetProj();
	}

	static void SetProj(glm::mat4 p)
	{
		Get().ImpSetProj(p);
	}

	static int GetResolutionX()
	{
		return Get().ImpGetResolutionX();
	}

	static int GetResolutionY()
	{
		return Get().ImpGetResolutionY();
	}

	static int GetGridSize()
	{
		return Get().ImpGetGridSize();
	}

	static int GetTileSize()
	{
		return Get().ImpGetTileSize();
	}

	static void InitalizeShaders(std::shared_ptr<Shader> pshader, std::shared_ptr<Shader> ptextShader)
	{
		return Get().ImpInitalizeShaders(pshader, ptextShader);
	}

	static void InitalizeRenderer(std::shared_ptr<Renderer> prenderer)
	{
		Get().ImpInitalizeRenderer(prenderer);
	}

	static std::shared_ptr<Shader> GetShader()
	{
		return Get().ImpGetShader();
	}

	static std::shared_ptr<Shader> GetTextShader()
	{
		return Get().ImpGetTextShader();
	}

	static std::shared_ptr<Renderer> GetRenderer()
	{
		return Get().ImpGetRenderer();
	}

	static bool IsDialogVisible()
	{
		return Get().ImpIsDialogVisible();
	}

	static void SetDialogVisible(bool visible)
	{
		Get().ImpSetDialogVisible(visible);
	}
	/*
	static bool CanAct()
	{
		bool act = Get().ImpIsDialogVisible();
		return act;
	}
	*/
	static std::string GetDialogText()
	{
		//return Get().story->nodes[0].lines[0];
		return Get().story->currentNode->current;
	}
	
	static void SetDialogText(std::string text)
	{
		Get().ImpSetDialogText(text);
	}

	static uint32_t GetDialogSprite(int index)
	{
		return Get().ImpGetDialogSprite(index);
	}

	static void SetStory(std::shared_ptr<Story> pstory)
	{
		Get().ImpSetStory(pstory);
	}

	static std::shared_ptr<Story> GetStory()
	{
		return Get().ImpGetStory();
	}

	static bool IsChoice()
	{
		return Get().ImpIsChoice();
	}

	static void SetIsChoice(bool choice)
	{
		Get().ImpSetIsChoice(choice);
	}

	static void SetChoiceLines()
	{
		Get().ImpSetChoiceLines();
	}

	static void AddCharacter(std::shared_ptr<CharacterEntity> character)
	{
		Get().ImpAddCharacter(character);
	}

	static std::shared_ptr<CharacterEntity> GetCharacter(ECharacter character)
	{
		return Get().ImpGetCharacter(character);
	}

	static std::vector<std::shared_ptr<CharacterEntity>> GetCharacters()
	{
		return Get().ImpGetCharacters();
	}

	static std::shared_ptr<MapLoader> GetMapLoader()
	{
		return Get().ImpGetMapLoader();
	}

	static void SetMapLoader(std::shared_ptr<MapLoader> loader)
	{
		Get().ImpSetMapLoader(loader);
	}

	static std::shared_ptr<CharacterEntity> GetPlayer()
	{
		return Get().ImpGetPlayer();
	}

	static void SetPlayer(std::shared_ptr<CharacterEntity> player)
	{
		return Get().ImpSetPlayer(player);
	}

	static void AddCameraPosition(float PosAdd, int dir)
	{
		return Get().ImpAddCameraPosition(PosAdd, dir);
	}

	static glm::vec2 GetCameraPosition()
	{
		return Get().ImpGetCameraPosition();
	}

	static void SetCameraPosition(glm::vec2 pos)
	{
		Get().ImpSetCameraPosition(pos);
	}

	static void SetTextureArray(std::shared_ptr<TextureArray> array)
	{
		Get().ImpSetTextureArray(array);
	}

	static void SetCharacterTextureArray(std::shared_ptr<TextureArray> array)
	{
		Get().ImpSetCharacterTextureArray(array);
	}

	static std::shared_ptr<TextureArray> GetTextureArray()
	{
		return Get().ImpGetTextureArray();
	}

	static std::shared_ptr<TextureArray> GetCharacterTextureArray()
	{
		return Get().ImpGetCharacterTextureArray();
	}

	static uint32_t GameData::GetTextureIndex(const std::string& textureName) {
		return Get().ImpGetTextureIndex(textureName);
	}

	static uint32_t GameData::GetCharacterTextureIndex(const std::string& textureName) {
		return Get().ImpGetCharacterTextureIndex(textureName);
	}

	static void AddToTextureIndex(std::string fileName, size_t i)
	{
		Get().GameData::ImpAddToTextureIndex(fileName, i);
	}

	static void AddToCharacterTextureIndex(std::string fileName, size_t i)
	{
		Get().GameData::ImpAddToCharacterTextureIndex(fileName, i);
	}

	static std::string GetTextureName(size_t index)
	{
		return Get().GameData::ImpGetTextureName(index);
	}

	static std::string GetCharacterTextureName(size_t index)
	{
		return Get().GameData::ImpGetCharacterTextureName(index);
	}

private:

	void ImpAddMap(std::shared_ptr<MapEntity> pmap)
	{
		maps.push_back(pmap);
		if (currentMap == nullptr)
		{
			currentMap = pmap;
			std::cout << "First map has been set to the active map" << std::endl;
		}
	}

	void ImpInitalizeUI(std::shared_ptr<UI> pui)
	{
		ui = pui;
	}

	std::shared_ptr<UI> ImpGetUI()
	{
		return ui;
	}

	std::shared_ptr<MapEntity> ImpGetMap()
	{
		return currentMap;
	}

	std::vector<std::shared_ptr<MapEntity>> ImpGetMaps()
	{
		return maps;
	}

	glm::mat4 ImpGetProj()
	{
		return proj;
	}

	void ImpSetProj(glm::mat4 p)
	{
		proj = p;
	}

	int ImpGetResolutionX()
	{
		return ResolutionX;
	}

	int ImpGetResolutionY()
	{
		return ResolutionY;
	}

	int ImpGetGridSize()
	{
		return currentMap->GetGridSize();
	}

	int ImpGetTileSize()
	{
		return TileSize;
	}

	void ImpInitalizeShaders(std::shared_ptr<Shader> pshader, std::shared_ptr<Shader> ptextShader)
	{
		shader = pshader;
		textShader = ptextShader;
	}

	void ImpInitalizeRenderer(std::shared_ptr<Renderer> prenderer)
	{
		renderer = prenderer;
	}

	std::shared_ptr<Shader> ImpGetShader()
	{
		return shader;
	}

	std::shared_ptr<Shader> ImpGetTextShader()
	{
		return textShader;
	}

	std::shared_ptr<Renderer> ImpGetRenderer()
	{
		return renderer;
	}

	bool ImpIsDialogVisible()
	{
		return dialog;
	}

	void ImpSetDialogVisible(bool visible)
	{
		dialog = visible;
	}

	std::string ImpGetDialogText()
	{
		return "removed function";
		//return dialogText;
	}

	void ImpSetDialogText(std::string text)
	{
		//dialogText = text;
	}

	uint32_t ImpGetDialogSprite(int index)
	{
		return 0;
	}

	void ImpSetStory(std::shared_ptr<Story> pstory)
	{
		story = pstory;
	}

	std::shared_ptr<Story> ImpGetStory()
	{
		return story;
	}

	bool ImpIsChoice()
	{
		return choice;
	}

	void ImpSetIsChoice(bool pchoice)
	{
		choice = pchoice;
	}

	void ImpSetChoiceLines()
	{
		std::vector<std::string> lines;
		for (auto &line : story->currentNode->choices)
		{
			lines.push_back(line.text);
		}

		ui->SetChoiceLines(lines);
	}

	void ImpAddCharacter(std::shared_ptr<CharacterEntity> character)
	{
		characterEntities.push_back(character);
	}

	std::shared_ptr<CharacterEntity> ImpGetCharacter(ECharacter character)
	{
		for (auto c : characterEntities)
		{
			if (c->ID == character)
			{
				return c;
			}
		}
		return nullptr;
	}

	std::vector<std::shared_ptr<CharacterEntity>> ImpGetCharacters()
	{
		return characterEntities;
	}

	void ImpSetCurrentMap(int id)
	{

		/*
		if (currentMap->IsActive())
		{
			currentMap->SetActive(false);
		}
		else
		{
			currentMap->SetActive(true);
		}
		*/

		currentMap->SetActive(false);
		
		if (maps.size() > id)
		{
			currentMap = maps[id];
			currentMap->SetActive(true);

			Player->SetPosition(2, GameData::GetMap()->GetGridSize() / 2);
			int center = GameData::GetMap()->GetGridSize() / 2 * GameData::GetMap()->GetTileSize();
			glm::vec2 centerOfMap = { 0, -center - (currentMap->GetTileSize() * 8) };
			cameraPosition = centerOfMap;

			std::cout << "Current map has been changed to " << id << std::endl;
			return;
		}
		std::cerr << "Set current map failed" << std::endl;
		//if (maps.size() > 0) currentMap = maps[0]; return;
		std::cerr << "Set current map failed -- maps vector empty" << std::endl;
		
	}

	std::shared_ptr<MapLoader> ImpGetMapLoader()
	{
		return mapLoader;
	}

	void ImpSetMapLoader(std::shared_ptr<MapLoader> loader)
	{
		mapLoader = loader;
	}

	std::shared_ptr<CharacterEntity> ImpGetPlayer()
	{
		return Player;
	}

	void ImpSetPlayer(std::shared_ptr<CharacterEntity> player)
	{
		Player = player;
	}

	glm::vec2 ImpGetCameraPosition()
	{
		return cameraPosition;
	}

	void ImpSetCameraPosition(glm::vec2 pos)
	{
		cameraPosition = pos;
	}

	void ImpAddCameraPosition(float PosAdd, int dir)
	{
		switch (dir)
		{
			case 0: cameraPosition.y += PosAdd;
			break;
			case 1: cameraPosition.x += PosAdd;
			break;
			case 2: cameraPosition.y -= PosAdd;
			break;
			case 3: cameraPosition.x -= PosAdd;
			break;
		}
	}

	void ImpSetTextureArray(std::shared_ptr<TextureArray> array)
	{
		textureArray = array;
	}

	void ImpSetCharacterTextureArray(std::shared_ptr<TextureArray> array)
	{
		characterTextureArray = array;
	}

	std::shared_ptr<TextureArray> ImpGetTextureArray()
	{
		return textureArray;
	}

	std::shared_ptr<TextureArray> ImpGetCharacterTextureArray()
	{
		return characterTextureArray;
	}

	uint32_t ImpGetTextureIndex(const std::string& textureName) {
		auto& indexMap = textureIndexMap;
		auto it = indexMap.find(textureName);
		if (it != indexMap.end())
			return it->second;
		return std::numeric_limits<size_t>::max();
	}

	uint32_t ImpGetCharacterTextureIndex(const std::string& textureName) {
		auto& indexMap = characterTextureIndexMap;
		auto it = indexMap.find(textureName);
		if (it != indexMap.end())
			return it->second;
		return std::numeric_limits<size_t>::max();
	}

	void ImpAddToTextureIndex(std::string fileName, size_t i)
	{
		GameData::textureIndexMap[fileName] = i;
	}

	void ImpAddToCharacterTextureIndex(std::string fileName, size_t i)
	{
		GameData::characterTextureIndexMap[fileName] = i;
	}

	std::string ImpGetTextureName(size_t index) 
	{
		for (const auto& pair : textureIndexMap) {
			if (pair.second == index) {
				return pair.first;
			}
		}
		return "";
	}

	std::string ImpGetCharacterTextureName(size_t index)
	{
		for (const auto& pair : characterTextureIndexMap) {
			if (pair.second == index) {
				return pair.first;
			}
		}
		return "";
	}


	std::vector<std::shared_ptr<MapEntity>> maps;
	std::shared_ptr<MapEntity> currentMap;

	std::shared_ptr<UI> ui;
	glm::mat4 proj = glm::mat4();
	
	int TileSize = 64;

	int ResolutionX = 1920;
	int ResolutionY = 1080;
	glm::mat4 Projection = glm::mat4();

	std::shared_ptr<MapLoader> mapLoader;

	std::shared_ptr<Shader> shader;
	std::shared_ptr<Shader> textShader;

	std::shared_ptr<Renderer> renderer;

	std::shared_ptr<CharacterEntity> Player;
	std::vector<std::shared_ptr<CharacterEntity>> characterEntities;
	glm::vec2 cameraPosition;

	std::shared_ptr<TextureArray> textureArray;
	std::shared_ptr<TextureArray> characterTextureArray;

	// Indecies for texture array (map)
	std::unordered_map<std::string, size_t> textureIndexMap;

	// Indecies for texture array (characters)
	std::unordered_map<std::string, size_t> characterTextureIndexMap;

	bool dialog = false;
	bool choice = false;
	//std::string dialogText = "Modify this text";
	
	std::shared_ptr<Story> story;

};

