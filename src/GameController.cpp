//
//  GameController.cpp
//
//
//  Created by Bennett Schalich on 4/11/14.
//
//

#include "GameController.h"

GameController::GameController(GameMap *map, UI *ui)
{
	startTimer = new sf::Clock();
	this->ui = ui;

	//set up heros
	Combatant *hero = new Warrior(glm::vec3(5*TILE_SIZE, -5, 0*TILE_SIZE), true);
	cList.push_back(hero);
	heroList.push_back(hero);
	hero = new Warrior(glm::vec3(5*TILE_SIZE, -5, 8*TILE_SIZE), true);
	cList.push_back(hero);
	heroList.push_back(hero);
	hero = new Archer(glm::vec3(5*TILE_SIZE, -5, 4*TILE_SIZE), true);
	cList.push_back(hero);
	heroList.push_back(hero);
	hero = new Archer(glm::vec3(5*TILE_SIZE, -5, 6*TILE_SIZE), true);
	cList.push_back(hero);
	heroList.push_back(hero);
	hero = new Mage(glm::vec3(5*TILE_SIZE, -5, 5*TILE_SIZE), true, map);
	cList.push_back(hero);
	heroList.push_back(hero);

	char *line = new char[10];
   std::ifstream file ("Maps/map1.txt");
   for (int i = 0; i < MAP_LENGTH; i++)
   {
      for (int j = 0; j < MAP_WIDTH; j++)
      {
		   file.read(line, 1);
		   while (line[0] == '\n')
		   {
			   file.read(line, 1);
		   }
		   if (line[0] == 'W')
		   {
			   Combatant *enemy = new Warrior(glm::vec3(i*TILE_SIZE, -5, j*TILE_SIZE), false);
			   cList.push_back(enemy);
			   enemyList.push_back(enemy);
		   }
		   else if (line[0] == 'A')
		   {
			   Combatant *enemy = new Archer(glm::vec3(i*TILE_SIZE, -5, j*TILE_SIZE), false);
			   cList.push_back(enemy);
			   enemyList.push_back(enemy);
		   }
		   else if (line[0] == 'M')
		   {
			   Combatant *enemy = new Mage(glm::vec3(i*TILE_SIZE, -5, j*TILE_SIZE), false, map);
			   cList.push_back(enemy);
			   enemyList.push_back(enemy);
		   } 
      }
   }
}

