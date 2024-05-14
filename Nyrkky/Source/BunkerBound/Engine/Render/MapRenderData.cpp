#include "MapRenderData.h"
#include "../../GameData.h"

MapRenderData::MapRenderData(int layer, int ScreenX, int ScreenY, int gridSize, int tileSize)
{
    std::cout << "map render data init" << std::endl;
    _layer = layer;
    Update(ScreenX, ScreenY, gridSize, tileSize);
}

void MapRenderData::Update(int ScreenX, int ScreenY, int gridSize, int tileSize)
{
    GridSize = gridSize;
    TileSize = tileSize;
    windowX = ScreenX;
    windowY = ScreenY;
    //_tileTypes = types;
    //_tiles = tiles;
}

MapRenderData::~MapRenderData()
{
    Clean();
}

void MapRenderData::Init(int PosX, int PosY)
{
    // Define Buffer
    //std::vector<float> positions;

    std::vector<unsigned int> indices;
    //std::cout << "GridSize " << GridSize << std::endl;
    //std::cout << "types size " << tileTypes.size() << std::endl;
    glm::vec2 centerOfMap = { -windowX * 0.33, -windowY * 0.75 };

    for (int y = 0; y < GridSize; y++)
    {
        for (int x = 0; x < GridSize; x++) {
            int index = y * GridSize + x;
            
            /*
            TileRenderData* data;

            data = &_tiles[index];
            */
            int textureID;
           if (GameData::GetMap() != nullptr && GameData::GetMap()->_tiles.size() > index)
            {
                textureID = GameData::GetMap()->_tiles[index].GetTexture();
                //std::cout << "tiles size: " << GameData::GetMap()->_tiles.size() << std::endl;
            }
            else textureID = 0;

            

            //int textureID = GameData::GetTextureIndex("StoneFloor01.png");

            AddVertex(positions, TileSize * x, -TileSize * y,
                0.0f, 0.0f, textureID);

            AddVertex(positions, TileSize * (x + 1), -TileSize * y,
                1.0f, 0.0f, textureID);

            AddVertex(positions, TileSize * x, -TileSize * (y + 1),
                0.0f, 1.0f, textureID);

            AddVertex(positions, TileSize * (x + 1), -TileSize * (y + 1),
                1.0f, 1.0f, textureID);
            

            /*
            AddVertex(positions, TileSize * x, -TileSize * y, 0.f, 0.f, textureID);
            AddVertex(positions, TileSize * (x + 1), -TileSize * y, 1.f, 0.f, textureID);
            AddVertex(positions, TileSize * x, -TileSize * (y + 1), 0.f, 1.f, textureID);
            AddVertex(positions, TileSize * (x + 1), -TileSize * (y + 1), 1.f, 1.f, textureID);
            */


            int counter = (x * 4) + (y * GridSize * 4);
            //std::cout << counter << std::endl;
            AddIndex(indices, 0 + counter, 1 + counter, 2 + counter);
            AddIndex(indices, 3 + counter, 2 + counter, 1 + counter);
        }
    }

    /**/
    //unsigned int vertexArrayID;
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _vb = new VertexBuffer(positions.data(), positions.size() * sizeof(float));
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
    /*
    for (int i = 0; i < _tileTypes.size(); i++)
    {
        _textures.push_back(new Texture("../Nyrkky/Resources/Textures/world/Plants01.png"));
    }
    */
    _initialized = true;
}
/*
bool MapRenderData::Activate(int PosX, int PosY)
{
    if (_initialized)
    {
        //std::cout << "activate map render" << std::endl;
        GameData::GetShader()->Bind();

        //std::cout << "size: " << _tileTypes.size() << std::endl;
        for (int i = 0; i < _tileTypes.size(); i++)
        {
           
            int slot = _tileTypes[i]->GetTexID();
            _tileTypes[i]->GetTexture()->Bind(slot);
            
            GameData::GetShader()->SetUniform1i("u_Textures[" + std::to_string(slot) + ']', slot);
            //Shader->SetUniform1i("u_Textures[0]", slot);
        }
        return true;
    }
    return false;
}
*/

bool MapRenderData::Activate(int PosX, int PosY)
{
    /**/
    if (_initialized)
    {
        // Bind the shader
        GameData::GetShader()->Bind();

        // Bind the texture array
        GameData::GetTextureArray()->Bind();

        for (int i = 0; i < _tileTypes.size(); i++)
        {
            GameData::GetShader()->SetUniform1i("u_Layer", 0);
        }

        return true;
    }
    return false;
}

void MapRenderData::AddVertex(std::vector<float>& x, float v1, float v2, float v3, float v4, float texIndex) {
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
    x.push_back(v4);
    x.push_back(texIndex);
}

void MapRenderData::AddIndex(std::vector<unsigned int>& x, float v1, float v2, float v3) {
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
}



