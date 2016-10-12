// Filename: main.cpp
// Author: Johnathan Inkley
// Date: 2016 10 12
// Description: A simple maze game the user has to navigate

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include "maze.h"

Maze::Maze(std::istream& mapFile)
{
  // Let S denote start, F denote finish and R denote a regular room. Can later have different room types wth different room messages
  // If there is a door between two rooms there will be a either N, S, E, W for the direction, or 0 if no door exists
  // Room messages come afterwards

  // 1) First count number of rooms and generate them as blank rooms
  createRooms(mapFile);
  // 2) Then add doors between all rooms
  addDoors(mapFile);
  // 3) Then add messages to the rooms
  addMessages(mapFile);

  cowardFlag = false;
  // Check if the user quit last time
  char rememberFlag = '0';
  std::ifstream rememberFile;
  rememberFile.open(".unimportantData");
  rememberFile >> rememberFlag;
  rememberFile.close();
  if (rememberFlag == '1')
    std::cout << "Look who's come crawling back...\n\n";

  // Game begins
  std::cout << "Welcome to BBG (boring basement game).\n"
	    << "You have been kidnapped by a monster with a very large basement,\n"
	    << "and you must do your best to find your way out!\n";
  while ((location->type) != 'F')
    {
      promptUser();
    }
  if (!cowardFlag)
    {
      std::cout << "Congratulations player. Please play again soon\n";
      std::ofstream flagRemember;
      flagRemember.open(".unimportantData");
      flagRemember << 0;
      flagRemember.close();
    }
  else
    {
      std::ofstream flagRemember;
      flagRemember.open(".unimportantData");
      flagRemember << 1;
      flagRemember.close();
    }
}


/* Maze::~Maze()
{
  for (int room = 0; room < roomCount; room++)
    {
      delete roomList[room];
    }
  return;
  } */

Maze::Maze(const Maze& aMaze)
{
  roomCount = aMaze.roomCount;
  for (int room = 0; room < roomCount; room++)
    {
      roomList[room] = new Room;
      roomList[room]->type = (aMaze.roomList[room])->type;
      std::strncpy(roomList[room]->message, aMaze.roomList[room]->message, MAX_MSG_SIZE);
    }
    for (int room = 0; room < roomCount; room++)
    {
      for (int otherRoom = 0; otherRoom < roomCount; otherRoom++)
	{
	  if ((aMaze.roomList[room])->north == aMaze.roomList[otherRoom])
	    roomList[room]->north = roomList[otherRoom];
	  else if ((aMaze.roomList[room])->south == aMaze.roomList[otherRoom])
	    roomList[room]->south = roomList[otherRoom];
	  else if ((aMaze.roomList[room])->east == aMaze.roomList[otherRoom])
	    roomList[room]->east = roomList[otherRoom];
	  else if ((aMaze.roomList[room])->west == aMaze.roomList[otherRoom])
	    roomList[room]->north = roomList[otherRoom];
	}
    }

}

void Maze::createRooms(std::istream& mapFile)
{
  roomList.resize(20);
  roomCount = 0;
  char currentChar;
  mapFile.get(currentChar);
  // Do twice as first character is a blank in input
  mapFile.get(currentChar);  
  while (currentChar != '\n')
    {
      roomCount++;
      RoomPtr newRoom;
      newRoom = new Room;
      newRoom->type = currentChar;
      roomList[roomCount-1] = newRoom;
      if (currentChar == 'S') // If this is the starting room, set location to here
	location = roomList[roomCount-1];
      mapFile.get(currentChar);
    }
  return;
}

void Maze::addDoors(std::istream& mapFile)
{
  char currentChar;
  for (int i=0; i < roomCount; i++)
    {
      mapFile.get(currentChar); // Discard as is room letter
      for (int door = 0; door < roomCount; door++)
	{
	  mapFile.get(currentChar); // Get door code for door to roomList[door]
	  switch (currentChar)
	    {
	    case '0':
	      break;
	    case 'N':
	      (roomList[i])->north = roomList[door];
	      break;
	    case 'S':
	      (roomList[i])->south = roomList[door];
	      break;
	    case 'W':
	      (roomList[i])->west = roomList[door];
	      break;
	    case 'E':
	      (roomList[i])->east = roomList[door];
	      break;
	      }
	}
      mapFile.get(currentChar); // Move to next line
    }
}

void Maze::addMessages(std::istream& mapFile)
{
  char currentChar, roomType, typeMessage[MAX_MSG_SIZE];
  mapFile.get(currentChar); // Move to next line so we are ready for messages

  while (!mapFile.eof())
    {
      mapFile.get(currentChar); // Get room type
      mapFile.get(currentChar); // Ignore the space
      mapFile.getline(typeMessage,MAX_MSG_SIZE); // Get the message from the file
      for (int room = 0; room < roomCount; room++)
	{
	  roomType = (roomList[room]->type);
	  if (roomType == currentChar)
	    std::strncpy((roomList[room]->message), typeMessage, MAX_MSG_SIZE);
	}
    }
}

void Maze::promptUser()
{
  std::cout << (location->message) << std::endl << std::endl
	    << "You can see doors around you to the ";
  if (location->north != NULL)
    std::cout << "north ";
  if (location->south != NULL)
    std::cout << "south ";
  if (location->east != NULL)
    std::cout << "east ";
  if (location->west != NULL)
    std::cout << "west ";
  std::cout << "\nWhere do you want to go? (or q to quit)\n";

  char inputChoice;
  bool promptAgain = true;
  std::string moveOptions = "nsewq";
  while (promptAgain)
    {
      std::cin >> inputChoice;
      if (moveOptions.find(inputChoice) == std::string::npos)
	{
	  std::cout << "Please choose from n, s, e or w\n";
	  promptAgain = true;
	}
      else
	{
	  promptAgain = false;
	  switch (inputChoice)
	    {
	    case 'n':
	      location = location->north;
	      break;
	    case 's':
	      location = location->south;
	      break;
	    case 'e':
	      location = location->east;
	      break;
	    case 'w':
	      location = location->west;
	      break;
	    case 'q':
	      std::cout << "How dare you quit BBG!\n";
	      cowardFlag = true;
	      location = roomList[roomCount-1];
	      break;
	    }
	}
    }  
  return;
}
