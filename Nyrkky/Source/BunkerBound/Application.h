#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Engine/Renderer.h"
#include "Basics.h"

#include "CharacterEntity.h"
#include "TextEntity.h"
#include "MapEntity.h"

#include "UI.h"
#include "DialogManager.h"
#include "GameData.h"
#include <unordered_set>


class Application
{
public:
	Application();
	virtual ~Application();

	void Run();
	void CreateWindow();
	virtual void StartGame();
	void SetScreenState(bool fullScreen);
	virtual void KeyPressEvent
	(int key, int scancode, int action, int mods);
	virtual void MouseClickEvent
	(int button, int action, int mods);
	virtual void MouseScrollEvent
	(double xoffset, double yoffset);

	void SaveMap()
	{
		GameData::GetMap()->SaveCurrentMap();
	}

protected:
	void AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex);
	void AddIndex(std::vector<unsigned int>& x, float v1, float v2, float v3);
	//void HandleInput();
	void UpdateViewMatrix();
	void LoadMap();
	void InitalizeGameStartingState();



	void MoveCamera(int x) {
		GameData::AddCameraPosition(_moveSpeed, x);
	}

	std::shared_ptr<TileEntity> GetFacedTileEntity() const
	{
		Direction dir = GameData::GetPlayer()->GetLastMovementDirection();
		int x, y;
		GameData::GetPlayer()->GetPosition(x, y);
		AddDirectionToCoordinate(dir, x, y);
		return GameData::GetMap()->GetTileEntity(x, y);
	}

	std::shared_ptr<TileEntity> GetUnderTileEntity() const
	{
		int x, y;
		GameData::GetPlayer()->GetPosition(x, y);
		return GameData::GetMap()->GetTileEntity(x, y);
	}

	std::shared_ptr<CharacterEntity> GetFacedCharacterEntity() const
	{
		Direction dir = GameData::GetPlayer()->GetLastMovementDirection();
		int x, y;
		GameData::GetPlayer()->GetPosition(x, y);
		AddDirectionToCoordinate(dir, x, y);
		return GameData::GetMap()->GetCharacterEntity(x, y);
	}

	void InteractWithObject()
	{
		auto entity = GetFacedTileEntity();

		if (entity != nullptr)
		{
			if (entity->_event.Type != EventType::EventTeleport)
			{
				entity->ActivateEvent();
			}
		}
		else
		{
			auto charEntity = GetFacedCharacterEntity();

			if (charEntity != nullptr)
			{
				charEntity->ActivateEvent();
			}

		}
	}

	void MoveMainCharacter(Direction direction)
	{
		auto entity = GetUnderTileEntity();
		GameData::GetPlayer()->currentDir = direction;
		if (entity != nullptr)
		{
			entity->ActivateEvent();
		}
	}

	void ChangeOffset(int offset, bool cursorPosCheck = false);

	int GetClickedTile();

	GLFWwindow* Window;

	void UpdateKeys();
	void HandleEntity(std::shared_ptr<Entity> entity, float deltaTime);

	bool CTRL = false;

	void LeftClick(bool ctrl = false);
	void RightClick();

	void GetClickedUIPosition(double& x, double& y) const
	{
		double mouseX, mouseY;
		glfwGetCursorPos(Window, &mouseX, &mouseY);

		int windowWidth, windowHeight;
		glfwGetFramebufferSize(Window, &windowWidth, &windowHeight);

		float scaleX, scaleY;
		glfwGetWindowContentScale(Window, &scaleX, &scaleY);

		x = mouseX * scaleX;
		y = windowHeight - mouseY * scaleY;
	}

protected:
	void HandleKeyPress(float DeltaTime);
	void StaticDelayPress(float DeltaTime);
	void StaticDelayPressDialog(float DeltaTimebool);

	void DialogExecute();

	std::unordered_set<int> _pressedKeys;
	bool _editor = false;
	bool _fullScreen = false;
	float _staticDelayTimer = 0;


private:

	float _moveSpeed = 20;

	void UpdateProjectionMatrix();
	glm::vec2 ScreenToWorld();

	glm::mat4 _view = glm::mat4(1.0f);
	std::vector<std::shared_ptr<TextEntity>> _textEntities;
	glm::vec2 _centerOfMap;
	bool _mouseInUse = false;

};





