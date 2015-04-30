#ifndef __GameMap__
#define __GameMap__

#include <iostream>
#include "AwesomeGL.h"

#include "MapTile.h"
#define MAP_SIZE 20
#define MAP_WIDTH 11
#define MAP_LENGTH 60

class MapTile;

class GameMap {
public:
   GameMap();
   ~GameMap();
   
   bool isOccupied(int row, int col);
   MapTile* getTile(int i, int j);
      
private:
   MapTile *tile[MAP_LENGTH][MAP_WIDTH];
};

#endif
