//
//  StateMachine.h
//
//
//  Created by Bennett Schalich on 4/21/14.
//
//
#ifndef __StateMachine__
#define __StateMachine__

class Combatant;

#include <list>
#include <ctime>
#include <random>

#include "AwesomeGL.h"
#include "Combatant.h"

using namespace AwesomeGL;

class StateMachine
{
public:
   enum State {NOTHING, MOVE, ATTACK, HALT, WANDER, SPECIAL};
   
   StateMachine(Combatant *combatant);
   ~StateMachine();
   
   sf::Clock *stopTimer;
   
   State currentState;
   
   void runActiveState();
   //void interruptState();
   
private:
   Combatant *combatant;
   bool runningState;

   std::mt19937 generator;
   std::uniform_int_distribution<int> wander_distance;
   std::uniform_int_distribution<int> wander_direction;
   
   int dir[3];
};

#endif