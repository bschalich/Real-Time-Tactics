#include "AStar.h"

AStar::AStar(GameMap *map, int maxSearch, bool allowDiag) {
   gameMap = map;
   this->maxSearch = maxSearch;
   this->allowDiag = allowDiag;
   this->heuristic = 0;
   
   for (int i = 0; i < MAP_LENGTH; i++) {
      for (int j = 0; j < MAP_WIDTH; j++) {
         nodes[i][j] = new Node(i, j);
         nodes[i][j]->parent = NULL;
         nodes[i][j]->cost = 0;
         nodes[i][j]->heuristic = 0;
      }
   }
}

AStar::~AStar() {
   for (int i = 0; i < MAP_LENGTH; i++) {
      for (int j = 0; j < MAP_WIDTH; j++) {
         delete nodes[i][j];
      }
   }
}

bool compareCost(AStar::Node *n1, AStar::Node *n2) {
   float thisCost = n1->heuristic + n1->cost;
   float otherCost = n2->heuristic + n2->cost;
   
   if (thisCost < otherCost) {
      return true;
   }
   return false;
}

std::list<glm::vec3> AStar::findPath(int startX, int startZ, int endX, int endZ) {
   if ((endX < MAP_LENGTH && endZ < MAP_WIDTH) && (endX >= 0 && endZ >= 0)) {
      nodes[startX][startZ]->cost = 0;
      nodes[startX][startZ]->depth = 0;
      nodes[startX][startZ]->parent = NULL;
      closedList.clear();
      openList.clear();
      openList.push_back(nodes[startX][startZ]);
      
      int maxDepth = 0;
      while ((maxDepth < maxSearch) && (openList.size() != 0)) {
         Node *current = openList.front();
         if (current == nodes[endX][endZ]) {
            break;
         }
         
         openList.remove(current);
         closedList.push_back(current);
         
         for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
               if ((i == 0) && (j == 0)) {
                  continue;
               }
               if (!allowDiag) {
                  if ((i != 0) && (j != 0)) {
                     continue;
                  }
               }
               int xp = i + current->x;
               int zp = j + current->z;
               
               if (checkForValidLocation(startX, startZ, xp, zp)) {
                  float nextStepCost = current->cost; //+ map->getCost();
                  Node *neighbor = nodes[xp][zp];
                  //map->pathFinderVisited(xp, zp);
                  
                  if (nextStepCost < neighbor->cost) {
                     openList.remove(neighbor);
                     closedList.remove(neighbor);
                  }
                  
                  if (!isInOpenList(neighbor) && !(isInClosedList(neighbor))) {
                     neighbor->cost = nextStepCost + getCost(current->x, current->z, endX, endZ);
                     neighbor->heuristic = getCost(startX, startZ, endX, endZ);
                     maxDepth = std::max(maxDepth, (int)neighbor->setParent(current));
                     openList.push_back(neighbor);
                  }
               }
            }
         }
         openList.sort(compareCost);
      }
      
      if (nodes[endX][endZ]->parent != NULL) {
         steps.clear();
         Node *target = nodes[endX][endZ];
         while (target != NULL && target != nodes[startX][startZ]) {
            steps.push_front(glm::vec3(target->x, 0, target->z));
            target = target->parent;
         }
      }
      steps.push_front(glm::vec3(startX, 0, startZ));
   }
   else {
      steps.clear();
   }
   return steps;
}

bool AStar::isInClosedList(Node *neighbor) {
   for (std::list<Node*>::iterator it = closedList.begin(); it != closedList.end(); ++it) {
      if (neighbor == *it) {
         return true;
      }
   }
   return false;
}

bool AStar::isInOpenList(Node *neighbor) {
   for (std::list<Node*>::iterator it = openList.begin(); it != openList.end(); ++it) {
      if (neighbor == *it) {
         return true;
      }
   }
   return false;
}

bool AStar::checkForValidLocation(int startX, int startZ, int otherX, int otherZ) {
   bool invalid = otherX < 0 || otherZ < 0 || otherX >= MAP_LENGTH || otherZ >= MAP_WIDTH;
   if (!invalid && (startX != otherX || startZ != otherZ)) {
      invalid = gameMap->isOccupied(otherX, otherZ);
   }
   /*if (abs(startX - otherX) => 1 && abs(startZ - otherZ) > 1) {
    invalid = true;
    }*/
   return !invalid;
}

float AStar::getCost(int x, int z, int tx, int tz) {
   int dx = tx - x;
   int dz = tz - z;
   
   return sqrt((float)dx*dx + dz*dz);
}