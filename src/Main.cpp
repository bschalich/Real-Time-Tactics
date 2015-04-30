#include "AwesomeGL.h"

#include "EventHandler.h"
#include "GameMap.h"
#include "GameController.h"
#include "Tween.h"
#include "UI.h"
#include "Billboard.h"
#include "Camera.h"
#include "Entity.h"

using namespace AwesomeGL;

int main() {
   // Request a 32-bits depth buffer when creating the window
   sf::ContextSettings contextSettings;
   contextSettings.depthBits = 32;
   contextSettings.minorVersion = 0;
   contextSettings.majorVersion = 3;
   
   bool displayHealth = true;
   
   // Create the main window
   sf::Window window(sf::VideoMode(1280, 720), "Real Time Tactics", sf::Style::Default, contextSettings);
   window.setVerticalSyncEnabled(true);
   UI *ui = new UI(window.getSize().x, window.getSize().y);

   // Make it the active window for OpenGL calls
   window.setActive();
#ifndef __APPLE__
   if (glewInit())
   {
	   fprintf(stderr, "Error initializing GLEW\n");
	   return false;
   }
   
   if (!GLEW_ARB_draw_instanced || !GLEW_ARB_instanced_arrays){
      fprintf(stderr, "GPU does not support instancing");
      getchar();
      return -1;
   }
#endif
   
   getGLversion();
   
   if (!initGL()) {
      printf("error initializing AwesomeGL");
      return 1;
   }
   AwesomeGL::camera = new Camera();
   // Initialize EventHandler
   EventHandler *eventHandler = new EventHandler();
   
   // Game Map
   AwesomeGL::map = new GameMap();
   GameController *gc = new GameController(AwesomeGL::map, ui);
   
   tauntSoundBuffer.loadFromFile("Sound/taunt.wav");
   
   bgSoundBuffer.loadFromFile("Sound/war.ogg");
   bgSound.setBuffer(bgSoundBuffer);
   bgSound.setVolume(40);
   bgSound.play();
   bgSound.setLoop(true);
   
   deathSoundBuffer.loadFromFile("Sound/older human dies.wav");
   startSound.loadFromFile("Sound/bigswordout.wav");
   music.loadFromFile("Sound/windstrong.wav");
   endSound.loadFromFile("Sound/journeysample.wav");
   
   tauntSound.setBuffer(tauntSoundBuffer);
   deathSound.setBuffer(deathSoundBuffer);
   start.setBuffer(startSound);
   
   colorTimer = new sf::Clock();
   
   //counter for changing directions
   
   //RenderingHelper ModelTrans;
   ModelTrans.useModelViewMatrix();
   
   // Configure the viewport (the same size as the window)
   glViewport(0, 0, window.getSize().x, window.getSize().y);
   
   AwesomeGL::clock = new sf::Clock();
   AwesomeGL::deltaClock = new sf::Clock();
   sf::Clock *displayHealthClock = new sf::Clock();
   
   AwesomeGL::window = &window;
   
   window.setFramerateLimit(120);
   
   musicSound.setBuffer(music);
   musicSound.setVolume(60);
   musicSound.setLoop(true);
   musicSound.play();
   
   endMusic.setBuffer(endSound);
   endMusic.setVolume(7);
   endMusic.setLoop(true);
   
   bool end = false;
   bool flag = true;
   bool winFlag = false;
   
   Tween *tweenCamStart = new Tween(&AwesomeGL::cameraPos.y, Tween::OUT_SINE, AwesomeGL::cameraPos.y, AwesomeGL::cameraPos.y+600, 1, true);
   tweenCamStart->start();
      
      while (window.isOpen()) {
      AwesomeGL::deltaTime = AwesomeGL::deltaClock->restart();
      // Process events
      
      eventHandler->Update();
      
      for (int i = 0; i < tweenList.size(); i++) {
         tweenList[i]->updateTween(deltaTime.asSeconds());
         
         if (tweenList[i]->complete) {
            tweenList.erase(tweenList.begin() + i);
         }
      }
      
      // Render entities
      AwesomeGL::Update();
      
      gc->Update();
      
      if (flag && (enemyList.size() == 0 || heroList.size() == 0))
      {
         musicSound.stop();
         end = true;
      }
      
      if (end == true)
      {
         endMusic.play();
         flag = false;
         end = false;
         winFlag = true;

		 for (int i = 0; i < entityList.size(); i++)
		 {
			 Tween *endTween = new Tween(&entityList[i]->trans.y, Tween::INOUT_CIRC, entityList[i]->trans.y, entityList[i]->trans.y + 400, 1.5, 1, true);
			 endTween->start();
		 }

		 for (int i = 0; i < tileList.size(); i++)
		 {
			 Tween *endTween = new Tween(&tileList[i]->trans.y, Tween::INOUT_CIRC, tileList[i]->trans.y, tileList[i]->trans.y - 400, 1.5, 1, true);
			 endTween->start();
		 }
      }
      
      if (winFlag)
      {
         AwesomeGL::setWin();
		 ui->gameOver();
      }
      
      ui->update();
      
      //printf("billboardList size: %d\n", billboardList.size());
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && displayHealthClock->getElapsedTime().asSeconds() > .25)
      {
         displayHealthClock->restart();
         displayHealth = !displayHealth;
      }
         
         //printf("icon list size: %d\n", ahIconList.size());
      for (int i = 0; i < ahIconList.size(); i++)
      {
         if (ahIconList[i]->getEntity() == activeHero)
            ahIconList[i]->Update();
      }
         
      if (displayHealth)
      {
         for (int i = 0; i < billboardList.size(); i++)
         {
            //printf("BILLBOARD\n");
            billboardList[i]->Update();
         }
      }
            

	   glUseProgram(0);
      // Finally, display the rendered frame on screen
      window.display();
   }
   
   return EXIT_SUCCESS;
}
