#include "CharacterRenderData.h"
#include "../../GameData.h"

CharacterRenderData::CharacterRenderData(int ScreenX, int ScreenY, std::vector<uint32_t> textures)
{
    _textures = textures;
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

    _initialized = true;
    Activate(PosX, PosY);

}

bool CharacterRenderData::Activate(int PosX, int PosY)
{
    if (_initialized)
    {
        
        GameData::GetShader()->Bind();

        // Bind the texture array
        if (GameData::GetCharacterTextureArray() != nullptr)
        {
            GameData::GetCharacterTextureArray()->Bind();
        }
        

        int TileSize = 64;

        float x = 0;
        float y = 0;

        int characterSize = 1;
        int textureID = 0;

        if (_textures.size() >= 4)
        {
            switch (_lastMovement)
            {
            case Forward: textureID = _textures[2]; break;
            case Right: textureID = _textures[3]; break;
            case Backwards: textureID = _textures[0]; break;
            case Left: textureID = _textures[1]; break;

            default: break;
            }
        }

        std::vector<float> positions;

        AddVertex(positions, TileSize * PosX, -TileSize * (PosY - characterSize),
            0.0f, 0.0f, textureID);
        AddVertex(positions, TileSize * (PosX + 1), -TileSize * (PosY - characterSize),
            1.0f, 0.0f, textureID);
        AddVertex(positions, TileSize * PosX, -TileSize * (PosY + characterSize),
            0.0f, 1.0f, textureID);
        AddVertex(positions, TileSize * (PosX + 1), -TileSize * (PosY + characterSize),
            1.0f, 1.0f, textureID);
        

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








