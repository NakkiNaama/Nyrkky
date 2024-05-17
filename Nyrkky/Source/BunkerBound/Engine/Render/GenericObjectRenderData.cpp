#include "GenericObjectRenderData.h"
#include "../../GameData.h"


GenericObjectRenderData::GenericObjectRenderData()
{
    
}

GenericObjectRenderData::~GenericObjectRenderData()
{
    Clean();
}



void GenericObjectRenderData::Init(int PosX, int PosY)
{
    // Define Buffer
    std::vector<float> positions;
    int TileSize = 64;
    std::vector<unsigned int> indices;

    int textureID = 11;

    AddVertex(positions, TileSize * PosX, -TileSize * PosY,
        0.0f, 0.0f, textureID);

    AddVertex(positions, TileSize * (PosX + 1), -TileSize * PosY,
        1.0f, 0.0f, textureID);

    AddVertex(positions, TileSize * PosX, -TileSize * (PosY + 1),
        0.0f, 1.0f, textureID);

    AddVertex(positions, TileSize * (PosX + 1), -TileSize * (PosY + 1),
        1.0f, 1.0f, textureID);
    
    AddIndex(indices, 1, 2, 3);
    AddIndex(indices, 2, 1, 0);


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
    _initialized = true;
    Activate(PosX, PosY);

}

bool GenericObjectRenderData::Activate(int PosX, int PosY)
{
    if (_initialized)
    {
        GameData::GetShader()->Bind();
        int textureID = _texID;

        int TileSize = 64;
        std::vector<float> positions;

        
        AddVertex(positions, TileSize * PosX, -TileSize * PosY,
            0.0f, 0.0f, textureID);

        AddVertex(positions, TileSize * (PosX + 1), -TileSize * PosY,
            1.0f, 0.0f, textureID);

        AddVertex(positions, TileSize * PosX, -TileSize * (PosY + 1),
            0.0f, 1.0f, textureID);

        AddVertex(positions, TileSize * (PosX + 1), -TileSize * (PosY + 1),
            1.0f, 1.0f, textureID);
        
        _vb->Bind();
        _vb->Update(positions.data(), positions.size() * sizeof(float));
        return true;
    }
    else std::cout << "generic object renderer not initalized!" << std::endl;
    return false;
}

void GenericObjectRenderData::AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex) {
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    x.push_back(v4);
    x.push_back(texIndex);
}

void GenericObjectRenderData::AddIndex(std::vector<unsigned int>& x, float v1, float v2, float v3) {
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
}
