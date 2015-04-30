#ifndef __Warrior__
#define __Warrior__

#include "AwesomeGL.h"
#include "Combatant.h"

class Warrior : public Combatant {
public:
   Warrior(glm::vec3 initPos, bool isHero);
   ~Warrior();
   
   void attack(Combatant *other);
   void special(Combatant *other);
   void animateAttack();
   bool checkForAttack();
};

#endif
