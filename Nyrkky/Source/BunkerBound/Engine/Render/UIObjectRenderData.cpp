#include "UIObjectRenderData.h"
#include "../../GameData.h"


UIObjectRenderData::UIObjectRenderData(std::shared_ptr<TileRenderData> data, float x, float y, float xSize, float ySize, bool interactable, std::shared_ptr<UIObjectRenderData> highlight, int ID)
{
    _highlight = highlight;
    _ID = ID;
    // Define Buffer
    _tileRenderData = data;
    std::vector<float> positions;
    std::vector<unsigned int> indices;
    xStart = x;
    yStart = y;
    xEnd = (x + xSize);
    yEnd = (y + ySize);
    _interactable = interactable;

    AddVertex(positions, xStart, yStart, 0.f, 1.f, 0);
    AddVertex(positions, xEnd, yStart, 1.f, 1.f, 0);
    AddVertex(positions, xStart, yEnd, 0.f, 0.f, 0);
    AddVertex(positions, xEnd, yEnd, 1.f, 0.f, 0);

    AddIndex(indices, 0, 1, 2);
    AddIndex(indices, 3, 2, 1);

    /**/
    unsigned int vertexArrayID;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _vb = new VertexBuffer(positions.data(), positions.size() * sizeof(float), true);
    _layout = new VertexBufferLayout();
    _va = new VertexArray();
    // --------------------------------------------------------------------------

    _layout->Push<float>(2);
    _layout->Push<float>(2);
    _layout->Push<float>(1);
    /**/
    _va->AddBuffer(*_vb, *_layout);
    // -----

    // Setup Index buffer
    _ib = new IndexBuffer(indices.data(), indices.size());
    _ib->Bind();
    // -----

    // Texture Init
    //_texture = std::make_unique<Texture>("../Nyrkky/Resources/Textures/test.png", true);
    //_texture = texture;
    /**/
    _initialized = true;
}

UIObjectRenderData::~UIObjectRenderData()
{
    Clean();
}

void UIObjectRenderData::Init(float x, float y, float xSize, float ySize)
{

}

bool UIObjectRenderData::Updater()
{
    if (_initialized)
    {
        if (_tileRenderData != nullptr)
        {
            GameData::GetShader()->Bind();

            // Bind the texture array
            if (GameData::GetTextureArray() != nullptr)
            {
                GameData::GetTextureArray()->Bind();

                //ameData::GetShader()->SetUniform1i("u_Layer", GameData::GetTextureIndex("121.png"));
            }
            /*
            GameData::GetShader()->Bind();
            int textureID = _tileRenderData->GetTexID();
            _tileRenderData->GetTexture()->Bind(textureID);
            GameData::GetShader()->SetUniform1i("u_Textures[" + std::to_string(textureID) + ']', textureID);
            */
            std::vector<float> positions;
            int texIndex = tekstuuriID;

            AddVertex(positions, xStart, yEnd,
                0.0f, 1.0f, texIndex);

            AddVertex(positions, xEnd, yEnd,
                1.0f, 1.0f, texIndex);

            AddVertex(positions, xStart, yStart,
                0.0f, 0.0f, texIndex);

            AddVertex(positions, xEnd, yStart,
                1.0f, 0.0f, texIndex);


            /*
            AddVertex(positions, xStart, yEnd,
                _tileRenderData->UV_x * _tileRenderData->SpriteW / _tileRenderData->SheetW,
                _tileRenderData->UV_y * _tileRenderData->SpriteH / _tileRenderData->SheetH, texIndex);

            AddVertex(positions, xEnd, yEnd,
                (_tileRenderData->UV_x + 1) * _tileRenderData->SpriteW / _tileRenderData->SheetW,
                _tileRenderData->UV_y * _tileRenderData->SpriteH / _tileRenderData->SheetH, texIndex);

            AddVertex(positions, xStart, yStart,
                _tileRenderData->UV_x * _tileRenderData->SpriteW / _tileRenderData->SheetW,
                (_tileRenderData->UV_y + 1) * _tileRenderData->SpriteH / _tileRenderData->SheetH, texIndex);

            AddVertex(positions, xEnd, yStart,
                (_tileRenderData->UV_x + 1) * _tileRenderData->SpriteW / _tileRenderData->SheetW,
                (_tileRenderData->UV_y + 1) * _tileRenderData->SpriteH / _tileRenderData->SheetH, texIndex);
            */

            _vb->Bind();
            _vb->Update(positions.data(), positions.size() * sizeof(float));
            return true;
        }
        std::cout << "UI renderer nullptr - updater" << std::endl;
        return false;
    }
    else std::cout << "generic object renderer not initalized!" << std::endl;
    return false;
}



void UIObjectRenderData::Update()
{
    if (_tileRenderData != nullptr)
    {
        int slot = _tileRenderData->GetTexID();
        //_tileRenderData->GetTexture()->Bind(slot);

        GameData::GetShader()->SetUniform1i("u_Textures[" + std::to_string(slot) + ']', slot);
    }
    else std::cout << "UI renderer nullptr - update" << std::endl;
}


void UIObjectRenderData::Init(int PosX, int PosY)
{
}

bool UIObjectRenderData::Activate(int PosX, int PosY)
{
    return false;
}

void UIObjectRenderData::AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex) {
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    x.push_back(v4);
    x.push_back(texIndex);
}

void UIObjectRenderData::AddIndex(std::vector<unsigned int>& x, float v1, float v2, float v3) {
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
}