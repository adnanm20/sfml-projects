#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>

class Tiles
{
public:
	int tileIndex;
	std::unordered_set<int> _northConnections;
	std::unordered_set<int> _southConnections;
	std::unordered_set<int> _eastConnections;
	std::unordered_set<int> _westConnections;
};

std::string texturesPath, texturesExtension;

void loadTiles(const std::string& filename, std::vector<sf::Image> &images, std::vector<std::string> &names)
{
	std::ifstream ifs;
	// no idea what to do if filename is wrong or file doesn't exist
	ifs.open(filename, std::ifstream::in);

	std::string word;
	ifs >> texturesPath >> texturesExtension;
	while (!ifs.eof())
	{
		ifs >> word;
		names.push_back(word);
		sf::Image img;
		img.loadFromFile(texturesPath + word + "." + texturesExtension);
		images.push_back(img);
	}
}

void printConnectionsToFile(const std::string& filename, int size, std::vector<Tiles> &tiles, std::vector<std::string> &tileNames)
{
	std::ofstream ofs;
	ofs.open(filename, std::ofstream::out);
	ofs << size << '\n'
			<< texturesPath << '\n'
			<< texturesExtension << '\n';
	for (int i = 0; i < tileNames.size(); ++i)
	{
		ofs << tileNames[i] << " ";
	}
	ofs << "\n";
	for (int i = 0; i < tiles.size(); ++i)
	{
		ofs << "# " << tileNames[i] << '\n';
		for (auto conn : tiles[i]._northConnections)
		{
			ofs << tileNames[conn] << " ";
		}
		ofs << "\n/ ";
		for (auto conn : tiles[i]._southConnections)
		{
			ofs << tileNames[conn] << " ";
		}
		ofs << "\n/ ";
		for (auto conn : tiles[i]._eastConnections)
		{
			ofs << tileNames[conn] << " ";
		}
		ofs << "\n/ ";
		for (auto conn : tiles[i]._westConnections)
		{
			ofs << tileNames[conn] << " ";
		}
		ofs << '\n';
	}
}

int main(int argc, char const *argv[])
{
	std::string inputFile, outputFile;
	if (argc != 5)
	{
		std::cout << "please provide input and output file using -i *inputfile* -o *outputfile*" << std::endl;
		return 0;
	}
	else
	{
		for (int i = 0; i < argc; ++i)
		{
			if (std::string{"-i"} == argv[i] && i + 1 < argc)
			{
				inputFile = argv[i+1];
			}
			if (std::string{"-o"} == argv[i] && i + 1 < argc)
			{
				outputFile = argv[i+1];
			}
		}
		if(inputFile == "" || outputFile == "") {
			std::cout << "please provide input and output file using -i *inputfile* -o *outputfile*" << std::endl;
		}
	}

	std::vector<std::string> tileNames_;
	std::vector<sf::Image> images_;
	loadTiles(inputFile, images_, tileNames_);
	std::vector<Tiles> tiles_{images_.size()};
	for (int i = 0; i < tiles_.size(); ++i)
		tiles_[i].tileIndex = i;
	sf::Vector2u imageSize = images_[0].getSize();
	bool flag = true;

	for (int i = 0; i < images_.size(); ++i)
	{
		for (int j = 0; j < images_.size(); ++j)
		{
			// north
			flag = true;
			for (int pixelIndex = 0; pixelIndex < imageSize.x; ++pixelIndex)
			{
				if (images_[i].getPixel(pixelIndex, 0) != images_[j].getPixel(pixelIndex, imageSize.y - 1))
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				tiles_[i]._northConnections.insert(j);
			}
			// south
			flag = true;
			for (int pixelIndex = 0; pixelIndex < imageSize.x; ++pixelIndex)
			{
				if (images_[i].getPixel(pixelIndex, imageSize.y - 1) != images_[j].getPixel(pixelIndex, 0))
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				tiles_[i]._southConnections.insert(j);
			}
			// west
			flag = true;
			for (int pixelIndex = 0; pixelIndex < imageSize.y; ++pixelIndex)
			{
				if (images_[i].getPixel(imageSize.x - 1, pixelIndex) != images_[j].getPixel(0, pixelIndex))
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				tiles_[i]._westConnections.insert(j);
			}
			// east
			flag = true;
			for (int pixelIndex = 0; pixelIndex < imageSize.y; ++pixelIndex)
			{
				if (images_[i].getPixel(0, pixelIndex) != images_[j].getPixel(imageSize.x - 1, pixelIndex))
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				tiles_[i]._eastConnections.insert(j);
			}
		}
	}

	printConnectionsToFile(outputFile, imageSize.x, tiles_, tileNames_);
	return 0;
}
