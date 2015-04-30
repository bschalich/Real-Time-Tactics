//
//  Combatant.cpp
//
//
//  Created by Bennett Schalich on 4/11/14.
//
//

#include "Combatant.h"
#include <math.h>

Combatant::Combatant(int velocity, std::string mesh, std::string texture, glm::vec3 initPos, bool isHero, Combatant_Type type) : Entity(mesh, texture)
{
   
   warriorAttackSoundBuffer.loadFromFile("Sound/swordclash.wav");
   archerAttackSoundBuffer.loadFromFile("Sound/arrowshot.wav");
   mageAttackSoundBuffer.loadFromFile("Sound/fireball.ogg");
   mageSpecialAttackSoundBuffer.loadFromFile("Sound/thunder.ogg");
   arrowHitSoundBuffer.loadFromFile("Sound/arrowhit.wav");
   warriorSpecialAttackSoundBuffer.loadFromFile("Sound/stab2.wav");
   archerSpecialSoundBuffer.loadFromFile("Sound/whoosh.ogg");
   potionSoundBuffer.loadFromFile("Sound/potion.wav");
   
   potionSound.setBuffer(potionSoundBuffer);
   archerSpecialSound.setBuffer(archerSpecialSoundBuffer);
   warriorSpecialAttackSound.setBuffer(warriorSpecialAttackSoundBuffer);
   warriorAttackSound.setBuffer(warriorAttackSoundBuffer);
   archerAttackSound.setBuffer(archerAttackSoundBuffer);
   mageAttackSound.setBuffer(mageAttackSoundBuffer);
   mageSpecialAttackSound.setBuffer(mageSpecialAttackSoundBuffer);
   arrowHitSound.setBuffer(arrowHitSoundBuffer);
   //arrowHitSound.setVolume(20);
   hitEffectY = 8;
   pathfinder = new AStar(AwesomeGL::map, 100, false);
   moved = false;
   walkSpeed = 20;
   
   this->velocity = velocity;
   dirDegrees = 0;
   gotHit = false;
   dead = false;
   eBoundingBox.max *= vec3(.1, .1, .1);
   eBoundingBox.min *= vec3(.1, .1, .1);
   //eBoundingBox.max += initPos;
   //eBoundingBox.min += initPos;
   
	eBoundingBox.min.y += 1;
	eBoundingBox.max.y += 17;
   
	ogBoundingBox.min = eBoundingBox.min;
	ogBoundingBox.max = eBoundingBox.max;
   
   trans = initPos;
   
   Tween *down = new Tween(&trans.y, Tween::OUT_SINE, 300, initPos.y, 2.5, 2.5);
   down->start();
   
   this->type = type;
   if (isHero) {
      health = 10;
   }
   else {
      health = 6;
   }
   this->isHero = isHero;
   
   if (type == AwesomeGL::WARRIOR)
   {
	   if (isHero)
			this->color = glm::vec3(1.0f, 1.0f, 1.0f);
	   else
		   this->color = glm::vec3(1.0f, 0.5f, 0.5f);
      
   }
   
   else if (type == AwesomeGL::ARCHER) {
      if (!isHero) {
         this->color = glm::vec3(1.0f, 0.5f, 0.5f);
      }
   }
   else if (type == AwesomeGL::MAGE) {
      if (!isHero) {
         this->color = glm::vec3(1.0f, 0.5f, 0.5f);
      }
   }
   //rotate(180, glm::vec3(0, 1, 0));
   scale(glm::vec3(.1, .1, .1)); //5, 5, 5
   
   brain = new StateMachine(this);
   if (!isHero)
      brain->currentState = StateMachine::WANDER;
   /*else
    brain->currentState = StateMachine::NOTHING;*/
   
   addEntity(this);
   addCombatant(this);
   attackClock = new sf::Clock();
   specialCooldown = new sf::Clock();
   doSpecial = false;
   
   enemy = NULL;
   
   Billboard *billboard = new Billboard(this, health);
   this->billboard = billboard;
   
   icon = new ActiveHeroIcon(this);
   
   
   rageEffect = new ParticleEmitter(200, 0.5, 10, glm::vec3(getPos().x, hitEffectY, getPos().z), 1.0, true, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0));
   rageEffect->setSpread(50);
   //rageEffect->randomRed(true);
   rageEffect->setColor(glm::vec4(1000 ^ 256, 1000 ^ 256, 0, (1000 ^ 256) / 3));
   
   dodgeEffect = new ParticleEmitter(200, 0.5, 10, glm::vec3(getPos().x, -5, getPos().z), 1.0, true, glm::vec3(1, 0, 1), glm::vec3(1, 0, 1));
   dodgeEffect->setSpread(10);
   //dodgeEffect->randomRed(true);
   dodgeEffect->setColor(glm::vec4(0, 1000 ^ 256, 0, (1000 ^ 256) / 3));
}

