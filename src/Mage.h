//
//  Mage.h
//  
//
//  Created by Bennett Schalich on 4/29/14.
//
//

#ifndef ____Mage__
#define ____Mage__

#include "AwesomeGL.h"
#include "Combatant.h"
#include "GameMap.h"

class Mage : public Combatant {
public:
   Mage(glm::vec3 initPos, bool isHero, GameMap *map);
   ~Mage();
   
   void attack(Combatant *other);
   void special(Combatant *other);
   void animateAttack();
   void causeExplosion(glm::vec3 attackCenter);
   bool checkForAttack();
   
private:
   GameMap *map;
   ParticleEmitter *pe;
};

#endif /* defined(____Mage__) */
