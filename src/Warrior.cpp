#include "Warrior.h"

Warrior::Warrior(glm::vec3 initPos, bool isHero) : Combatant(WARRIOR_SPEED, "Models/Warrior.dae", "Models/Warrior.bmp", initPos, isHero, AwesomeGL::WARRIOR) {
   
}

void Warrior::attack(Combatant *other)
{
   if (attackClock->getElapsedTime().asSeconds() > 2)
   {
      anim_offset = 10;
      anim_time = 0;
      warriorAttackSound.play();
      attackClock->restart();
      
      other->decrementHealth(this);
      
      //special attack
      if (doSpecial)
      {
         other->decrementHealth(this);
         printf("Special Attack\n");
         doSpecial = false;
         rageEffect->stop();
         warriorSpecialAttackSound.play();
         Tween *lcolorB = new Tween(&lightColor.z, Tween::OUT_SINE, 0, lightColor.z, 2);
         lcolorB->start();
         Tween *lcolorR = new Tween(&lightColor.x, Tween::OUT_SINE, 1, lightColor.x, 2);
         lcolorR->start();
         Tween *lcolorG = new Tween(&lightColor.y, Tween::OUT_SINE, 1, lightColor.y, 2);
         lcolorG->start();
      }

   }
}

/*void Warrior::special(Combatant *other)
{
   if (attackClock->getElapsedTime().asSeconds() > 2)
   {
      anim_offset = 10;
      anim_time = 0;
      anim_step = 0.01;

      warriorAttackSound.play();
      attackClock->restart();
      printf("G\n");
      other->decrementHealth(this);
      printf("H\n");
   }
}*/

void Warrior::animateAttack()
{
   
}

bool Warrior::checkForAttack()
{
   //printf("enemy pos: %.2f   %.2f\n", enemy->getPos().x, enemy->getPos().z);
   //printf("pos: %.2f   %.2f\n", getPos().x, getPos().z);
   /*if(enemy->getPos().x == getPos().x + TILE_SIZE && enemy->getPos().z == getPos().z)
   {
      rotate(90, glm::vec3(0, 1, 0));
      dir.x = -1;
      return true;
   }
   else if (enemy->getPos().x == getPos().x - TILE_SIZE && enemy->getPos().z == getPos().z)
   {
      rotate(270, glm::vec3(0, 1, 0));
      dir.x = 1;
      return true;
   }
   
   else if (enemy->getPos().z == getPos().z + TILE_SIZE && enemy->getPos().x == getPos().x)
   {
      rotate(360, glm::vec3(0, 1, 0));
      dir.z = 1;
      return true;
   }
   
   else if (enemy->getPos().z == getPos().z - TILE_SIZE && enemy->getPos().x == getPos().x)
   {
      rotate(180, glm::vec3(0, 1, 0));
      dir.z = -1;
      return true;
   }*/
   
   if (isHero)
   {
      if (!moved && abs(glm::distance(enemy->getPos(), getPos())) <= TILE_SIZE + 5)
      {
         glm::vec3 projDir = this->getPos() - enemy->getPos();
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
         
         return true;
      }
   }
   
   else
   {
      if (abs(glm::distance(enemy->getPos(), getPos())) <= TILE_SIZE + 2)
      {
         glm::vec3 projDir = this->getPos() - enemy->getPos();
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
         
         return true;
      }
   }
   
   return false;
}
