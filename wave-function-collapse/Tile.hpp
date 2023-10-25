#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "./Textures.hpp"
#include <unordered_set>

class Tile
{
private:
	std::unordered_set<int> _possibleTiles;
	sf::Sprite _sprite;
	sf::Vector2i _position;
	int _currentTile = -1;

public:
	bool filterPossibleTiles(const std::unordered_set<int> &);

	std::unordered_set<int> possibleTiles(Directions, const Textures &) const;

	bool setRandomTileType(Textures &);

	void setPossibleTiles(int ammount)
	{
		for (int i = 0; i < ammount; ++i)
			_possibleTiles.insert(i);
	}

	int type() const
	{
		return _currentTile;
	}

	sf::Vector2i getPosition() const
	{
		return _position;
	}

	int getEntropy() const
	{
		return _possibleTiles.size();
	}

	void setPosition(int x, int y, unsigned int textureSize)
	{
		_sprite.setPosition( textureSize * x, textureSize * y);
		_position = sf::Vector2i(x, y);
	}

	void draw(sf::RenderWindow &window)
	{
		window.draw(_sprite);
	}

};
