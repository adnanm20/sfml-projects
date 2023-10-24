#pragma once
#include <vector>
#include <string>
#include "./Textures.hpp"
#include "./Tile.hpp"

class Map
{
private:
	std::vector<std::vector<Tile>> _tiles;
	Textures _textures;
	int _tilesFilled{0};

public:
	Map(unsigned int, unsigned int, unsigned int, float);
	void loadTextures(std::string, std::string, std::string);
	void drawOn(sf::RenderWindow &);
	void updatePossibilities(int, int);
	Tile &getTileWithLowestEntropy();
	void updateMap();
};
