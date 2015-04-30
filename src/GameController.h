#ifndef ____GameController__
#define ____GameController__

//#include "Combatant.h"
#include "Warrior.h"
#include "Entity.h"
#include <vector>
#include <math.h>
#include "AwesomeGL.h"
#include "Archer.h"
#include "Mage.h"
#include "GameMap.h"
#include "UI.h"

class GameController
{
public:
   GameController(GameMap *map, UI *ui);
   
   void incrementCounter();
   
   void moveCombatants();
   void spawnCombatants();
   
   void spawnProjectiles();
   void moveProjectiles();

   void checkCombatantCollision();
   void checkProjectileCollision();
   
   void checkMCCollision();
   
   void Update();
private:
	sf::Clock *startTimer;
	UI *ui;
	bool initEnemies;

   std::vector<Combatant*> cList;
};

#endif