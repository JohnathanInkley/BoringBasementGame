# BoringBasementGame
BoringBasementGame is a simple program I've made to test my knowledge of classes and nodes. The user finds themself in a basement and has to navigate through rooms to find the exit, by going through doors to the north, south east and west. The map is defined by the user in an input file.

The map is initialised by first reading in a map of the form

 SRRRF
S0E000
RW0SE0
R00N00
R0W00E
F000W0

The top line and first column represent the rooms, with S being start, F being finish and R being regular types of rooms. Each row says, for a given room, what doors there are and where do they lead. For example the first row has a single E, meaning the start room only has one door, and that door is to the east and leads to the second room.

We define a structure called Room, that has a message to display to the user, a type (at the moment S, R of F as mentioned above) and 4 pointers (called north, south, east and west) that either point to other rooms or to NULL. The constructor for the program first creates a vector of rooms by counting elements in the first row of the map file. It then uses the table to create links in the right directions to link the rooms. It then adds the messages, which are defined later in our input file.

The game then prompts the user to choose a direction from the available doors, and the user continues to move through the map until they reach the finish room, F. The predefined messages from above are diaplayed. If the user choses to leave early by quitting, a datafile (called ".unimportantData" to make it less obvious to players) stores this act of cowardice and will insult the player upon the next time they play. Once the game is won, this flag is removed and the game being normally.

This simple game could be expanded to include monsters, more room types (battle rooms vs rest rooms), and turn into a fully blown text based game but the aim here was to establish I could use classes and linked structures.
