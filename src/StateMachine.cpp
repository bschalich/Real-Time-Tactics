//
//  FSM.cpp
//
//
//  Created by Bennett Schalich on 4/21/14.
//
//

#include "StateMachine.h"

StateMachine::StateMachine(Combatant *combatant) : wander_distance(1, 8), wander_direction(0, 4)
{
   srand((unsigned)time(0));
   this->combatant = combatant;
   currentState = NOTHING;
   runningState = false;
   stopTimer = new sf::Clock();
   dir[0] = 1;
   dir[1] = -1;
   dir[2] = 0;
}

StateMachine::~StateMachine()
{
   
}

void StateMachine::runActiveState()
{
      switch (currentState)
      {
         {case MOVE:
            /*if (!combatant->getIsHero())
               printf("Moving\n");*/
            
            if (combatant->getEnemy() && !runningState)
            {
               combatant->moveTo(int(combatant->getEnemy()->getPos().x / 10), int(combatant->getEnemy()->getPos().z / 10));
            }
            
            else
            {
               //printf("Going to Halt\n");
               runningState = false;
               currentState = HALT;
            }

            break;}
            
         {case ATTACK:
            /*if (!combatant->getIsHero())
               printf("Attacking\n");*/
         
            if (combatant->getEnemy() && combatant->checkForAttack()) {
               combatant->attack(combatant->getEnemy());
               combatant->animateAttack();
            }
            
            else if (!combatant->getIsHero())
            {
               currentState = MOVE;
            }
            
            break;}
            
         /*{case SPECIAL:
            if (combatant->getEnemy() && combatant->checkForAttack()) {
               combatant->special(combatant->getEnemy());
               combatant->animateAttack();
            }
            break;}*/
            
         {case HALT:
            /*if (!combatant->getIsHero())
               printf("Halting\n");*/
            if (!combatant->getEnemy())
            {
               if (stopTimer->getElapsedTime().asSeconds() > 1.5)
               {
                  stopTimer->restart();
                  currentState = WANDER;
               }
            }
            
            else
            {
               currentState = MOVE;
            }
            break;}
            
         {case WANDER:
            /*if (!combatant->getIsHero())
               printf("Wandering\n");*/
            float x = (float)(wander_distance(generator));
            float z = (float)(wander_distance(generator));
            int xDir = dir[wander_direction(generator)];
            int zDir = dir[wander_direction(generator)];
            
            if (!combatant->getEnemy())
            {
               if (!combatant->isMoving())
               {
                  if (!runningState)
                  {
                     combatant->moveTo((int)(combatant->getPos().x/TILE_SIZE + xDir*x),
                                       (int)(combatant->getPos().z/TILE_SIZE + zDir*z));
                     runningState = true;
                  }
                  
                  else if (!combatant->isMoving() && runningState)
                  {
                     stopTimer->restart();
                     
                     currentState = HALT;
                     runningState = false;
                  }
               }
            }
            
            else
               currentState = MOVE;
            
            break;}
            
         {case NOTHING:
            /*if (!combatant->getIsHero())
               printf("Nothing\n");*/
            break;}
            
         {default:
            if (!combatant->getIsHero())
               //printf("Default\n");;
            break;}
      }
}


