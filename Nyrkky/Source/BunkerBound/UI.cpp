#include "UI.h"
#include "GameData.h"

UI::UI(int frameBufferX, int frameBufferY)
{

	_frameBufferX = frameBufferX;
	_frameBufferY = frameBufferY;

	_dialogText = std::make_unique<Text>();
	_dialogText->Init(_dialogTextSize);

	_inputText = std::make_unique<Text>();
	_inputText->Init(_dialogTextSize);

	// Choice Text Init
	for (int i = 0; i < 4; i++)
	{
		_choiceText.push_back(std::make_unique<Text>());
	}

	for (auto &t: _choiceText)
	{
		t = std::make_unique<Text>();
		t->Init(_choiceTextSize);
	}
	// --------------------

	CreateGameUI();
	CreateEditorUI();
	
	UpdateUIOnFramebufferResize(_frameBufferX, _frameBufferY);

}

UI::~UI()
{

}

std::shared_ptr<UIObjectRenderData> UI::CreateUIObject(UIObjectType type, uint32_t arrayID, uint32_t texture, float xPercentage, float yPercentage, float widthPercentage, float heightPercentage, bool interactable, int id)
{
	std::shared_ptr<UIObjectRenderData> highlight = nullptr;
	if (type != UIObjectType::ESelection)
	{
		highlight = CreateHighlight(UIObjectType::ESelection, xPercentage, yPercentage, widthPercentage, heightPercentage, true);
		
	}

	float xPosition = _frameBufferX * xPercentage;
	float yPosition = _frameBufferY * yPercentage;
	float elementWidth = _frameBufferX * widthPercentage;
	float elementHeight = _frameBufferY * heightPercentage;

	std::shared_ptr<UIObjectRenderData> element = std::make_unique<UIObjectRenderData>(arrayID, texture, xPosition, yPosition, elementWidth, elementHeight, interactable, highlight, id);


	// should be removed and vector should be parameter or something like that
	switch (type)
	{
	case UIObjectType::EGameOverlay: _gameOverlayRenders.push_back(element); break;
	case UIObjectType::EGameButton: _buttons.push_back(element); break;
	case UIObjectType::EEditorOverlay: _editorRenders.push_back(element); break;
	case UIObjectType::EEditorButton: _editorButtons.push_back(element); break;
	case UIObjectType::EEditorTextureButton: _editorTextureButtons.push_back(element); break;
	case UIObjectType::EDialog: _dialogRenders.push_back(element); break;
	case UIObjectType::EEditorObjectButton: _objectButtons.push_back(element); break;
	case UIObjectType::EChoiceUI: _choiceRenders.push_back(element); break;
	case UIObjectType::EChoiceButton: _choiceButtons.push_back(element); break;
	case UIObjectType::EInventoryOverlay: _inventoryButtons.push_back(element); break;

	}
	/**/

	return element;
}

std::shared_ptr<UIObjectRenderData> UI::CreateHighlight(UIObjectType type, float xPercentage, float yPercentage, float widthPercentage, float heightPercentage, bool interactable)
{
	float hP = xPercentage;
	float wP = yPercentage;
	float xP = widthPercentage;
	float yP = heightPercentage;

	float offset = 0.005f;

	hP -= offset;
	wP -= offset * 1.55f;
	xP += offset * 2.f;
	yP += offset * 2.f * 1.55f;

	std::shared_ptr<UIObjectRenderData> element = CreateUIObject(UIObjectType::ESelection, ETextureArray::EMapTexture, GameData::GetTextureIndex("highlight.png"), hP, wP, xP, yP, true);

	return element;
}

