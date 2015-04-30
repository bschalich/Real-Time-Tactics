//
//  Mage.cpp
//
//
//  Created by Bennett Schalich on 4/29/14.
//
//

#include "Mage.h"

Mage::Mage(glm::vec3 initPos, bool isHero, GameMap *map) : Combatant(MAGE_SPEED, "Models/Caster.dae", "Models/Caster.bmp", initPos, isHero, AwesomeGL::MAGE)
{
   this->map = map;
}

Mage::~Mage()
{
   
}

void Mage::attack(Combatant *other)
{
   glm::vec3 projDir = this->getPos() - other->getPos();
   int magnitude = projDir.x * projDir.x + projDir.z * projDir.z;
   projDir.x = projDir.x / magnitude;
   projDir.z = projDir.z / magnitude;
   projDir.y = 0;
   
   double rotation = projDir.x / projDir.z;
   
   rotation = (atan(rotation) * (180 / PI));
   
   if (projDir.z > 0)
      rotation = rotation - 180;
   
   if (rotation == 90 || rotation == -90)
      rotation = -rotation;
   
   this->angle = rotation;
   this->axis = glm::vec3(0, 1, 0);
   
   if (attackClock->getElapsedTime().asSeconds() > 2.5 && !doSpecial)
   {
      anim_offset = 10;
      anim_time = 0;
      attackClock->restart();
      animateAttack();
      glm::vec3 attackCenter = other->getPos();
      
      causeExplosion(attackCenter);
      
      mageAttackSound.play();
      
      if (!doSpecial) {
         for (int i = 0; i < cList.size(); i++)
         {
            if (cList[i]->getIsHero() != this->isHero && abs(glm::distance(attackCenter, cList[i]->getPos())) < MAGE_AOE)
            {
               cList[i]->decrementHealth(this);
            }
         }
      }
   }
}

/*void Mage::special(Combatant *other)
 {
 glm::vec3 projDir = this->getPos() - other->getPos();
 int magnitude = projDir.x * projDir.x + projDir.z * projDir.z;
 projDir.x = projDir.x / magnitude;
 projDir.z = projDir.z / magnitude;
 projDir.y = 0;
 
 double rotation = projDir.x / projDir.z;
 
 rotation = (atan(rotation) * (180 / PI));
 
 if (projDir.z > 0)
 rotation = rotation - 180;
 
 if (rotation == 90 || rotation == -90)
 rotation = -rotation;
 
 this->angle = rotation;
 this->axis = glm::vec3(0, 1, 0);
 
 if (attackClock->getElapsedTime().asSeconds() > 4)
 {
 anim_offset = 10;
 anim_time = 0;
 attackClock->restart();
 animateAttack();
 glm::vec3 attackCenter = other->getPos();
 
 causeExplosion(attackCenter);
 
 mageAttackSound.play();
 
 for (int i = 0; i < cList.size(); i++)
 {
 if (cList[i]->getIsHero() != this->isHero && abs(glm::distance(attackCenter, cList[i]->getPos())) < MAGE_AOE)
 {
 cList[i]->decrementHealth(this);
 
 
 }
 }
 }
 }*/

void Mage::animateAttack()
{
   
}

bool Mage::checkForAttack()
{
   if (!isHero)
   {
      if (abs(glm::distance(this->getPos(), enemy->getPos())) <= MAGE_RANGE)
      {
         return true;
      }
   }
   
   else
   {
      if (moved == false && abs(glm::distance(this->getPos(), enemy->getPos())) <= MAGE_RANGE)
      {
         return true;
      }
   }
   
   return false;
}

void Mage::causeExplosion(glm::vec3 attackCenter)
{
   pe = new ParticleEmitter(500, 1, 100, attackCenter, 5.0, false, glm::vec3(1, 0, 1), glm::vec3(0, 0, 0));
   pe->setColor(glm::vec4(0, 0, 1000^256, 1000 ^ 256 / 3));
   pe->setSpread(20);
   pe->start();
}
