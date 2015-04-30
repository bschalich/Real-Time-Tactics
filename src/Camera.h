#ifndef __Camera__
#define __Camera__

#include "AwesomeGL.h"
#include "GameMap.h"
#include "Tween.h"

class Camera {
   
public:
   Camera();
   ~Camera();
   
   void moveTo(Entity*);
   void zoom(bool zoomOnly=false);
   void shake();
   
   bool zoomToggle;
   bool cameraLock;
   
private:
   glm::vec2 getCamCoord(glm::vec3);
   
   Tween* camTweenX;
   Tween* camTweenY;
   
   Tween* zoomOutX;
   Tween* zoomOutY;
   Tween* zoomOutZ;
   Tween* zoomInX;
   Tween* zoomInY;
   Tween* zoomInZ;
   
   Tween* shakeX;
   Tween* shakeY;
   
   sf::Clock *zoomTimer;
   sf::Clock *shakeTimer;
   
};

#endif