void UI::CreateGameUI()
{
	_vnBox = CreateUIObject(UIObjectType::EDialog, ETextureArray::EMapTexture, GameData::GetTextureIndex("transparent.png"), 0.25f, 0.02f, 0.50f, 0.25f, false); // VN border

	_vnLeftCharacterBox = CreateUIObject(UIObjectType::EDialog, ETextureArray::ECharacterTexture, GameData::GetCharacterTextureIndex("emily_front.png"), 0.f, 0.0f, 0.25f, 0.75f, false);  // Left Character
	_vnRightCharacterBox = CreateUIObject(UIObjectType::EDialog, ETextureArray::ECharacterTexture, GameData::GetCharacterTextureIndex("Arisu.png"), 0.75f, 0.0f, 0.25f, 0.75f, false); // Right Character

	_choiceBox = CreateUIObject(UIObjectType::EChoiceUI, ETextureArray::EMapTexture, GameData::GetTextureIndex("transparent.png"), 0.33f, 0.33f, 0.33f, 0.33f, false); // choice box

	{
		float xP = 0.35f;
		float yP = 0.55f;
		float width = 0.29f;
		float height = 0.08f;
		CreateUIObject(UIObjectType::EChoiceButton, ETextureArray::EMapTexture, GameData::GetTextureIndex("transparent.png"), xP, yP, width, height, true, 0);

		yP -= 0.1f;
		CreateUIObject(UIObjectType::EChoiceButton, ETextureArray::EMapTexture, GameData::GetTextureIndex("transparent.png"), xP, yP, width, height, true, 1);
	}

	_itemBox = CreateUIObject(UIObjectType::EGameOverlay, ETextureArray::EMapTexture, GameData::GetTextureIndex("transparent.png"), 0.0f, 0.0f, 0.2f, 0.1f, false); // Item box

	{
		float heightP = 0.1f / 2;
		float widthP = heightP * 0.545f;
		float xP = 0.006f;
		float yP = 0.025f;
		float xPplus = xP;

		for (int i = 0; i < 5; i++)
		{
			CreateUIObject(UIObjectType::EInventoryOverlay, ETextureArray::EMapTexture, 0, xPplus, yP, widthP, heightP, true, i);
			xPplus += 0.04f;
		}

	}

}

void UI::CreateEditorUI()
{
	CreateUIObject(UIObjectType::EEditorOverlay, ETextureArray::EMapTexture, GameData::GetTextureIndex("transparent.png"), 0.9f, 0.f, 0.1f, 1.f, true); // editor button bg

	_collisionButton = CreateUIObject(UIObjectType::ETypeless, ETextureArray::EMapTexture, GameData::GetTextureIndex("collisionOff.png"), 0.91f, 0.05f, 0.035f, 0.05f, true);
	_layerButton = CreateUIObject(UIObjectType::ETypeless, ETextureArray::EMapTexture, GameData::GetTextureIndex("StoneFloor01.png"), 0.95f, 0.05f, 0.035f, 0.05f, true);
	_viewButton = CreateUIObject(UIObjectType::ETypeless, ETextureArray::EMapTexture, GameData::GetTextureIndex("ObjectView.png"), 0.95f, 0.90f, 0.035f, 0.05f, true);

	float heightP = 0.1f;
	float widthP = heightP * 0.545f;
	float xP = 1.f - widthP - 0.02f;
	float yP = 0.2f;
	float yPplus = yP;

	for (int i = 0 ; i < 5; i++)
	{
		if (GameData::GetTextureArray()->GetSize() > i)
		{
			CreateUIObject(UIObjectType::EEditorTextureButton, ETextureArray::EMapTexture, i, xP, yPplus, widthP, heightP, true, i);
			yPplus += 0.13f;
		}
		else break;
	}

	yPplus = yP;

	for (int i = 0; i < 5; i++)
	{
		if (GameData::GetMapLoader()->_entityTypes.size() > i)
		{
			CreateUIObject(UIObjectType::EEditorObjectButton, ETextureArray::EMapTexture, GameData::GetMapLoader()->_entityTypes[i]->GetFirstTexture(), xP, yPplus, widthP, heightP, true, i);
			yPplus += 0.13f;
		}
		else break;
	}
}


void UI::AddTextureOffset(int offset)
{
	_tOffset += offset;
	if (_tOffset < 0)
	{
		_tOffset = 0;
	}
	else if (_tOffset + _editorButtons.size() > GameData::GetTextureArray()->GetSize()) // GameData::GetMap()->_tileTypes.size()
	{
		_tOffset -= offset;
	}
}

