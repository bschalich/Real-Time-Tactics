#include "EventHandler.h"
#include "MapTile.h"

using namespace AwesomeGL;

EventHandler::EventHandler()
{
   focus = true;
   clickedHero = false;
   specialCooldown = new sf::Clock();
}

EventHandler::~EventHandler()
{
   
}

void EventHandler::Update()
{
   if (focus && !camera->cameraLock) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
         if ((camera->zoomToggle && AwesomeGL::cameraPos.y < 1500) ||  (!camera->zoomToggle && AwesomeGL::cameraPos.y < 3500))
         AwesomeGL::cameraPos.y += 1000 * AwesomeGL::deltaTime.asSeconds();
         //std::cout << "Y: " << AwesomeGL::cameraPos.y << std::endl;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
         if ((camera->zoomToggle && AwesomeGL::cameraPos.x > -2500) || (!camera->zoomToggle && AwesomeGL::cameraPos.x > -5500))
         AwesomeGL::cameraPos.x -= 1000 * AwesomeGL::deltaTime.asSeconds();
         //std::cout << "X: " << AwesomeGL::cameraPos.x << std::endl;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
         if (AwesomeGL::cameraPos.y > 300) //-400
            AwesomeGL::cameraPos.y -= 1000 * AwesomeGL::deltaTime.asSeconds();
         //std::cout << "Y: " << AwesomeGL::cameraPos.y << std::endl;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
         if (AwesomeGL::cameraPos.x < 300) //1100
            AwesomeGL::cameraPos.x += 1000 * AwesomeGL::deltaTime.asSeconds();
         //std::cout << "X: " << AwesomeGL::cameraPos.x << std::endl;
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
         if (activeHero != NULL && activeHero->type == AwesomeGL::MAGE) {
            if (specialCooldown->getElapsedTime().asSeconds() > 20) {
               camera->zoomToggle = false;
               camera->zoom();
               activeHero->setSpecial(true);
               specialCooldown->restart();
               printf("Special set\n");
            }
         }
         else if (activeHero != NULL) {
            if (specialCooldown->getElapsedTime().asSeconds() > 10) {
               if (activeHero->type == AwesomeGL::WARRIOR) {
                  activeHero->rageEffect->start();
               }
               else if (activeHero->type == AwesomeGL::ARCHER) {
                  activeHero->dodgeEffect->start();
                  activeHero->walkSpeed = 30;
                  activeHero->potionSound.play();
               }
               camera->moveTo(activeHero);
               activeHero->setSpecial(true);
               specialCooldown->restart();
               printf("Special set\n");
            }
         }
      }
      
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
         AwesomeGL::lightPos.x += 50 * AwesomeGL::deltaTime.asSeconds();
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
         AwesomeGL::lightPos.x -= 50 * AwesomeGL::deltaTime.asSeconds();
      }
   }
   sf::Event event;
   while (window->pollEvent(event)) {
      switch (event.type) {
            // Close window: exit
         case sf::Event::Closed:
            window->close();
            break;
            
         case sf::Event::GainedFocus:
            focus = true;
            break;
            
         case sf::Event::LostFocus:
            focus = false;
            break;
            
            // Escape key: exit
         case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape) {
               window->close();
            }
            
            else if (event.key.code == sf::Keyboard::Space && !camera->cameraLock) {
				 	activeHeroIndex += 1;
				   if (activeHeroIndex >= heroList.size())
					   activeHeroIndex = 0;
               
				   activeHero = heroList[activeHeroIndex];
               //camera->moveTo(activeHero);
            }
            else if (event.key.code == sf::Keyboard::Tab) {
               camera->zoom();
            }
            else if (event.key.code == sf::Keyboard::F) {
               std::cout << "CAMERA: " << AwesomeGL::cameraPos.x << " " << AwesomeGL::cameraPos.y << std::endl;
               camera->shake();
            }

            break;
            
            
            // Resize event: adjust the viewport
         case sf::Event::Resized:
            glViewport(0, 0, event.size.width, event.size.height);
            break;
            
         case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left && AwesomeGL::clock->getElapsedTime().asSeconds() > 6 && activeHero != NULL ) {
               GLfloat depth;
               glReadPixels(event.mouseButton.x, window->getSize().y - event.mouseButton.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
               glm::vec3 rayDir = glm::unProject(glm::vec3(event.mouseButton.x, window->getSize().y - event.mouseButton.y, depth), getViewMatrix(), getProjectionMatrix(), glm::vec4(0, 0, window->getSize().x, window->getSize().y));
               std::cout << "X: " << AwesomeGL::cameraPos.x << " Y: " << AwesomeGL::cameraPos.y << std::endl;
               //printf("Raydir: %f %f %f\n", rayDir.x, rayDir.y, rayDir.z);
               bool clicked = false;
               
               for (unsigned int i = 0; i < entityList.size(); i++)
               {
                  clickedHero = false;
                  //********NORMALIZE RAYDIR
                  if (entityList[i]->rayIntersectEntity(glm::vec3(0, 0, 0), rayDir)
                      && dynamic_cast<Combatant*>(entityList[i])) {
                     //if hero, make activeHero
                     if (((Combatant*)entityList[i])->getIsHero()) {
                        activeHero = (Combatant*)entityList[i];
                        //camera->zoomToggle = false;
                        //camera->zoom();
                        //camera->moveTo(entityList[i]);
                        clickedHero = true;
                        break;
                        //glm::vec3 test = glm::project(activeHero->getPos(), getViewMatrix()*getModelMatrix(), getProjectionMatrix(), glm::vec4(0, 0, window->getSize().x, window->getSize().y));
                        /*Camera::moveCameraXOutSine(activeHero->getPos().x);
                         Camera::moveCameraYOutSine(activeHero->getPos().z);
                         printf("camPos: %f, %f, %f\n", cameraPos.x, cameraPos.y, cameraPos.z);
                         printf("Activehero: %f, %f, %f\n", activeHero->getPos().x, activeHero->getPos().y, activeHero->getPos().z);*/
                     }
                     //
                  }
               }
               
              // if (!clickedHero) {
                  setRay(rayDir);
             //  }
            }
            break;
            
            /*case sf::Event::MouseWheelMoved:
             if (event.mouseWheel.delta > 0) {
             if (zoomFactor.x < 20)
             zoomFactor += 1;
             }
             else if (event.mouseWheel.delta < 0) {
             if (zoomFactor.x > 7)
             zoomFactor -= 1;
             }
             break;*/
            
            
         default:
            break;
      }
   }
}

void EventHandler::setRay(glm::vec3 ray)
{
   if (ray.x > -5)
      activeHero->tilePos.x = abs(ceil(ray.x / TILE_SIZE - 0.5f));
   else
      activeHero->tilePos.x = -1;
   
   if (ray.z > -5)
      activeHero->tilePos.z = abs(ceil(ray.z / TILE_SIZE - 0.5f));
   else
      activeHero->tilePos.z = -1;
   //std::cout << tilePos.x << " " << tilePos.y << std::endl;
   for (int i = 0; i < tileList.size(); i++) {
      if (((MapTile*)tileList[i])->xPos == activeHero->tilePos.x && ((MapTile*)tileList[i])->zPos == activeHero->tilePos.z) {
         tileList[i]->setColor(glm::vec3(1, 1, 0));
         colorTimer->restart();
      }
   }
}
