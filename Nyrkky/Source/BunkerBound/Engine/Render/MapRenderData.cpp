#include "MapRenderData.h"
#include "../../GameData.h"

MapRenderData::MapRenderData(int layer, int ScreenX, int ScreenY, int gridSize, int tileSize, int mapID)
{
    _mapID = mapID;
    _layer = layer;
    Update(ScreenX, ScreenY, gridSize, tileSize);
}

void MapRenderData::Update(int ScreenX, int ScreenY, int gridSize, int tileSize)
{
    GridSize = gridSize;
    TileSize = float(tileSize);
    windowX = ScreenX;
    windowY = ScreenY;

}

MapRenderData::~MapRenderData()
{
    Clean();
}

void MapRenderData::Init(int PosX, int PosY)
{
    // Define Buffer
    /**/
    if (GameData::GetMaps().size() <= _mapID)
    {
        std::cerr << "ERROR: map id out of bounds!" << std::endl;
        return;
    }
    std::shared_ptr<MapEntity> map = GameData::GetMaps()[_mapID];

    std::vector<unsigned int> indices;
    glm::vec2 centerOfMap = { -windowX * 0.33, -windowY * 0.75 };

    for (int y = 0; y < GridSize; y++)
    {
        for (int x = 0; x < GridSize; x++) {
            int index = y * GridSize + x;
            
           float textureID;
           if (map != nullptr && map->_tiles.size() > index)
            {
               if (_layer == 0) textureID = float(map->_tiles[index].GetTexture());
               else
               {
                   if (map->_tiles[index].HasSub)
                   {
                       textureID = float(map->_tiles[index].GetSubTile()->GetTextureID());
                   }
                   else textureID = float(GameData::GetTextureIndex("invisible.png"));
               }
                
            }
            else textureID = 0;

            AddVertex(positions, TileSize * x, -TileSize * y,
                0.0f, 0.0f, textureID);

            AddVertex(positions, TileSize * (x + 1), -TileSize * y,
                1.0f, 0.0f, textureID);

            AddVertex(positions, TileSize * x, -TileSize * (y + 1),
                0.0f, 1.0f, textureID);

            AddVertex(positions, TileSize * (x + 1), -TileSize * (y + 1),
                1.0f, 1.0f, textureID);
            

            int counter = (x * 4) + (y * GridSize * 4);
            AddIndex(indices, 0 + counter, 1 + counter, 2 + counter);
            AddIndex(indices, 3 + counter, 2 + counter, 1 + counter);
        }
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    _vb = new VertexBuffer(positions.data(), unsigned int(positions.size()) * sizeof(float));
    _layout = new VertexBufferLayout();
    _va = new VertexArray();
    // --------------------------------------------------------------------------
    
    _layout->Push<float>(2);
    _layout->Push<float>(2);
    _layout->Push<float>(1);
    _va->AddBuffer(*_vb, *_layout);

    // Setup Index buffer
    _ib = new IndexBuffer(indices.data(), unsigned int(indices.size()));
    _ib->Bind();

    _initialized = true;
}

bool MapRenderData::Activate(int PosX, int PosY)
{
    if (_initialized)
    {
        // Bind the shader
        GameData::GetShader()->Bind();

        // Bind the texture array
        GameData::GetTextureArray()->Bind();

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

void MapRenderData::AddIndex(std::vector<unsigned int>& x, int v1, int v2, int v3) {
    x.push_back(v1);
    x.push_back(v2);
    x.push_back(v3);
}



