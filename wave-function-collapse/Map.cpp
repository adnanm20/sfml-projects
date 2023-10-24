#include "./Map.hpp"
#include <iostream>

Map::Map(unsigned int width, unsigned int height, unsigned int textureSize, float scale)
{
	for (int i = 0; i < width/scale; ++i)
	{
		std::vector<Tile> temp_;
		for (int j = 0; j < height/scale; ++j)
		{
			Tile tile;
			tile.setPosition(i, j, textureSize, scale);
			temp_.push_back(tile);
		}
		_tiles.push_back(temp_);
	}
}

void Map::loadTextures(std::string tileConnectionsFileName, std::string texturesPath, std::string texturesExtension = "png")
{
	int textureCount = _textures.load(tileConnectionsFileName, texturesPath, texturesExtension);
	for (int i = 0; i < _tiles.size(); ++i)
		for (int j = 0; j < _tiles[0].size(); ++j)
			_tiles[i][j].setPossibleTiles(textureCount);
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
	}
	if (y + 1 < _tiles[0].size())
	{
		bD = _tiles[x][y + 1].filterPossibleTiles(_tiles[x][y].possibleTiles(Directions::south, _textures));
	}
	if (x - 1 > -1)
	{
		bL = _tiles[x - 1][y].filterPossibleTiles(_tiles[x][y].possibleTiles(Directions::east, _textures));
	}
	if (x + 1 < _tiles.size())
	{
		bR = _tiles[x + 1][y].filterPossibleTiles(_tiles[x][y].possibleTiles(Directions::west, _textures));
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
	int x = -1, y = -1;
	int minEntropy = _textures.size();
	for (int i = 0; i < _tiles.size(); ++i)
	{
		for (int j = 0; j < _tiles[0].size(); ++j)
		{
			if (_tiles[i][j].type() != -1)
				continue;
			int t = _tiles[i][j].getEntropy();
			if (t < minEntropy)
			{
				x = i;
				y = j;
				minEntropy = t;
			}
		}
	}
	if (x == -1)
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
}