void UI::AddObjectOffset(int offset)
{
	_oOffset += offset;
	if (_oOffset < 0)
	{
		_oOffset = 0;
	}
	else if (_oOffset + _objectButtons.size() > GameData::GetMapLoader()->_entityTypes.size())
	{
		_oOffset -= offset;
	}
}

void UI::DrawHighlight(std::shared_ptr<UIObjectRenderData> render)
{
	
	if (render->GetHighlight() != nullptr)
	{
		
		bool draw = false;
		if (_view == 0)
		{
			if (render->_ID + _tOffset == _lastClickedTexture) draw = true;
		}		
		else
		{
			if (render->_ID + _oOffset == _lastClickedObject) draw = true;
		}
		
		if (draw)
		{
			if (render->GetHighlight()->Update())
			{
				_renderer->Draw(render->GetHighlight()->GetVA(), render->GetHighlight()->GetIB());
			}
		}
		

	}
	
}

void UI::DrawEditorButtons()
{
	int index = 0;
	
	if (_view == 0)
	{
		for (auto& render : _editorTextureButtons)
		{
			if (render != nullptr && render->GetVA() != nullptr && render->GetIB() != nullptr)
			{
				int id = index + _tOffset;
				
				if (GameData::GetTextureArray()->GetSize() > id)
				{
					render->SetTexture(id);

					if (render->Update())
					{
						GameData::GetRenderer()->Draw(render->GetVA(), render->GetIB());
						DrawHighlight(render);

					}
				}
			}
			index++;
		}
	}
	else
	{
		for (auto& render : _objectButtons)
		{
			if (render != nullptr && render->GetVA() != nullptr && render->GetIB() != nullptr)
			{
				int id = index + _oOffset;
				if (GameData::GetMapLoader()->_entityTypes.size() > id)
				{
					render->SetTexture(GameData::GetMapLoader()->_entityTypes[id]->GetFirstTexture());
					if (render->Update())
					{
						GameData::GetRenderer()->Draw(render->GetVA(), render->GetIB());
						DrawHighlight(render);

					}
				}
			}
			index++;
		}
	}

	if (_view == 0)
	{		
		if (_collisionButton != nullptr && _collisionButton->GetVA() != nullptr && _collisionButton->GetIB() != nullptr)
		{
			if (!_collision) _collisionButton->SetTexture(GameData::GetTextureIndex("collisionOff.png"));
			else _collisionButton->SetTexture(GameData::GetTextureIndex("collisionOn.png"));

			if (_collisionButton->Update())
			{
				GameData::GetRenderer()->Draw(_collisionButton->GetVA(), _collisionButton->GetIB());
			}
		}

		if (_layerButton != nullptr && _layerButton->GetVA() != nullptr && _layerButton->GetIB() != nullptr)
		{
			if (_layer == 0) _layerButton->SetTexture(GameData::GetTextureIndex("number_1.png"));
			else _layerButton->SetTexture(GameData::GetTextureIndex("number_2.png"));
			
			if (_layerButton->Update())
			{
				GameData::GetRenderer()->Draw(_layerButton->GetVA(), _layerButton->GetIB());
			}
		}
	}

	if (_viewButton != nullptr && _viewButton->GetVA() != nullptr && _viewButton->GetIB() != nullptr)
	{
		if (_view == 0) _viewButton->SetTexture(GameData::GetTextureIndex("ObjectView.png"));
		else _viewButton->SetTexture(GameData::GetTextureIndex("TerrainView.png"));

		if (_viewButton->Update())
		{
			GameData::GetRenderer()->Draw(_viewButton->GetVA(), _viewButton->GetIB());
		}
	}

}

