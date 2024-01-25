#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

enum State {
	None,
	Some1,
	Some2,
	Some3
};

void setPixel(sf::Image &img, int x1, int y1, int width, const sf::Color &clr) {
	int x = x1*width, y = y1*width;
	for(int i = 0; i < width; ++i)
		for(int j = 0; j < width; ++j)
			img.setPixel(x+i, y+j, clr);
}

void updateMap(std::vector<std::vector<State>> &map) {
	srand(time(NULL));
	int a = rand()%2 ? -1 : 1;
	for(int i = 0; i < map.size(); ++i) {
		for(int j = map[0].size()-2; j >=0; --j) {
			if(map[i][j] != None) {
				if(map[i][j+1] == None) {
					map[i][j+1] = map[i][j];
					map[i][j] = None;
				}
				else if (i+a >= 0 && i+a < map.size() && map[i+a][j+1] == None) {
					map[i+a][j+1] = map[i][j];
					map[i][j] = None;
				}
				else if (i+a >= 0 && i-a < map.size() && map[i-a][j+1] == None) {
					map[i-a][j+1] = map[i][j];
					map[i][j] = None;
				}
			}
		}
	}
}

void updateImage(sf::Sprite &mapSprite, sf::Texture &mapTexture, sf::Image &mapImage, std::vector<std::vector<State>> &map) {
	static std::vector<sf::Color> colors;
	static int num_of_colors = 3;
	colors.push_back(sf::Color::Black);
	colors.push_back(sf::Color{246, 215, 176});
	colors.push_back(sf::Color{236, 204, 162});
	colors.push_back(sf::Color{225, 191, 146});
	int width = mapImage.getSize().x/map.size();
	for(int i = 0; i < map.size(); ++i) {
		for(int j = 0; j < map[0].size(); ++j) {
			setPixel(mapImage, i, j, width, colors[map[i][j]]);
		}
	}
	mapTexture.loadFromImage(mapImage);
	mapSprite.setTexture(mapTexture);	
}

void placeSandBlob(int x, int y, int size, std::vector<std::vector<State>> &map) {
	if(!(x>=0 && x < map.size())) return;
	if(!(y>=0 && y < map[0].size())) return;

	for(int i = x-size; i < x+size; ++i) {
		if(!(i>=0 && i < map.size())) continue;
		for(int j = y-size; j < y+size; ++j) {
			if(!(j>=0 && j < map[0].size())) continue;
			map[i][j] = State(rand()%3+1);
		}
	}
}

int main(int argc, char* argv[])
{
  int resX = 800, resY = 800;

  sf::ContextSettings settings;
  settings.antialiasingLevel = 10.0;
  
  sf::RenderWindow window(sf::VideoMode(resX, resY), "Sand Falling!", sf::Style::Default, settings);
	window.setFramerateLimit(60);
  
  sf::View view;
  view.reset(sf::FloatRect(0, 0, resX, resY));
  window.setView(view);
  

	const unsigned int grainWidth = 5;
	std::vector<std::vector<State>> map(resX/grainWidth, std::vector<State>(resY/grainWidth, None));
	sf::Image mapImage;
	mapImage.create(resX, resY, sf::Color::Black);
	sf::Texture mapTexture;
	mapTexture.loadFromImage(mapImage);
  sf::Sprite mapSprite;
	mapSprite.setTexture(mapTexture);
	updateImage(mapSprite, mapTexture, mapImage, map);
	map[24][24] = State(rand()%3+1);
	map[24][54] = State(rand()%3+1);
	map[24][55] = State(rand()%3+1);
	map[24][120] = State(rand()%3+1);
	map[25][24] = State(rand()%3+1);

  bool resizedWindow = false;

	bool placeSand = false;
	int pSX = -1;
	int pSY = -1;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
			if (event.type == sf::Event::Closed) {
        std::cout << "Closing window" << std::endl;
        window.close();
      }
			else if (event.type == sf::Event::MouseButtonPressed) {
				placeSand = true;
				pSX = event.mouseButton.x/grainWidth;
				pSY = event.mouseButton.y/grainWidth;
			}
			else if (event.type == sf::Event::MouseButtonReleased) {
				placeSand = false;
			}
			else if (event.type == sf::Event::MouseMoved) {
				pSX = event.mouseMove.x/grainWidth;
				pSY = event.mouseMove.y/grainWidth;
			}
    }

		if(placeSand) {
			placeSandBlob(pSX, pSY, 10, map);
		}

		updateMap(map);
		updateImage(mapSprite, mapTexture, mapImage, map);

    window.clear();
		window.draw(mapSprite);
    window.display();
  }
  return 0;
}
