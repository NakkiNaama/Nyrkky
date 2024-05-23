#pragma once
#include "Engine/Render/Text.h"
#include "Engine/Shader.h"
#include "Engine/Renderer.h"
#include "Engine/Render/UIObjectRenderData.h"
#include "Engine/TileTypeList.h"
#include "MapEntity.h"
#include "Inventory.h"
#include <filesystem>


enum ETextureArray
{
	EMapTexture = 0,
	ECharacterTexture = 1
};

enum ClickResponse
{
	ENoneClick, 
	EGameClick,
	EButtonClick,
	EEditorButtonClick,
	EStaticElementClick
};

enum UIObjectType
{
	ETypeless,
	EEditorOverlay,
	EEditorButton,
	EEditorTextureButton,
	EEditorObjectButton,
	ESelection,
	EGameOverlay,
	EDialog,
	EGameButton,
	EChoiceUI,
	EChoiceButton
};


class UI
{
public:
	UI(int frameBufferX, int frameBufferY);

	~UI();

	std::shared_ptr<UIObjectRenderData> CreateUIObject(UIObjectType type, uint32_t arrayID, uint32_t texture, float xPercentage, float yPercentage, float widthPercentage, float heightPercentage, bool interactable, int id = 0);
	
	void CreateGameUI();
	void CreateEditorUI();
	std::shared_ptr<UIObjectRenderData> CreateHighlight(UIObjectType type, float xPercentage, float yPercentage, float widthPercentage, float heightPercentage, bool interactable);

	std::shared_ptr<Text> _text = nullptr;
	std::vector<std::shared_ptr<Text>> _choiceText;

	// Texture button offset. Determinates textures drawn and result of button press
	int _tOffset = 0;
	int _oOffset = 0;

	void RenderUI(bool editor);
	
	ClickResponse IdentifyClick(glm::vec2 loc, int& elementID);

	bool IsHoveringEditorUI(glm::vec2 loc) const
	{
		float newY = loc.y;

		for (auto& render : _gameOverlayRenders)
		{
			if (loc.x >= render->xStart && loc.x <= render->xEnd &&
				newY >= render->yStart && newY <= render->yEnd)
			{
				return true;
			}
		}

		for (auto& render : _editorRenders)
		{
			if (loc.x >= render->xStart && loc.x <= render->xEnd &&
				newY >= render->yStart && newY <= render->yEnd)
			{
				return true;
			}
		}

		return false;
	}
	
	void DrawObjects();

	void DrawHighlight(std::shared_ptr<UIObjectRenderData> render);
	void DrawEditorButtons();

	void UpdateUIOnFramebufferResize(int newWidth, int newHeight);


	void AddTextureOffset(int offset);
	void AddObjectOffset(int offset);

	//glm::mat4* _proj;
	glm::mat4 _newProj;

	bool GetIsSolid() const { return _collision; }
	int GetLayer() const { return _layer; }
	int GetUIView() const { return _view; }

	inline int GetTextureID() const { return _textureID; }
	void SetTextureID(int id)
	{
		_textureID = id;
	}

	std::string GetObjectName() const;
	
	void SetObjectID(int id)
	{
		_objectID = id;
	}

	void SetChoiceLines(std::vector<std::string> lines)
	{

	}

protected:

	std::vector<std::shared_ptr<UIObjectRenderData>> _choiceButtons;

	std::vector<std::shared_ptr<UIObjectRenderData>> _editorTextureButtons;
	std::vector<std::shared_ptr<UIObjectRenderData>> _objectButtons;
	std::vector<std::shared_ptr<UIObjectRenderData>> _editorButtons;
	std::vector<std::shared_ptr<UIObjectRenderData>> _editorRenders;
	std::vector<std::shared_ptr<UIObjectRenderData>> _buttons;

	std::shared_ptr<UIObjectRenderData> _layerButton;
	std::shared_ptr<UIObjectRenderData> _viewButton;
	std::vector<std::shared_ptr<UIObjectRenderData>> _gameOverlayRenders;
	std::vector<std::shared_ptr<UIObjectRenderData>> _dialogRenders;
	std::vector<std::shared_ptr<UIObjectRenderData>> _choiceRenders;

	std::shared_ptr<UIObjectRenderData> _selectedObject;
	std::shared_ptr<UIObjectRenderData> _collisionButton;

	std::shared_ptr<UIObjectRenderData> _vnBox = nullptr;
	std::shared_ptr<UIObjectRenderData> _vnLeftCharacterBox;
	std::shared_ptr<UIObjectRenderData> _vnRightCharacterBox;

	std::shared_ptr<UIObjectRenderData> _choiceBox = nullptr;


	int _frameBufferX, _frameBufferY;

	int _lastClickedTexture = 0;
	int _lastClickedObject = 0;

	bool _collision = false;
	int _layer = 0;
	int _view = 0;
	bool _editor = false;

	const int _dialogTextSize = 36;
	const int _choiceTextSize = 24;

	Renderer* _renderer;

	int _textureID = 0;
	int _objectID = 0;


};