ClickResponse UI::IdentifyClick(glm::vec2 loc, int& elementID)
{
	int i = 0;
	int newY = int(loc.y);

	if (_editor)
	{
		// Editor Texture Buttons
		for (auto& render : _editorTextureButtons)
		{
			if (loc.x >= render->xStart && loc.x <= render->xEnd &&
				newY >= render->yStart && newY <= render->yEnd)
			{
				elementID = i;
				if (_view == 0)
				{
					elementID += _tOffset;
					_lastClickedTexture = elementID;
				}
				else
				{
					elementID += _oOffset;
					_lastClickedObject = elementID;
				}

				std::cout << "editor button " << elementID << " clicked!" << std::endl;
				_selectedObject = render;
				return EEditorButtonClick;
			}
			i++;
		}
		i = 0;

		// Editor Buttons
		for (auto& render : _editorButtons)
		{
			if (loc.x >= render->xStart && loc.x <= render->xEnd &&
				newY >= render->yStart && newY <= render->yEnd)
			{
				std::cout << "editor button " << elementID << " clicked!" << std::endl;
				elementID = i;
				return EEditorButtonClick;
			}
			i++;
		}
		i = 0;

		// Buttons
		for (auto& render : _buttons)
		{
			if (loc.x >= render->xStart && loc.x <= render->xEnd &&
				newY >= render->yStart && newY <= render->yEnd)
			{
				std::cout << "button clicked!" << std::endl;
				elementID = i;
				//_selectedObject = render;
				return EEditorButtonClick;
			}
			i++;
		}
		i = 0;

		// Collision Button
		if (loc.x >= _collisionButton->xStart && loc.x <= _collisionButton->xEnd &&
			newY >= _collisionButton->yStart && newY <= _collisionButton->yEnd)
		{
			std::cout << "collision button clicked!" << std::endl;
			if (_collision)
			{
				_collision = false;
			}
			else
			{
				_collision = true;
			}

			return EEditorButtonClick;
		}

		// Layer Button
		if (loc.x >= _layerButton->xStart && loc.x <= _layerButton->xEnd &&
			newY >= _layerButton->yStart && newY <= _layerButton->yEnd)
		{
			std::cout << "layer button clicked!" << std::endl;
			if (_layer != 0)
			{
				_layer = 0;
			}
			else
			{
				_layer = 1;
			}

			return EEditorButtonClick;
		}

		// View Button
		if (loc.x >= _viewButton->xStart && loc.x <= _viewButton->xEnd &&
			newY >= _viewButton->yStart && newY <= _viewButton->yEnd)
		{
			std::cout << "view button clicked!" << std::endl;
			if (_view != 0)
			{
				_view = 0;
			}
			else
			{
				_view = 1;
			}

			return EEditorButtonClick;
		}

		// UI elements that consume clicks
		for (auto& render : _gameOverlayRenders)
		{
			if (loc.x >= render->xStart && loc.x <= render->xEnd &&
				newY >= render->yStart && newY <= render->yEnd)
			{
				std::cout << "UI consumed the click!" << std::endl;
				elementID = i;

				return EStaticElementClick;
			}
			i++;
		}

		// Editor UI elements that consume clicks
		for (auto& render : _editorRenders)
		{
			if (loc.x >= render->xStart && loc.x <= render->xEnd &&
				newY >= render->yStart && newY <= render->yEnd)
			{
				std::cout << "editor UI consumed the click!" << std::endl;
				elementID = i;
				return EStaticElementClick;
			}
			i++;
		}
		i = 0;

	}

	if (GameData::IsChoice())
	{
		// Choice Buttons
		for (auto& render : _choiceButtons)
		{
			if (loc.x >= render->xStart && loc.x <= render->xEnd &&
				newY >= render->yStart && newY <= render->yEnd)
			{
				std::cout << "choice button " << i << " clicked!" << std::endl;
				elementID = i;
				return EButtonClick;
			}
			i++;
		}
		i = 0;
	}

	//_selectedObject = nullptr;
	elementID = -1;
	return ENoneClick;
}

