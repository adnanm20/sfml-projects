#include "../Map.hpp"
#include <iostream>

Map::Map(unsigned int resX, unsigned int resY, std::string tileConnectionsFileName)
{
	int textureCount = _textures.load(tileConnectionsFileName, _textureSize);
	for (int i = 0; i < resX / _textureSize; ++i)
	{
		std::vector<Tile> temp_;
		for (int j = 0; j < resY / _textureSize; ++j)
		{
			Tile tile;
			tile.setPosition(i, j, _textureSize);
			tile.setPossibleTiles(textureCount);
			_entropies.push_back(Entr{textureCount, sf::Vector2i{i, j}});
			temp_.push_back(tile);
		}
		_tiles.push_back(temp_);
	}
}

void Map::drawOn(sf::RenderWindow &window)
{
	for (int i = 0; i < _tiles.size(); ++i)
		for (int j = 0; j < _tiles[0].size(); ++j)
			_tiles[i][j].draw(window);
}

void Map::updatePossibilities(int x, int y)
{
	bool bU = false, bD = false, bL = false, bR = false;
	if (y - 1 > -1)
	{
		bU = _tiles[x][y - 1].filterPossibleTiles(_tiles[x][y].possibleTiles(Directions::north, _textures));
		auto it = std::find_if(_entropies.begin(), _entropies.end(), [x, y](Entr a)
													 { return (a._pos.x == x) && (a._pos.y == (y - 1)); });
		if (it != _entropies.end())
			it->_entropy = _tiles[x][y - 1].getEntropy();
	}
	if (y + 1 < _tiles[0].size())
	{
		bD = _tiles[x][y + 1].filterPossibleTiles(_tiles[x][y].possibleTiles(Directions::south, _textures));
		auto it = std::find_if(_entropies.begin(), _entropies.end(), [x, y](Entr a)
													 { return (a._pos.x == x) && (a._pos.y == (y + 1)); });
		if (it != _entropies.end())
			it->_entropy = _tiles[x][y + 1].getEntropy();
	}
	if (x - 1 > -1)
	{
		bL = _tiles[x - 1][y].filterPossibleTiles(_tiles[x][y].possibleTiles(Directions::east, _textures));
		auto it = std::find_if(_entropies.begin(), _entropies.end(), [x, y](Entr a)
													 { return (a._pos.x == (x - 1)) && (a._pos.y == y); });
		if (it != _entropies.end())
			it->_entropy = _tiles[x - 1][y].getEntropy();
	}
	if (x + 1 < _tiles.size())
	{
		bR = _tiles[x + 1][y].filterPossibleTiles(_tiles[x][y].possibleTiles(Directions::west, _textures));
		auto it = std::find_if(_entropies.begin(), _entropies.end(), [x, y](Entr a)
													 { return (a._pos.x == (x + 1)) && (a._pos.y == y); });
		if (it != _entropies.end())
			it->_entropy = _tiles[x + 1][y].getEntropy();
	}
	if (bU)
		updatePossibilities(x, y - 1);
	if (bD)
		updatePossibilities(x, y + 1);
	if (bL)
		updatePossibilities(x - 1, y);
	if (bR)
		updatePossibilities(x + 1, y);
}

Tile &Map::getTileWithLowestEntropy()
{
	int x, y, i = 0;
	do
	{
		x = _entropies[i]._pos.x;
		y = _entropies[i]._pos.y;
		++i;
	} while(_tiles[x][y].type() != -1);

	if (_entropies[0]._entropy == _textures.size())
	{
		x = rand() % _tiles.size();
		y = rand() % _tiles[0].size();
	}
	return _tiles[x][y];
}

void Map::updateMap()
{
	if (_tilesFilled == _tiles.size() * _tiles[0].size())
	{
		return;
	}
	Tile &tileWithLowestEntropy = getTileWithLowestEntropy();
	sf::Vector2i pos = tileWithLowestEntropy.getPosition();
	tileWithLowestEntropy.setRandomTileType(_textures);
	updatePossibilities(pos.x, pos.y);
	++_tilesFilled;
	std::sort(_entropies.begin(), _entropies.end(), [](Entr a, Entr b)
						{ return a._entropy < b._entropy; });
}

void Map::reset()
{
	unsigned int resX = _tiles.size(), resY = _tiles[0].size();
	_tiles.clear();
	_entropies.clear();
	for (int i = 0; i < resX / _scale; ++i)
	{
		std::vector<Tile> temp_;
		for (int j = 0; j < resY / _scale; ++j)
		{
			Tile tile;
			tile.setPosition(i, j, _textureSize);
			temp_.push_back(tile);
		}
		_tiles.push_back(temp_);
	}
	_tilesFilled = 0;
	int textureCount = _textures.size();
	for (int i = 0; i < _tiles.size(); ++i)
	{
		for (int j = 0; j < _tiles[0].size(); ++j)
		{
			_tiles[i][j].setPossibleTiles(textureCount);
			_entropies.push_back(Entr{textureCount, sf::Vector2i{i, j}});
		}
	}
}
