#ifndef __EventHandler__
#define __EventHandler__

#include <iostream>
#include "AwesomeGL.h"
#include "Combatant.h"
#include "Tween.h"
#include "Camera.h"
#include <cmath>
#include "StateMachine.h"


class EventHandler {
public:
   EventHandler();
   ~EventHandler();

   void setRay(glm::vec3 ray);
   void Update();
   sf::Clock *specialCooldown;
private:
   bool clickedHero;
   bool focus;
};

#endif
