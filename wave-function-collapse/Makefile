compile: main.o Map.o Textures.o Tile.o
	g++ main.o Map.o Textures.o Tile.o -o waveFunctionCollapse.out -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

Map.o: Map.cpp Map.hpp
	g++ -c Map.cpp

Textures.o: Textures.cpp Textures.hpp
	g++ -c Textures.cpp

Tile.o: Tile.cpp Tile.hpp
	g++ -c Tile.cpp

clean:
	rm main.o Map.o Textures.o Tile.o