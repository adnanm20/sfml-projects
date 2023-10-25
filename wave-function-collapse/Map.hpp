#pragma once
#include <vector>
#include <string>
#include <map>
#include "./Textures.hpp"
#include "./Tile.hpp"

class Map
{
private:
	struct Entr {
		int _entropy;
		sf::Vector2i _pos;
		Entr(int e, sf::Vector2i p) : _entropy{e}, _pos{p} {}
	};
	std::vector<std::vector<Tile>> _tiles;
	std::vector<Entr> _entropies;
	Textures _textures;
	int _tilesFilled{0};
	unsigned int _textureSize;
	float _scale{1};

public:
	Map(unsigned int, unsigned int, std::string);
	void drawOn(sf::RenderWindow &);
	void updatePossibilities(int, int);
	Tile &getTileWithLowestEntropy();
	void updateMap();
	void reset();
};
