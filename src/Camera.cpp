#include "Camera.h"

using namespace AwesomeGL;

Camera::Camera() {
   camTweenX = new Tween(&AwesomeGL::cameraPos.x, Tween::OUT_SINE, AwesomeGL::cameraPos.x, 0, 0.5);
   camTweenY = new Tween(&AwesomeGL::cameraPos.y, Tween::OUT_SINE, AwesomeGL::cameraPos.y, 0, 0.5);
   
   zoomTimer = new sf::Clock();
   shakeTimer = new sf::Clock();
   zoomOutX = new Tween(&zoomFactor.x, Tween::OUT_SINE, zoomFactor.x, 7, 0.5);
   zoomOutY = new Tween(&zoomFactor.y, Tween::OUT_SINE, zoomFactor.y, 7, 0.5);
   zoomOutZ = new Tween(&zoomFactor.z, Tween::OUT_SINE, zoomFactor.z, 7, 0.5);
   
   zoomInX = new Tween(&zoomFactor.x, Tween::OUT_SINE, zoomFactor.x, 15, 0.5);
   zoomInY = new Tween(&zoomFactor.y, Tween::OUT_SINE, zoomFactor.y, 15, 0.5);
   zoomInZ = new Tween(&zoomFactor.z, Tween::OUT_SINE, zoomFactor.z, 15, 0.5);
   
   zoomToggle = false;
   
   shakeX = new Tween(&cameraPos.x, Tween::OUT_BOUNCE, cameraPos.x, 0, 0.5);
   shakeY = new Tween(&cameraPos.y, Tween::OUT_BOUNCE, cameraPos.y, 0, 0.5);
   cameraLock = true;
}

Camera::~Camera() {
   
}

glm::vec2 Camera::getCamCoord(glm::vec3 pos) {
   if (zoomToggle) {
      if (pos.x <= 5*TILE_SIZE) {
         return glm::vec2(0, 600);
      }
      else if (pos.x <= 10*TILE_SIZE && pos.x > 5) {
         return glm::vec2(-600, 500);
      }
      else if (pos.x <= 15*TILE_SIZE && pos.x > 10) {
         return glm::vec2(-1000, 1300);
      }
      else if (pos.x <= 20*TILE_SIZE && pos.x > 15) {
         return glm::vec2(-1600, 1600);
      }
      else if (pos.x <= 25*TILE_SIZE && pos.x > 20) {
         return glm::vec2(-2100, 1800);
      }
      else if (pos.x <= 30*TILE_SIZE && pos.x > 25) {
         return glm::vec2(-2600, 2100);
      }
      else if (pos.x <= 35*TILE_SIZE && pos.x > 30) {
         return glm::vec2(-3100, 2500);
      }
      else if (pos.x <= 40*TILE_SIZE && pos.x > 35) {
         return glm::vec2(-3700, 2900);
      }
      else if (pos.x <= 45*TILE_SIZE && pos.x > 40) {
         return glm::vec2(-4200, 3100);
      }
      else if (pos.x <= 50*TILE_SIZE && pos.x > 45) {
         return glm::vec2(-4800, 3400);
      }
      else if (pos.x <= 60*TILE_SIZE && pos.x > 50) {
         return glm::vec2(-4800, 3500);
      }
      else {
         return glm::vec2(-2600, 2100);
      }
   }
   else {
      if (pos.x <= 20*TILE_SIZE) {
         return glm::vec2(-200, 200);
      }
      else if (pos.x <= 40*TILE_SIZE) {
         return glm::vec2(-2000, 1300);
      }
      else {
         return glm::vec2(-1000, 1000);
      }
   }
}

void Camera::moveTo(Entity* e) {
   if (zoomTimer->getElapsedTime().asSeconds() > 0.6 && !cameraLock && e->trans.x != 0 && e->trans.z != 0) {
      glm::vec2 camCoord = getCamCoord(e->getPos());
      
      /*zoomInX->setStartVal(zoomFactor.x);
      zoomInY->setStartVal(zoomFactor.y);
      zoomInZ->setStartVal(zoomFactor.z);
      zoomInX->reset();
      zoomInX->start();
      zoomInY->reset();
      zoomInY->start();
      zoomInZ->reset();
      zoomInZ->start();
      zoomToggle = false;
      zoomTimer->restart();*/
      
      camTweenX->setEndVal(camCoord.x);
      camTweenY->setEndVal(camCoord.y);
      camTweenX->setStartVal(AwesomeGL::cameraPos.x);
      camTweenY->setStartVal(AwesomeGL::cameraPos.y);
      camTweenX->reset();
      camTweenX->start();
      camTweenY->reset();
      camTweenY->start();
   }
}

