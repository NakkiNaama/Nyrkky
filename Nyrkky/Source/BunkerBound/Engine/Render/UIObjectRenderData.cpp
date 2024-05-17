#include "UIObjectRenderData.h"
#include "../../GameData.h"


UIObjectRenderData::UIObjectRenderData(uint32_t arrayID, uint32_t texture, float x, float y, float xSize, float ySize, bool interactable, std::shared_ptr<UIObjectRenderData> highlight, int ID)
{
    _highlight = highlight;
    _ID = ID;
    _textureArray = arrayID;
     _textureID = texture;

    // Define Buffer
    std::vector<float> positions;
    std::vector<unsigned int> indices;
    xStart = x;
    yStart = y;
    xEnd = (x + xSize);
    yEnd = (y + ySize);


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

    _initialized = true;
}

UIObjectRenderData::~UIObjectRenderData()
{
    Clean();
}

void UIObjectRenderData::Init(float x, float y, float xSize, float ySize)
{

}

bool UIObjectRenderData::Update()
{
    if (_initialized)
    {

        GameData::GetShader()->Bind();

        // Bind the texture array
        /**/
        std::shared_ptr<TextureArray> arr;
        
        switch (_textureArray)
        {
        case 0: arr = GameData::GetTextureArray(); break;
        case 1: arr = GameData::GetCharacterTextureArray(); break;

        default: break;
        }
        
        if (arr != nullptr)
        {
            arr->Bind();
        }

        std::vector<float> positions;
        int texIndex = _textureID;

        AddVertex(positions, xStart, yEnd,
            0.0f, 0.0f, texIndex);

        AddVertex(positions, xEnd, yEnd,
            1.0f, 0.0f, texIndex);

        AddVertex(positions, xStart, yStart,
            0.0f, 1.0f, texIndex);

        AddVertex(positions, xEnd, yStart,
            1.0f, 1.0f, texIndex);

        _vb->Bind();
        _vb->Update(positions.data(), positions.size() * sizeof(float));
        return true;
    }
    else std::cout << "generic object renderer not initalized!" << std::endl;
    return false;
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
