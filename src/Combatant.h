//
//  Combatant.h
//
//
//  Created by Bennett Schalich on 4/11/14.
//
//

#ifndef ____Combatant__
#define ____Combatant__

class StateMachine;

#include "AwesomeGL.h"
#include "Entity.h"
#include "AStar.h"
#include <string>
#include <list>
#include "StateMachine.h"
#include "Projectile.h"
#include "Billboard.h"
#include "Camera.h"
#include "ActiveHeroIcon.h"

using namespace AwesomeGL;

class Combatant : public Entity
{
public:
   Combatant(int velocity, std::string mesh, std::string texture, glm::vec3 initPos, bool isHero, Combatant_Type type);
   ~Combatant();
   sf::SoundBuffer warriorAttackSoundBuffer;
   sf::SoundBuffer archerAttackSoundBuffer;
   sf::SoundBuffer mageAttackSoundBuffer;
   sf::SoundBuffer arrowHitSoundBuffer;
   sf::SoundBuffer warriorSpecialAttackSoundBuffer;
   sf::SoundBuffer mageSpecialAttackSoundBuffer;
   sf::SoundBuffer archerSpecialSoundBuffer;
   sf::SoundBuffer potionSoundBuffer;
   
   sf::Sound potionSound;
   sf::Sound archerSpecialSound;
   sf::Sound warriorSpecialAttackSound;
   sf::Sound mageSpecialAttackSound;
   sf::Sound warriorAttackSound;
   sf::Sound archerAttackSound;
   sf::Sound mageAttackSound;
   sf::Sound arrowShotSound;
   
   virtual void attack(Combatant *other) = 0;
   //virtual void special(Combatant *other) = 0;
   virtual void animateAttack() = 0;
   void setVelocity(int velocity);
   int getVelocity();
   void Update();
   void changeBoundingBox(glm::vec3 oldPos);
   void setCurrentState();
   
   void hitByMage();
   int getHealth();
   void decrementHealth(Combatant *from);
   void deleteCombatant();
   void moveTo(int tx, int tz);
   bool isOnDest();
   glm::vec3 getDest();
   void setDest(int x, int z);
   void setDir(glm::vec3 dir);
   bool isMoving();
   bool getIsHero();
   glm::vec3 getDir();
   float getDirDegrees();
   virtual bool checkForAttack() = 0;
   StateMachine* getBrain();
   void setMoved(bool moved);
   void setSpecial(bool special);
   bool getSpecial();
   sf::Clock* getSpecialCooldown();
   
   void setEnemyNull();
   void setEnemy(Combatant *enemy);
   Combatant* getEnemy();
   void specialAttack();
   float walkSpeed;
   sf::Clock *attackClock;
   sf::Clock *specialCooldown;
   bool doSpecial;
   
   glm::vec3 tilePos;
   Combatant_Type type;

   float hitEffectY;
   bool dead;
   
   ParticleEmitter *rageEffect;
   ParticleEmitter *dodgeEffect;
   
protected:
   ParticleEmitter *hitEffect;
   AStar *pathfinder;
   std::list<glm::vec3> steps;
   int velocity;
   int health;
   bool isHero;
   bool gotHit;
   bool moved, takeNextStep;
   glm::vec3 dest;
   glm::vec3 dir;
   glm::vec3 st;
   float dirDegrees;
   StateMachine *brain;
   Entity *bb[8];
   Combatant *enemy;
   
   
   
   void useStep();
   void getNextDir();

private:
   Billboard *billboard;
   ActiveHeroIcon *icon;
   
};

#endif /* defined(____Combatant__) */