void Camera::shake() {
   if (shakeTimer->getElapsedTime().asSeconds() > 0.7 && camTweenX->complete && camTweenY->complete && !cameraLock) {
      float shakesX[2] = {cameraPos.x+50, cameraPos.x-50};
      float shakesY[2] = {cameraPos.y+50, cameraPos.y-50};
      
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
         shakeY->setStartVal(shakesY[rand() % 2]);
         shakeY->setEndVal(cameraPos.y);
         shakeY->reset();
         shakeY->start();
      }
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
         shakeX->setStartVal(shakesX[rand() % 2]);
         shakeX->setEndVal(cameraPos.x);
         shakeX->reset();
         shakeX->start();
      }
      else {
         shakeY->setStartVal(shakesY[rand() % 2]);
         shakeY->setEndVal(cameraPos.y);
         shakeY->reset();
         shakeY->start();
         
         shakeX->setStartVal(shakesX[rand() % 2]);
         shakeX->setEndVal(cameraPos.x);
         shakeX->reset();
         shakeX->start();
      }
      shakeTimer->restart();
   }
}

void Camera::zoom(bool zoomOnly) {
   if (!cameraLock) {
      if (!zoomToggle && zoomTimer->getElapsedTime().asSeconds() > 0.6) {
         zoomOutX->setStartVal(zoomFactor.x);
         zoomOutY->setStartVal(zoomFactor.y);
         zoomOutZ->setStartVal(zoomFactor.z);
         zoomOutX->reset();
         zoomOutX->start();
         zoomOutY->reset();
         zoomOutY->start();
         zoomOutZ->reset();
         zoomOutZ->start();
         zoomToggle = true;
         zoomTimer->restart();
         
         if (!zoomOnly) {
            if (cameraPos.x >= -2600 && cameraPos.y < 2100) {
               camTweenX->setEndVal(-400);
               camTweenY->setEndVal(400);
            }
            else if (cameraPos.x >= -4800 && cameraPos.y < 3500) {
               camTweenX->setEndVal(-2000);
               camTweenY->setEndVal(1300);
            }
            else {
               camTweenX->setEndVal(-1000);
               camTweenY->setEndVal(1000);
            }
            camTweenX->setStartVal(AwesomeGL::cameraPos.x);
            camTweenY->setStartVal(AwesomeGL::cameraPos.y);
            camTweenX->reset();
            camTweenX->start();
            camTweenY->reset();
            camTweenY->start();
         }
         else {
            zoomToggle = false;
         }
      }
      else if (zoomToggle && zoomTimer->getElapsedTime().asSeconds() > 0.6) {
         zoomInX->setStartVal(zoomFactor.x);
         zoomInY->setStartVal(zoomFactor.y);
         zoomInZ->setStartVal(zoomFactor.z);
         zoomInX->reset();
         zoomInX->start();
         zoomInY->reset();
         zoomInY->start();
         zoomInZ->reset();
         zoomInZ->start();
         zoomToggle = false;
         zoomTimer->restart();
         
         if (!zoomOnly) {
            if (cameraPos.x >= -200 && cameraPos.y < 800) {
               camTweenX->setEndVal(0);
               camTweenY->setEndVal(600);
            }
            else if (cameraPos.x >= -800 && cameraPos.y < 800) {
               camTweenX->setEndVal(-1300);
               camTweenY->setEndVal(1300);
            }
            else if (cameraPos.x >= -1500 && cameraPos.y < 1100) {
               camTweenX->setEndVal(-2800);
               camTweenY->setEndVal(2200);
            }
            else if (cameraPos.x >= -2200 && cameraPos.y < 1500) {
               camTweenX->setEndVal(-4000);
               camTweenY->setEndVal(2800);
            }
            else if (cameraPos.x >= -2600 && cameraPos.y < 1600) {
               camTweenX->setEndVal(-4800);
               camTweenY->setEndVal(3400);
            }
            else {
               camTweenX->setEndVal(-2100);
               camTweenY->setEndVal(1800);
            }
            
            camTweenX->setStartVal(AwesomeGL::cameraPos.x);
            camTweenY->setStartVal(AwesomeGL::cameraPos.y);
            camTweenX->reset();
            camTweenX->start();
            camTweenY->reset();
            camTweenY->start();
         }
      }
   }
}