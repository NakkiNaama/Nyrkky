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
    float TileSize = 64;
    std::vector<unsigned int> indices;

    float textureID = 11;

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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _vb = new VertexBuffer(positions.data(), unsigned int(positions.size()) * unsigned int(sizeof(float)), true);
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
    _ib = new IndexBuffer(indices.data(), unsigned int(indices.size()));
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
        float textureID = float(_texID);

        float TileSize = 64;
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
        _vb->Update(positions.data(), unsigned int(positions.size()) * unsigned int(sizeof(float)));
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

void GenericObjectRenderData::AddIndex(std::vector<unsigned int>& x, int v1, int v2, int v3) {
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
}