void GameController::Update() {

	//Beginning countdown wait
	if (startTimer->getElapsedTime().asSeconds() > 8)
	{
      if (!initEnemies)
		{
         start.play();
			for (int i = 0; i < enemyList.size(); i++)
			{
				enemyList[i]->setCurrentState();
			}
			initEnemies = true;
		}
	}
	else //UI beginning
	{
		ui->countdown();
	}
}
/*void GameController::moveCombatants()
 {
 glm::vec3 newPos = glm::vec3(0, 0, 0);
 
 for (std::list<Combatant *>::iterator it = cList.begin(); it != cList.end(); ++it)
 {
 int velocity = (*it)->getVelocity();
 
 //printf("getPos().x: %d\n", (int)(*it)->getPos().x);
 if ((*it)->getMoveTo().x > (int)(*it)->getPos().x)
 {
 newPos.x = (*it)->getPos().x + AwesomeGL::deltaTime.asSeconds() * velocity;
 newPos.z = (*it)->getPos().z;
 (*it)->setTransAmt(newPos);
 (*it)->moveBoundingBox((*it)->getPos());
 (*it)->translate(newPos);
 }
 
 else if ((*it)->getMoveTo().x < (int)(*it)->getPos().x)
 {
 newPos.x = (*it)->getPos().x + AwesomeGL::deltaTime.asSeconds() * -velocity;
 newPos.z = (*it)->getPos().z;
 (*it)->setTransAmt(newPos);
 (*it)->moveBoundingBox((*it)->getPos());
 (*it)->translate(newPos);
 }
 
 if ((*it)->getMoveTo().z > (int)(*it)->getPos().z)
 {
 newPos.z = (*it)->getPos().z + AwesomeGL::deltaTime.asSeconds() * velocity;
 newPos.x = (*it)->getPos().x;
 (*it)->setTransAmt(newPos);
 (*it)->moveBoundingBox((*it)->getPos());
 (*it)->translate(newPos);
 }
 
 else if((*it)->getMoveTo().z < (int)(*it)->getPos().z)
 {
 newPos.z = (*it)->getPos().z + AwesomeGL::deltaTime.asSeconds() * -velocity;
 newPos.x = (*it)->getPos().x;
 (*it)->setTransAmt(newPos);
 (*it)->moveBoundingBox((*it)->getPos());
 (*it)->translate(newPos);
 }
 
 else
 {
 (*it)->setMoveTo(glm::vec3(rand() % 100, 0, rand() % 100));
 }
 }
 }
 
 void GameController::incrementCounter()
 {
 counter++;
 }
 
 void GameController::spawnCombatants()
 {
 if (counter % 250 == 0 && cList.size() < 8)
 {
 //printf("SPAWN\n\n");
 Combatant *c = new Combatant(10, "Models/Warrior.obj");
 cList.push_front(c);
 }
 AwesomeGL::setScore(cList.size());
 }
 
 void GameController::moveProjectiles()
 {
 for (std::list<Projectile *>::iterator it = pList.begin(); it != pList.end(); ++it)
 {
 (*it)->move();
 (*it)->moveBoundingBox((*it)->getPos());
 
 glm::vec3 transAmt = (*it)->getTransAmt();
 
 if (transAmt.x > 105 || transAmt.x < -5 || transAmt.z > 105 || transAmt.z < -5)
 {
 AwesomeGL::removeEntity(*it);
 it = pList.erase(it);
 
 }
 }
 }
 
 void GameController::spawnProjectiles()
 {
 bool shoot = true;
 if (counter % 30 == 0)
 {
 for (std::list<Combatant *>::iterator it = cList.begin(); it != cList.end(); ++it)
 {
 if (abs(sqrt(((mc->getPos().x - (*it)->getPos().x) * (mc->getPos().x - (*it)->getPos().x)) + ((mc->getPos().z - (*it)->getPos().z)) * (mc->getPos().z - (*it)->getPos().z))) < 40 && shoot)
 {
 //printf("ATTACK\n\n");
 
 double x = mc->getPos().x - (*it)->getPos().x;
 double z = mc->getPos().z - (*it)->getPos().z;
 double length = sqrt((x * x) + (z * z));
 
 x = x / length;
 z = z / length;
 
 Projectile *p = new Projectile(50, "Models/cube.obj", glm::vec3(x, 0, z), mc->getPos());
 pList.push_front(p);
 shoot = false;
 //printf("Test\n");
 }
 }
 }
 }
 
 void GameController::checkCombatantCollision()
 {
 for (std::list<Combatant *>::iterator it = cList.begin(); it != cList.end(); ++it)
 {
 for (std::list<Combatant *>::iterator it2 = cList.begin(); it2 != cList.end(); ++it2)
 {
 if ((*it) != (*it2) && (*it)->collisionCheck(*it2))
 {
 glm::vec3 newMoveTo1 = (*it)->getMoveTo();
 glm::vec3 newMoveTo2 = (*it2)->getMoveTo();
 //printf("Combatant Collision\n");
 if ((*it)->getMoveTo().x >= (*it2)->getMoveTo().x)
 {
 if (newMoveTo1.x - 10 >= 0)
 newMoveTo1 = glm::vec3(newMoveTo1.x - 10, newMoveTo1.y, newMoveTo1.z);
 else
 newMoveTo1 = glm::vec3(0, newMoveTo1.y, newMoveTo1.z);
 
 if (newMoveTo2.x + 10 <= 100)
 newMoveTo2 = glm::vec3(newMoveTo2.x + 10, newMoveTo2.y, newMoveTo2.z);
 else
 newMoveTo2 = glm::vec3(100, newMoveTo2.y, newMoveTo2.z);
 }
 
 else
 {
 if (newMoveTo1.x + 10 <= 100)
 newMoveTo1 = glm::vec3(newMoveTo1.x + 10, newMoveTo1.y, newMoveTo1.z);
 else
 newMoveTo1 = glm::vec3(100, newMoveTo1.y, newMoveTo1.z);
 
 if (newMoveTo2.x - 10 >= 0)
 newMoveTo2 = glm::vec3(newMoveTo2.x - 10, newMoveTo2.y, newMoveTo2.z);
 else
 newMoveTo2 = glm::vec3(0, newMoveTo2.y, newMoveTo2.z);
 }
 
 
 
 if ((*it)->getMoveTo().z >= (*it2)->getMoveTo().z)
 {
 if (newMoveTo1.z - 10 >= 0)
 newMoveTo1 = glm::vec3(newMoveTo1.x, newMoveTo1.y, newMoveTo1.z - 10);
 else
 newMoveTo1 = glm::vec3(newMoveTo1.x, newMoveTo1.y, 0);
 
 if (newMoveTo2.z + 10 <= 100)
 newMoveTo2 = glm::vec3(newMoveTo2.x, newMoveTo2.y, newMoveTo2.z + 10);
 else
 newMoveTo2 = glm::vec3(newMoveTo2.x, newMoveTo2.y, 100);
 }
 
 else
 {
 if (newMoveTo1.z + 10 <= 100)
 newMoveTo1 = glm::vec3(newMoveTo1.x, newMoveTo1.y, newMoveTo1.z + 10);
 else
 newMoveTo1 = glm::vec3(newMoveTo1.x, newMoveTo1.y, 100);
 
 if (newMoveTo2.z - 10 >= 0)
 newMoveTo2 = glm::vec3(newMoveTo2.x, newMoveTo2.y, newMoveTo2.z - 10);
 else
 newMoveTo2 = glm::vec3(newMoveTo2.x, newMoveTo2.y, 0);
 }
 
 (*it)->setMoveTo(newMoveTo1);
 (*it2)->setMoveTo(newMoveTo2);
 }
 }
 }
 }
 
 void GameController::checkProjectileCollision()
 {
 for (std::list<Combatant*>::iterator it1 = cList.begin(); it1 != cList.end(); ++it1)
 {
 for (std::list<Projectile*>::iterator it2 = pList.begin(); it2 != pList.end(); ++it2)
 {
 if (cList.size() > 0 && (*it2)->collisionCheck(*it1))
 {
 (*it2)->deleteProjectile();
 
 printf("B it2: %d\n", (*it2));
 it2 = pList.erase(it2);
 printf("A it2: %d\n", (*it2));
 
 (*it1)->decrementHealth();
 
 if ((*it1)->getHealth() <= 0)
 {
 (*it1)->deleteCombatant();
 it1 = cList.erase(it1);
 }
 }
 }
 }
 }
 
 void GameController::checkMCCollision()
 {
 for (std::list<Combatant *>::iterator it = cList.begin(); it != cList.end(); ++it)
 {
 //printf("Checking MC Collision\n");
 if (cList.size() > 0 && (mc)->collisionCheck(*it))
 {
 mc->setColor();
 printf("\nMC Collsion\n\n");
 }
 }
 }
 
 MainCharacter* GameController::getMC()
 {
 return mc;
 }*/







