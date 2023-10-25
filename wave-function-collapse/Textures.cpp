#include "./Textures.hpp"

std::unordered_set<int> Textures::getConnections(int textureIndex, Directions direction) const
{
	switch (direction)
	{
	case north:
		return _textures[textureIndex]._northConnections;
		break;
	case south:
		return _textures[textureIndex]._southConnections;
		break;
	case east:
		return _textures[textureIndex]._eastConnections;
		break;
	case west:
		return _textures[textureIndex]._westConnections;
		break;
	default:
		return std::unordered_set<int>{};
		break;
	}
}

int Textures::load(std::string tileConnectionsFileName, unsigned int &textureSize)
{
	std::ifstream ifs;
	// no idea what to do if filename is wrong or file doesn't exist
	ifs.open(tileConnectionsFileName, std::ifstream::in);

	std::string word, texturesPath, texturesExtension;
	ifs >> textureSize >> texturesPath >> texturesExtension;
	int tileIndex = -1;
	bool hashFlag = false;
	Directions direction = north;
	while (!ifs.eof())
	{
		ifs >> word;
		if (!hashFlag && word != "#")
		{
			_textureNames.push_back(word);
			Texture tx;
			tx._texture.loadFromFile(texturesPath + word + "." + texturesExtension);
			_textures.push_back(tx);
		}
		else if (word == "#")
		{
			direction = north;
			hashFlag = true;
			ifs >> word;
			for (int i = 0; i < _textureNames.size(); ++i)
			{
				if (_textureNames[i] == word)
				{
					tileIndex = i;
					break;
				}
			}
		}
		else if (word == "/")
		{
			switch (direction)
			{
			case north:
				direction = south;
				break;
			case south:
				direction = east;
				break;
			case east:
				direction = west;
				break;
			}
		}
		else
		{
			int t = -1;
			for (int i = 0; i < _textureNames.size(); ++i)
			{
				if (_textureNames[i] == word)
				{
					t = i;
					break;
				}
			}

			switch (direction)
			{
			case north:
				_textures[tileIndex]._northConnections.insert(t);
				break;
			case south:
				_textures[tileIndex]._southConnections.insert(t);
				break;
			case east:
				_textures[tileIndex]._eastConnections.insert(t);
				break;
			case west:
				_textures[tileIndex]._westConnections.insert(t);
				break;
			}
		}
	}
	return _textureNames.size();
}
