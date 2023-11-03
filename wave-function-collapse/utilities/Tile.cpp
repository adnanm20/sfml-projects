#include "../Tile.hpp"
#include <iostream>

bool Tile::filterPossibleTiles(const std::unordered_set<int> &validTiles)
{
	if (_currentTile != -1)
		return 0;
	bool anyRemoved = false;
	std::vector<int> temp;
	for (auto tile : _possibleTiles)
	{
		auto it = validTiles.find(tile);
		if (it == validTiles.end())
		{
			anyRemoved = true;
			temp.push_back(tile);
		}
	}
	for (auto it : temp)
	{
		_possibleTiles.erase(it);
	}

	return anyRemoved;
}

std::unordered_set<int> Tile::possibleTiles(Directions direction, const Textures &textures) const
{
	if (_currentTile != -1)
	{
		return textures.getConnections(_currentTile, direction);
	}
	std::unordered_set<int> res;
	for (auto tile : _possibleTiles)
	{
		res.merge(textures.getConnections(tile, direction));
	}
	return res;
}

bool Tile::setRandomTileType(Textures &textures)
{
	if (_currentTile != -1)
		return 0;
	std::vector<int> temp;
	for (auto tile : _possibleTiles)
	{
		temp.push_back(tile);
	}
	int randTextIndex = temp[rand() % temp.size()];
	_sprite.setTexture(textures[randTextIndex]);
	_currentTile = randTextIndex;
	return 1;
}
