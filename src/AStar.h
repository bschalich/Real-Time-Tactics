#ifndef __AStar__
#define __AStar__

#include "AwesomeGL.h"
#include "GameMap.h"

class AStar {
   
public:
   AStar(GameMap *map, int maxSearch, bool allowDiag);
   ~AStar();
   std::list<glm::vec3> findPath(int startX, int startZ, int endX, int endY);
   float getCost(int x, int z, int tx, int tz);
   
   class Node {
      
   public:
      float cost;
      float heuristic;
      float depth;
      Node *parent;
      int x;
      int z;
      
      Node(int x, int z) {
         this->x = x;
         this->z = z;
      }
      
      float setParent(Node *parent) {
         depth = parent->depth + 1;
         this->parent = parent;
         return depth;
      }
   };
   
private:
   std::list<Node*> closedList;
   std::list<Node*> openList;
   std::list<glm::vec3> steps;
   GameMap *gameMap;
   int maxSearch;
   Node *nodes[MAP_LENGTH][MAP_WIDTH];
   bool allowDiag;
   float heuristic;
   
protected:
   bool isInOpenList(Node *node);
   bool isInClosedList(Node *node);
   bool checkForValidLocation(int startX, int startY, int curX, int curZ);
   
};

#endif