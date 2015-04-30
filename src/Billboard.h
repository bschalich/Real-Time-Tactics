//
//  Billboard.h
//  
//
//  Created by Bennett Schalich on 5/13/14.
//
//

#ifndef ____Billboard__
#define ____Billboard__

class Combatant;

#include "AwesomeGL.h"
#include "Entity.h"
#include "Tween.h"

using namespace AwesomeGL;

class Billboard
{
public:
   Billboard(Entity *entity, int health);
   void Update();
   
   void setHealth(int health);
   void setOldHealth(int oldHealth);
   
   void startTween();
private:
   GLuint billboard_vertex_buffer;
   Entity *entity;
   float health;
   float oldHealth;
   float thisHealth;
   Tween *tween;
};

#endif /* defined(____Billboard__) */