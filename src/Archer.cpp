//
//  Archer.cpp
//
//
//  Created by Bennett Schalich on 4/27/14.
//
//

#include "Archer.h"

Archer::Archer(glm::vec3 initPos, bool isHero) : Combatant(ARCHER_SPEED, "Models/Ranged.dae", "Models/Ranged.bmp", initPos, isHero, AwesomeGL::ARCHER)
{
   scale(glm::vec3(.12, .12, .12));
}

Archer::~Archer()
{
   
}

void Archer::attack(Combatant* other)
{
   glm::vec3 projDir = this->getPos() - other->getPos();
   int magnitude = projDir.x * projDir.x + projDir.z * projDir.z;
   projDir.x = projDir.x / magnitude;
   projDir.z = projDir.z / magnitude;
   projDir.y = 0;
   
   double rotation = projDir.x / projDir.z;
   
   rotation = (atan(rotation) * (180 / PI));
   
   /*if (rotation == -90 || rotation == 90)
     rotation = -rotation;*/
   
   if (projDir.z > 0)
      rotation = rotation - 180;
   
   if (rotation == 90 || rotation == -90)
      rotation = -rotation;
   
   this->angle = rotation;
   this->axis = glm::vec3(0, 1, 0);
   //printf("rotation: %f\n", rotation);
   
   if (attackClock->getElapsedTime().asSeconds() > 3)
   {
      anim_offset = 10;
      anim_time = 0;
      anim_step = 0.025;

      attackClock->restart();
   
      archerAttackSound.play();
   
      Projectile *p;

         p = new Projectile(PROJ_SPEED - 5, "Models/Arrow.obj", "Models/Arrow.bmp", projDir, vec3(this->getPos().x, this->getPos().y + 10, this->getPos().z), this->getIsHero(), this, AwesomeGL::NORMAL);
      p->setRotation(rotation, glm::vec3(0, 1, 0));
   }
}

/*void Archer::special(Combatant* other)
{
   glm::vec3 projDir = this->getPos() - other->getPos();
   int magnitude = projDir.x * projDir.x + projDir.z * projDir.z;
   projDir.x = projDir.x / magnitude;
   projDir.z = projDir.z / magnitude;
   projDir.y = 0;
   
   double rotation = projDir.x / projDir.z;
   
   rotation = (atan(rotation) * (180 / PI));
   
   /*if (rotation == -90 || rotation == 90)
    rotation = -rotation;*/
   
   /*if (projDir.z > 0)
      rotation = rotation - 180;
   
   if (rotation == 90 || rotation == -90)
      rotation = -rotation;
   
   this->angle = rotation;
   this->axis = glm::vec3(0, 1, 0);
   //printf("rotation: %f\n", rotation);
   
   if (attackClock->getElapsedTime().asSeconds() > 3)
   {
      anim_offset = 10;
      anim_time = 0;
      attackClock->restart();
      
      archerAttackSound.play();
      
      
      Projectile *p = new Projectile(PROJ_SPEED - 5, "Models/Arrow.obj", "Models/Arrow.bmp", projDir, vec3(this->getPos().x, this->getPos().y + 10, this->getPos().z), this->getIsHero(), this);
      
      p->setRotation(rotation, glm::vec3(0, 1, 0));
   }
}*/

void Archer::animateAttack()
{
   
}

bool Archer::checkForAttack()
{
   if (isHero)
   {
      if (moved == false && abs(glm::distance(this->getPos(), enemy->getPos())) <= ARCHER_RANGE)
      {
         return true;
      }
   }
   
   else
   {
      if (abs(glm::distance(this->getPos(), enemy->getPos())) <= ARCHER_RANGE)
      {
         return true;
      }
   }
   
   return false;
}
