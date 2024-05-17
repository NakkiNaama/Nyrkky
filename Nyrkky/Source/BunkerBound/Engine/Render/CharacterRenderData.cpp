#include "CharacterRenderData.h"
#include "../../GameData.h"

CharacterRenderData::CharacterRenderData(int ScreenX, int ScreenY, std::string texturePath)
{
    //Init(_shader);
    _textureLoc = texturePath;
}

CharacterRenderData::~CharacterRenderData()
{
    Clean();
}

void CharacterRenderData::Init(int PosX, int PosY)
{
    // Define Buffer
    std::vector<float> positions;
    int TileSize = 64;
    std::vector<unsigned int> indices;

    AddVertex(positions, TileSize * PosX, -TileSize * PosY, 0.f, 0.f, 0);
    AddVertex(positions, TileSize * (PosX + 1), -TileSize * PosY, 1.f, 0.f, 0);
    AddVertex(positions, TileSize * PosX, -TileSize * (PosY + 1), 0.f, 1.f, 0);
    AddVertex(positions, TileSize * (PosX + 1), -TileSize * (PosY + 1), 1.f, 1.f, 0);

    AddIndex(indices, 1, 2, 3);
    AddIndex(indices, 2, 1, 0);

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

    _va->AddBuffer(*_vb, *_layout);


    // Setup Index buffer
    _ib = new IndexBuffer(indices.data(), indices.size());
    _ib->Bind();
    // -----

    // Texture Init
    texture = std::make_unique<Texture>(_textureLoc);

    _initialized = true;
    Activate(PosX, PosY);

}

bool CharacterRenderData::Activate(int PosX, int PosY)
{
    if (_initialized && texture != nullptr)
    {
        
        GameData::GetShader()->Bind();

        // Bind the texture array
        if (GameData::GetCharacterTextureArray() != nullptr)
        {
            GameData::GetCharacterTextureArray()->Bind();

            GameData::GetShader()->SetUniform1i("u_Layer", 0);
        }
               
        int TileSize = 64;

        float x = 0;
        float y = 0;

        float sheetWidth = 128;
        float sheetHeight = 128;
        float spriteSize = 128;
        int characterSize = 1;

        std::vector<float> positions;

        
        AddVertex(positions, TileSize * PosX, -TileSize * (PosY - characterSize),
            (x * spriteSize) / sheetWidth, ((y)* spriteSize) / sheetHeight, 0);
        AddVertex(positions, TileSize * (PosX + 1), -TileSize * (PosY - characterSize),
            ((x + 1)* spriteSize) / sheetWidth, (y * spriteSize) / sheetHeight, 0);
        AddVertex(positions, TileSize * PosX, -TileSize * (PosY + characterSize),
            ((x)* spriteSize) / sheetWidth, ((y + 1)* spriteSize) / sheetHeight, 0);
        AddVertex(positions, TileSize * (PosX + 1), -TileSize * (PosY + characterSize),
            ((x + 1) * spriteSize) / sheetWidth, ((y + 1) * spriteSize) / sheetHeight, 0);
        

        _vb->Bind();
        _vb->Update(positions.data(), positions.size() * sizeof(float));
        return true;
    }
    return false;
}

void CharacterRenderData::AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex) {
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    x.push_back(v4);
    x.push_back(texIndex);
}

void CharacterRenderData::AddIndex(std::vector<unsigned int>& x, float v1, float v2, float v3) {
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
}








