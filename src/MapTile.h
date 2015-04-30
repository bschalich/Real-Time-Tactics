#ifndef __MapTile__
#define __MapTile__

#include "AwesomeGL.h"
#include "Entity.h"
#include <random>

extern GLuint mapVert;
extern GLuint mapIndex;
extern GLuint mapNormal;
extern int    mapNumVert;
extern GLuint mapUV;

class MapTile : public Entity {
public:
   MapTile(int x, int z);
   ~MapTile();
   bool checkOccupied();
   void setOccupied(bool oc);

   void setObject(std::string mesh, std::string texture, double height, glm::vec3 scale, bool occupy);
   Entity* getObject();
   
   void Update();
   int xPos, zPos;
   
private:
   std::uniform_int_distribution<int> intDist;
   bool occupied;
   Entity *object;
   
};

#endif