void UI::UpdateUIOnFramebufferResize(int newWidth, int newHeight) 
{
	// Calculate scaling factors for the UI elements based on the new framebuffer size
	float scaleX = static_cast<float>(newWidth) / static_cast<float>(_frameBufferX);
	float scaleY = static_cast<float>(newHeight) / static_cast<float>(_frameBufferY);

	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scaleX, scaleY, 1.0f));
	_newProj = GameData::GetProj() * scaleMatrix;
	GameData::GetShader()->Bind();
	GameData::GetShader()->SetUniformMat4f("u_MVP", _newProj);

	// Update the position and size of each UI element based on the new scaling factors
	for (auto& render : _gameOverlayRenders) {
		render->xStart *= scaleX;
		render->xEnd *= scaleX;
		render->yStart *= scaleY;
		render->yEnd *= scaleY;

	}

	// Store the new framebuffer size for future reference
	_frameBufferX = newWidth;
	_frameBufferY = newHeight;
}

std::string UI::GetObjectName() const
{
	if (GameData::GetMapLoader()->_entityTypes.size() > _objectID)
	{
		return GameData::GetMapLoader()->_entityTypes[_objectID]->GetName();
	}
	return "error";
}

void UI::RenderUI(bool editor)
{
	_editor = editor;

	GameData::GetShader()->Bind();
	GameData::GetShader()->SetUniformMat4f("u_MVP", _newProj);

	DrawObjects();
	if (_editor) DrawEditorButtons();

}

void UI::DrawObjects()
{
	if (_editor)
	{
		for (auto& render : _editorRenders)
		{
			if (render != nullptr && render->GetVA() != nullptr && render->GetIB() != nullptr)
			{
				if (render->Update())
				{
					GameData::GetRenderer()->Draw(render->GetVA(), render->GetIB());
				}
			}
		}
	}

	for (auto& render : _gameOverlayRenders)
	{
		if (render != nullptr && render->GetVA() != nullptr && render->GetIB() != nullptr)
		{
			if (render->Update())
			{
				GameData::GetRenderer()->Draw(render->GetVA(), render->GetIB());
			}
		}
	}

	int itemCount = 0;
	for (auto& render : _inventoryButtons)
	{
		if (render != nullptr && render->GetVA() != nullptr && render->GetIB() != nullptr)
		{
			if (GameData::GetInventory()->GetItems().size() > itemCount)
			{
				render->SetTexture(GameData::GetInventory()->GetItems()[itemCount]->TextureID);
				if (render->Update())
				{
					GameData::GetRenderer()->Draw(render->GetVA(), render->GetIB());
				}
			}
		}
		itemCount++;
	}
	
	if (GameData::IsChoice())
	{
		for (auto& render : _choiceRenders)
		{
			if (render != nullptr && render->GetVA() != nullptr && render->GetIB() != nullptr)
			{
				if (render->Update())
				{
					GameData::GetRenderer()->Draw(render->GetVA(), render->GetIB());
				}
			}
		}

		for (auto& render : _choiceButtons)
		{
			if (render != nullptr && render->GetVA() != nullptr && render->GetIB() != nullptr)
			{
				if (render->Update())
				{
					GameData::GetRenderer()->Draw(render->GetVA(), render->GetIB());
				}
			}
		}
		
		std::vector<Choice> choices = GameData::GetStory()->currentNode->choices;

		for (int ti = 0; ti < _choiceText.size(); ti++)
		{
			if (_choiceButtons.size() > ti && choices.size() > ti)
			{
				float x = _choiceButtons[ti]->xStart;
				float offset = abs(_choiceButtons[ti]->yEnd - _choiceButtons[ti]->yStart) / 2;
				float y = _choiceButtons[ti]->yEnd - offset;
				
				_choiceText[ti]->RenderText(choices[ti].text, int(x), int(y));
			}
		}	
	}

	if (GameData::IsDialogVisible())
	{
		for (auto& render : _dialogRenders)
		{
			if (render != nullptr && render->GetVA() != nullptr && render->GetIB() != nullptr)
			{
				if (render->Update())
				{
					GameData::GetRenderer()->Draw(render->GetVA(), render->GetIB());
				}
			}
		}

		float x = 0;
		float y = 0;
		if (_vnBox != nullptr)
		{
			x = _vnBox->xStart + 50;
			y = _vnBox->yEnd - 75;
		}
		
		_dialogText->RenderText(GameData::GetDialogText(), int(x), int(y));
	}

	_inputText->RenderText(GameData::GetInputText(), 300, 300);
	
}



