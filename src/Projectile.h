#ifndef __Projectile__
#define __Projectile__

//
//  Projectile.h
//  
//
//  Created by Bennett Schalich on 4/9/14.
//
//

#include "Entity.h"
#include <string>
#include "AwesomeGL.h"
#include "Combatant.h"

using namespace AwesomeGL;

class Projectile: public Entity
{
public:
   Projectile(int velocity, std::string mesh, std::string texture, glm::vec3 direction, glm::vec3 initPos, bool isFromHero, Combatant *from, AttackType attackType);
   ~Projectile();
   
   int getVelocity();
   void move();
   void Update();
   glm::vec3 getDirection();
   void deleteProjectile();
   void setRotation(float dir, glm::vec3);
   
private:
   AttackType attackType;
   int velocity;
   glm::vec3 direction;
   bool isFromHero;
   Entity *attachedEntity;
   float dirDegrees;
   Combatant *from;

   Projectile_State state;

   void projCollisionCheck();
   sf::Clock *deathClock;
};

#endif
