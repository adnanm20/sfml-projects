# SFML projects

Fun projects made using C++ library SFML

## Requirements

You need [SFML](https://www.sfml-dev.org/) installed

Ubuntu:
```bash
sudo apt-get install libsfml-dev
```

## Usage

Every directory is a different project and should contain its own Makefile which you run using make command

## Wave Function Collapse
An example of how we can use wave function collapse to generate different images based on tiles given a set of rules.

Start the program using
```bash
./waveFunctionCollapse.out -i tileConnections.txt
```
Hit space to see the generation run to the end or use n to view each tile being placed. You can reset the image using R. 

Using the connectionMaker you can generate rules for any set of tiles. It checks all edges of every tile and compares to every other tile's edges.
```bash
./connectionMaker.out -i tiles.txt -o circuit2.txt
```

## Falling Sand
My take on the falling sand simulation using [Celullar Automata](https://en.wikipedia.org/wiki/Cellular_automaton).
Idea from [Coding challenge](https://www.youtube.com/watch?v=L4u7Zy_b868).

Start using
```bash
./sand-ca.out
```
Mouse click will add a blob of sand.