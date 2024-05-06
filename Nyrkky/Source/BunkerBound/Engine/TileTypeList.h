#pragma once
#include <iostream>
#include "Texture.h"

/*
enum TileName
{
	Black,
	Grey,
	Grass01,
	Grass02,
	Plants01,
	Plants02,
};
*/

struct TileRenderData
{
public:
	TileRenderData(std::string name, std::shared_ptr<Texture> texture, float sheetW, float sheetH, float spriteW, float spriteH, float uvID)
		: _name(name), _texture(texture), SheetW(sheetW), SheetH(sheetH), SpriteW(spriteW), SpriteH(spriteH)
	{
		int rowH = SheetH / SpriteH;
		int rowW = SheetW / SpriteW;

		UV_y = uvID / rowW;
		UV_x = int(uvID) % rowW;

		UV_ID = uvID;

		//std::cout << "uv y: " << UV_y << " ... uv x: " << UV_x << std::endl;
	}

	std::string GetName() const { return _name; }
	//std::shared_ptr<Texture> GetTexture() const { return _texture; }
	uint32_t GetTextureID()
	{
		return NewTex;
	}

	void SetNewTeks(size_t t)
	{
		NewTex = t;
	}

	void SetTextureID(int id)
	{
		_textureID = id;
		_initalized = true;
	}
	int GetTexID() const
	{
		if (_initalized)
		{
			return _textureID;
		}
		std::cout << "Texture ID not initalized!" << std::endl;
		return 0;
	}

	float SheetW = 2560;
	float SheetH = 1664;
	float SpriteW = 128;
	float SpriteH = 128;

	int UV_ID = 0;
	int UV_x = 0;
	int UV_y = 0;

private:
	bool _initalized = false;
	std::string _name;
	int _textureID = -1;
	size_t NewTex = 0;
	std::shared_ptr<Texture> _texture;
};
/*
struct SubTile
{
public:
	SubTile(TileRenderData data)
		: Data(data)
	{
		_solid = solid;
	}

	bool IsSolid() const { return _solid; }
	TileRenderData Data;

private:
	bool _solid;
};
*/
struct Tile
{
public:
	Tile(TileRenderData data, bool solid, bool hasSub, TileRenderData subRender)
		: Data(data), SubData(subRender)
	{
		_solid = solid;
		HasSub = hasSub;
	}
	std::string GetTileName() const { return _name; }
	bool IsSolid() const { return _solid; }
	void SetSolid(bool solid)
	{
		_solid = solid;
	}

	TileRenderData Data;
	TileRenderData SubData;
	bool HasSub;

private:
	std::string _name;
	bool _solid;


};

class TileTypeList
{

};

