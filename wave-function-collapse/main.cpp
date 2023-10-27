#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <random>
#include <time.h>
#include <algorithm>
#include <iterator>
#include <queue>
#include <functional>
#include <iostream>
#include "./Map.hpp"
#include "./Tile.hpp"

int main(int argc, char const *argv[])
{
	std::string inputFile;
	if(argc != 3) {
		std::cout << "Please provide an input file for tiles using -i  *inputFile*" << std::endl;
		return 0;
	} else {
		if(std::string{"-i"} == argv[1]) {
			inputFile = argv[2];
		}
	}
	
	int resX = 1920, resY = 1080;
	Map map(resX, resY, inputFile);

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(resX, resY), "Wave Function Collapse!", sf::Style::Fullscreen);

	sf::View customView;
	customView.reset(sf::FloatRect(0, 0, resX, resY));
	window.setView(customView);
	bool startMapCreation = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				customView.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
				window.setView(customView);
			}
			else if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					startMapCreation = true;
				}
				else if (event.key.code == sf::Keyboard::R)
				{
					map.reset();
					startMapCreation = false;
				}
				else if (event.key.code == sf::Keyboard::N)
				{
					map.updateMap();
				}
			}
		}

		if (startMapCreation)
			map.updateMap();

		window.clear();

		map.drawOn(window);

		window.display();
	}

	return 0;
}