Combatant::~Combatant()
{
   
}

void Combatant::setSpecial(bool special)
{
   doSpecial = special;
   
   if (type == AwesomeGL::WARRIOR) {
      tauntSound.play();
   }
   else if (type == AwesomeGL::ARCHER) {
      
   }
   else if (type == AwesomeGL::MAGE) {
      
   }
}

bool Combatant::getSpecial()
{
   return doSpecial;
}

sf::Clock* Combatant::getSpecialCooldown()
{
   return specialCooldown;
}

/*void Combatant::specialAttack() {
 if (type == AwesomeGL::WARRIOR) {
 tauntSound.play();
 }
 else if (type == AwesomeGL::ARCHER) {
 
 }
 else if (type == AwesomeGL::MAGE) {
 
 }
 
 brain->currentState = StateMachine::SPECIAL;
 }*/

void Combatant::setCurrentState() {
   if (!isHero)
      brain->currentState = StateMachine::WANDER;
}

Combatant* Combatant::getEnemy()
{
   return enemy;
}

void Combatant::setVelocity(int velocity)
{
   this->velocity = velocity;
}

int Combatant::getVelocity()
{
   return velocity;
}

int Combatant::getHealth()
{
   return health;
}

bool Combatant::isMoving() {
   return moved;
}

glm::vec3 Combatant::getDir() {
   return dir;
}

void Combatant::setEnemyNull()
{
   enemy = NULL;
}

void Combatant::hitByMage() {
   hitEffectY = 400;
   hitEffect = new ParticleEmitter(400, 3, 100, glm::vec3(getPos().x, hitEffectY, getPos().z), 5.0, false, glm::vec3(0, -1, 0), glm::vec3(0, -1, 0));
   hitEffect->setSpread(10);
   //hitEffect->randomBlue(true);
   hitEffect->setColor(glm::vec4(0, 0, 1000 ^ 256, (1000 ^ 256) / 3));
   hitEffect->start();
   Tween *lcolorB = new Tween(&lightColor.z, Tween::INOUT_BOUNCE, 0, lightColor.z, 5);
   lcolorB->start();
   Tween *lcolorR = new Tween(&lightColor.x, Tween::INOUT_BOUNCE, 0, lightColor.x, 5);
   lcolorR->start();
   Tween *lcolorG = new Tween(&lightColor.y, Tween::INOUT_BOUNCE, 0, lightColor.y, 5);
   lcolorG->start();
}

