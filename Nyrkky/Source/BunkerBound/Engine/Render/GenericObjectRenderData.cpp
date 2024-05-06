#include "GenericObjectRenderData.h"
#include "../../GameData.h"


GenericObjectRenderData::GenericObjectRenderData(std::shared_ptr<TileRenderData> data)
{
    _data = data;
    
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

    int textureID = 0;
    
    AddVertex(positions, TileSize * PosX, -TileSize * PosY,
        (_data->UV_x * _data->SpriteW) / _data->SheetW,
        ((_data->UV_y) * _data->SpriteH) / _data->SheetH, textureID);

    AddVertex(positions, TileSize * (PosX + 1), -TileSize * PosY,
        ((_data->UV_x + 1) * _data->SpriteW) / _data->SheetW,
        (_data->UV_y * _data->SpriteH) / _data->SheetH, textureID);

    AddVertex(positions, TileSize * PosX, -TileSize * (PosY + 1),
        ((_data->UV_x) * _data->SpriteW) / _data->SheetW,
        ((_data->UV_y + 1) * _data->SpriteH) / _data->SheetH, textureID);

    AddVertex(positions, TileSize * (PosX + 1), -TileSize * (PosY + 1),
        ((_data->UV_x + 1) * _data->SpriteW) / _data->SheetW,
        ((_data->UV_y + 1) * _data->SpriteH) / _data->SheetH, textureID);
    
    
    /*
    AddVertex(positions, TileSize * PosX, -TileSize * PosY, 0.f, 0.f, 0);
    AddVertex(positions, TileSize * (PosX + 1), -TileSize * PosY, 1.f, 0.f, 0);
    AddVertex(positions, TileSize * PosX, -TileSize * (PosY + 1), 0.f, 1.f, 0);
    AddVertex(positions, TileSize * (PosX + 1), -TileSize * (PosY + 1), 1.f, 1.f, 0);
    */

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

    //_layout->Push<float>(5);
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
    //_texture = std::make_unique<Texture>("../Nyrkky/Resources/Textures/Chest.png");
    _initialized = true;
    Activate(PosX, PosY);

}

bool GenericObjectRenderData::Activate(int PosX, int PosY)
{
    if (_initialized && _data != nullptr)
    {
        GameData::GetShader()->Bind();
        int textureID = 0;
        //_data->GetTexture()->Bind(textureID);
        GameData::GetShader()->SetUniform1i("u_Textures[" + std::to_string(textureID) + ']', textureID);
        
        int TileSize = 64;
        std::vector<float> positions;
        


        AddVertex(positions, TileSize * PosX, -TileSize * PosY,
            (_data->UV_x * _data->SpriteW) / _data->SheetW,
            ((_data->UV_y) * _data->SpriteH) / _data->SheetH, textureID);

        AddVertex(positions, TileSize * (PosX + 1), -TileSize * PosY,
            ((_data->UV_x + 1) * _data->SpriteW) / _data->SheetW,
            (_data->UV_y * _data->SpriteH) / _data->SheetH, textureID);

        AddVertex(positions, TileSize * PosX, -TileSize * (PosY + 1),
            ((_data->UV_x) * _data->SpriteW) / _data->SheetW,
            ((_data->UV_y + 1) * _data->SpriteH) / _data->SheetH, textureID);

        AddVertex(positions, TileSize * (PosX + 1), -TileSize * (PosY + 1),
            ((_data->UV_x + 1) * _data->SpriteW) / _data->SheetW,
            ((_data->UV_y + 1) * _data->SpriteH) / _data->SheetH, textureID);
        
        /*
        AddVertex(positions, TileSize * PosX, -TileSize * PosY, 0.f, 0.f, 0);
        AddVertex(positions, TileSize * (PosX + 1), -TileSize * PosY, 1.f, 0.f, 0);
        AddVertex(positions, TileSize * PosX, -TileSize * (PosY + 1), 0.f, 1.f, 0);
        AddVertex(positions, TileSize * (PosX + 1), -TileSize * (PosY + 1), 1.f, 1.f, 0);
        */

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
