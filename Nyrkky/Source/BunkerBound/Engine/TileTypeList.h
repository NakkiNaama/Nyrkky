#pragma once
#include <iostream>
#include "Texture.h"

struct SubTile
{
public:
	SubTile(uint32_t texture, bool solid)
	{
		_texture = texture;
		_solid = solid;
	}

	bool IsSolid() const { return _solid; }
	uint32_t GetTextureID() const { return _texture; }


private:
	bool _solid;
	uint32_t _texture;
};

struct Tile
{
public:
	Tile(std::string name, bool solid, bool hasSub, uint32_t texture, std::shared_ptr<SubTile> sub)
		: _texture(texture)
	{
		_name = name;
		_solid = solid;
		HasSub = hasSub;
		subTile = sub;
	}
	std::string GetTileName() const { return _name; }
	bool IsSolid() const { return _solid; }
	void SetSolid(bool solid)
	{
		_solid = solid;
	}

	bool HasSub;

	uint32_t GetTexture() const
	{
		return _texture;
	}

	void SetSubTile(std::shared_ptr<SubTile> newSub)
	{
		subTile = newSub;
	}

	std::shared_ptr<SubTile> GetSubTile() const
	{
		return subTile;
	}

private:
	std::string _name;
	bool _solid;
	uint32_t _texture;
	std::shared_ptr<SubTile> subTile;
};

class TileTypeList
{

};