void Combatant::decrementHealth(Combatant *from)
{
   if (type == AwesomeGL::ARCHER && doSpecial) {
      archerSpecialSound.play();
      doSpecial = false;
      dodgeEffect->stop();
      walkSpeed = 20;
      Tween *lcolorB = new Tween(&lightColor.z, Tween::OUT_SINE, 0, lightColor.z, 2);
      lcolorB->start();
      Tween *lcolorR = new Tween(&lightColor.x, Tween::OUT_SINE, 0, lightColor.x, 2);
      lcolorR->start();
      Tween *lcolorG = new Tween(&lightColor.y, Tween::OUT_SINE, 1, lightColor.y, 2);
      lcolorG->start();
      
   }
   else {
      if (isHero) {
         camera->shake();
      }
      hitEffectY = 8;
      hitEffect = new ParticleEmitter(25, 1, 10, glm::vec3(getPos().x, hitEffectY, getPos().z), 1.0, false, glm::vec3(1, 1, 1), glm::vec3(0, -1, 0));
      hitEffect->setSpread(10);
      hitEffect->randomGreen(true);
      hitEffect->setColor(glm::vec4(1000 ^ 256, 100 ^ 256, 100 ^ 256, (1000 ^ 256) / 3));
      hitEffect->start();
      gotHit = true;
      
      billboard->setOldHealth(health);
      health--;
      billboard->setHealth(health);
      
      billboard->startTween();
      
      if (health == 3)
         color = glm::vec3(0.8f, 0.3f, 0.3f);
      
      else if (health == 2)
         color = glm::vec3(0.9f, 0.1f, 0.1f);
      
      else if (health == 1)
         color = glm::vec3(1.0f, 0.0f, 0.0f);
      
      if (health <= 0)
      {
         deathSound.play();
         deleteCombatant();
         removeEnemy(this);
         dead = true;
         for (int i = 0; i < cList.size(); i++) {
            //if (cList[i]->enemy != NULL)
            //cList[i]->enemy->setEnemyNull();
            cList[i]->enemy = NULL;
         }
         if (isHero) {
            removeHero(this);
         }
         
         printf("Remove Billboard\n");
         removeParticle(hitEffect);
         removeAHIcon(icon);
         removeBillboard(billboard);
      }
   }

}

void Combatant::setEnemy(Combatant *newEnemy)
{
   /*if (isHero)
    this->enemy = newEnemy;*/
   
   //else
   //{
   if (!enemy)
   {
      int range;
      switch (type)
      {
         {case AwesomeGL::WARRIOR:
            range = WARRIOR_LOOK_RANGE;
            break;}
            
         {case AwesomeGL::ARCHER:
            range = ARCHER_LOOK_RANGE;
            break;}
            
         {case AwesomeGL::MAGE:
            range = MAGE_LOOK_RANGE;
            break;}
            
         {default:
            range = 0;
            break;}
      }
      
      int distance = 1000;
      
      for (int i = 0; i < cList.size(); i++)
      {
         int newDistance;
         if (this->getIsHero() != cList[i]->getIsHero() && (newDistance = abs(glm::distance(this->getPos(), cList[i]->getPos()))) < range)
         {
            distance = newDistance;
            this->enemy = cList[i];
            printf("Enemy Set\n");
            /*setDest(int(this->enemy->getPos().x / 10), this->getPos().y, int(this->enemy->getPos().z)));*/
            if (!isHero)
               brain->currentState = StateMachine::MOVE;
         }
      }
   }
   //}
}

glm::vec3 Combatant::getDest()
{
   return dest;
}

void Combatant::setDest(int x, int z)
{
   this->dest = glm::vec3(x, dest.y, z);
}

float Combatant::getDirDegrees() {
   return dirDegrees;
}

void Combatant::setDir(glm::vec3 dir) {
   this->dir = dir;
}

void Combatant::deleteCombatant()
{
   rageEffect->stop();
   brain->currentState = StateMachine::NOTHING;
   map->getTile((int)(this->getPos().x/TILE_SIZE),
                (int)(this->getPos().z/TILE_SIZE))->setOccupied(false);
   removeEntity(this);
   removeCombatant(this);
}

void Combatant::moveTo(int tx, int tz) {
   if (!moved) {
      steps = pathfinder->findPath((int)(this->getPos().x/TILE_SIZE),
                                   (int)(this->getPos().z/TILE_SIZE),
                                   tx,
                                   tz);
      if (!steps.empty()) {
         dest = steps.back();
         map->getTile((int)(this->getPos().x/TILE_SIZE),
                      (int)(this->getPos().z/TILE_SIZE))->setOccupied(false);
         map->getTile((int)dest.x, (int)dest.z)->setOccupied(true);
         moved = true;
         takeNextStep = true;
      }
   }
}

