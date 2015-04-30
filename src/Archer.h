//
//  Archer.h
//  
//
//  Created by Bennett Schalich on 4/29/14.
//
//

#ifndef ____Archer__
#define ____Archer__

#include "AwesomeGL.h"
#include "Combatant.h"

using namespace AwesomeGL;

class Archer : public Combatant {
public:
   Archer(glm::vec3 initPos, bool isHero);
   ~Archer();
   
   void attack(Combatant *other);
   void special(Combatant *other);
   void animateAttack();
   bool checkForAttack();
};



#endif /* defined(____Archer__) */
