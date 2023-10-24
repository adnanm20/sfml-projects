#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <unordered_set>

enum Directions
{
	north = 0,
	south = 1,
	east = 2,
	west = 3
};

class Textures
{
private:
	class Texture
	{
	public:
		sf::Texture _texture;
		std::unordered_set<int> _northConnections;
		std::unordered_set<int> _southConnections;
		std::unordered_set<int> _eastConnections;
		std::unordered_set<int> _westConnections;
	};
	std::vector<std::string> _textureNames;
	std::vector<Texture> _textures;

public:
	sf::Texture& operator[](int index)
	{
		return _textures[index]._texture;
	}

	int size() const
	{
		return _textureNames.size();
	}
	std::unordered_set<int> getConnections(int, Directions) const;

	int load(std::string, std::string, std::string);
};