void Combatant::getNextDir() {
   if (st.x*10 < this->getPos().x) {
      dir.x = -1;
      rotate(270, glm::vec3(0, 1, 0));
      dirDegrees = 270;
   }
   else if (st.x*10 > this->getPos().x) {
      dir.x = 1;
      rotate(90, glm::vec3(0, 1, 0));
      dirDegrees = 90;
   }
   else {
      dir.x = 0;
   }
   
   if (st.z*10 < this->getPos().z) {
      dir.z = -1;
      rotate(180, glm::vec3(0, 1, 0));
      dirDegrees = 180;
   }
   else if (st.z*10 > this->getPos().z) {
      dir.z = 1;
      rotate(360, glm::vec3(0, 1, 0));
      dirDegrees = 360;
   }
   else {
      dir.z = 0;
   }
}

void Combatant::useStep() {
   getNextDir();
   
   //moveBoundingBox(this->trans);
   
   translate(glm::vec3(this->getPos().x + (dir.x * walkSpeed) * deltaTime.asSeconds(), this->getPos().y, this->getPos().z + (dir.z * walkSpeed) * deltaTime.asSeconds()));
   
   if (dir.x == -1 && this->getPos().x <= st.x*10) {
      translate(glm::vec3(st.x*10, this->getPos().y, this->getPos().z));
      
      takeNextStep = true;
   }
   else if (dir.x == 1 && this->getPos().x >= st.x*10) {
      translate(glm::vec3(st.x*10, this->getPos().y, this->getPos().z));
      
      takeNextStep = true;
   }
   
   if (dir.z == -1 && this->getPos().z <= st.z*10) {
      translate(glm::vec3(this->getPos().x, this->getPos().y, st.z*10));
      
      takeNextStep = true;
   }
   else if (dir.z == 1 && this->getPos().z >= st.z*10) {
      translate(glm::vec3(this->getPos().x, this->getPos().y, st.z*10));
      
      takeNextStep = true;
   }
   
   if (dir.x == 0 && dir.z == 0)
      takeNextStep = true;
}

bool Combatant::isOnDest() {
   if (this->getPos().x == dest.x*10
       && this->getPos().z == dest.z*10) {
      return true;
   }
   return false;
}

bool Combatant::getIsHero()
{
	return isHero;
}

StateMachine* Combatant::getBrain()
{
   return brain;
}

void Combatant::Update()
{
   if (type == AwesomeGL::MAGE) {
      if (doSpecial) {
         mageSpecialAttackSound.play();
         anim_offset = 10;
         anim_time = 0;
         for (int i = 0; i < enemyList.size(); i++)
         {
            enemyList[i]->decrementHealth(this);
            enemyList[i]->hitByMage();
         }
         doSpecial = false;
      }
   }
   
   if (!dead) {
      if (gotHit)
         hitEffect->setPos(glm::vec3(trans.x, hitEffectY, trans.z));
      rageEffect->setPos(glm::vec3(trans.x, hitEffectY, trans.z));
      dodgeEffect->setPos(glm::vec3(trans.x, -5, trans.z));
      brain->runActiveState();
      
      setEnemy(NULL);
      
      if (this == activeHero && dest != tilePos)
      {
         enemy = NULL;
         moved = false;
         moveTo((int)tilePos.x, (int)tilePos.z);
      }
      
      if (enemy != NULL && checkForAttack())
      {
         brain->currentState = StateMachine::ATTACK;
         //printf("pos: %f %f\n", getPos().x, getPos().z);
         moved = false;
      }
      
      //actually move
      if (moved) {
         if (!isOnDest()) {
            if (takeNextStep) {
               st = steps.front();
               steps.pop_front();
               useStep();
               takeNextStep = false;
            }
            else {
               useStep();
            }
         }
         else {
            moved = false;
         }
      }
      
      if (this == activeHero)
      {
         this->color = vec3(0.5, 0.5, 1);
      }
      else if (isHero)
      {
         this->color = vec3(1, 1, 1);
      }
      
      //Updating bounding box
      eBoundingBox.min = vec3(ogBoundingBox.min.x + this->getPos().x, ogBoundingBox.min.y, ogBoundingBox.min.z + this->getPos().z);
      eBoundingBox.max = vec3(ogBoundingBox.max.x + this->getPos().x, ogBoundingBox.max.y, ogBoundingBox.max.z + this->getPos().z);
      Entity::Update();
   }
}
