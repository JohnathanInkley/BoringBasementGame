// Filename: main.cpp
// Author: Johnathan Inkley
// Date: 2016 10 12
// Description: A simple maze game the user has to navigate

#include <iostream>
#include <fstream>
#include <vector>
#include "maze.h"

int main()
{
  std::ifstream mapFile;
  mapFile.open("map.dat");
  Maze newGame(mapFile);
  return 0;
}

