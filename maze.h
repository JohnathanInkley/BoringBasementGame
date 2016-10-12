// Filename: maze.h
// Author: Johnathan Inkley
// Date: 2016 10 12
// Description: Class interface for the maze

#ifndef MAZE_H
#define MAZE_H

const int MAX_MSG_SIZE = 20;

struct Room
{
  char message[MAX_MSG_SIZE];
  char type;
  Room *north, *south, *east, *west;
};

typedef Room* RoomPtr;

class Maze
{
 public:
  Maze(std::istream& mapFile);
  // Constructs a maze by reading in from a file the layout
  Maze(const Maze& aMaze);
   ~Maze();
  // Destructor for the maze
  void promptUser();
  // Prompts user with the room's message and asks for direction choice, then moves the user
 private:
  void createRooms(std::istream& mapFile);
  void addDoors(std::istream& mapFile);
  void addMessages(std::istream& mapFile);
  RoomPtr location;
  int roomCount;
  std::vector<RoomPtr> roomList;
  bool cowardFlag;
};

#endif
