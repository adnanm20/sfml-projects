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

configConnections: connectionMaker.o 
	g++ connectionMaker.o -o connectionMaker.out -lsfml-graphics -lsfml-system

connectionMaker.o: connectionMaker.cpp
	g++ -c connectionMaker.cpp

clean:
	rm *.o