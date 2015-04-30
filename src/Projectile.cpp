//
//  Projectile.cpp
//  
//
//  Created by Bennett Schalich on 4/9/14.
//
//

#include "Projectile.h"

using namespace AwesomeGL;

Projectile::Projectile(int velocity, std::string mesh, std::string texture, glm::vec3 direction, glm::vec3 initPos, bool isFromHero, Combatant* from, AttackType attackType) : Entity(mesh, texture)
{
   this->attackType = attackType;
   this->velocity = velocity;
   this->direction = direction;
   transAmt = initPos;
   trans = initPos;
   this->isFromHero = isFromHero;

   state = AwesomeGL::MOVING;
   deathClock = new sf::Clock();

   this->setColor(vec3(1, 1, 1));
   dirDegrees = 0;
   
   scale(glm::vec3(4, 20, 4));
   
   eBoundingBox.max *= vec3(.01, .01, .01);
   eBoundingBox.min *= vec3(.01, .01, .01);
   //eBoundingBox.max += initPos;
   //eBoundingBox.min += initPos;

    eBoundingBox.min.y += 5;
	eBoundingBox.max.y += 5;

    ogBoundingBox.min = eBoundingBox.min;
	ogBoundingBox.max = eBoundingBox.max;
	
	/*
	bb[0] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    bb[0]->scale(vec3(.01, .01, .01));
	bb[0]->setColor(vec3(1, 0, 0));
    bb[0]->translate(eBoundingBox.max);
    
    bb[1] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    bb[1]->scale(vec3(.01, .01, .01));
    bb[1]->translate(eBoundingBox.min);
    
    bb[2] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    bb[2]->scale(vec3(.01, .01, .01));
    bb[2]->translate(vec3(eBoundingBox.max.x, eBoundingBox.max.y, eBoundingBox.min.z));
    
    bb[3] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    bb[3]->scale(vec3(.01, .01, .01));
    bb[3]->translate(vec3(eBoundingBox.max.x, eBoundingBox.min.y, eBoundingBox.min.z));
    
    bb[4] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    bb[4]->scale(vec3(.01, .01, .01));
    bb[4]->translate(vec3(eBoundingBox.max.x, eBoundingBox.min.y, eBoundingBox.max.z));
    
    bb[5] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    bb[5]->scale(vec3(.01, .01, .01));
    bb[5]->translate(vec3(eBoundingBox.min.x, eBoundingBox.min.y, eBoundingBox.max.z));
    
    bb[6] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    bb[6]->scale(vec3(.01, .01, .01));
    bb[6]->translate(vec3(eBoundingBox.min.x, eBoundingBox.max.y, eBoundingBox.min.z));
    
    bb[7] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    bb[7]->scale(vec3(.01, .01, .01));
    bb[7]->translate(vec3(eBoundingBox.min.x, eBoundingBox.max.y, eBoundingBox.max.z));
    
    addEntity(bb[0]);
    addEntity(bb[1]);
    addEntity(bb[2]);
    addEntity(bb[3]);
    addEntity(bb[4]);
    addEntity(bb[5]);
    addEntity(bb[6]);
    addEntity(bb[7]); */
   
   /*printf("Projectile CMax: %f %f %f\nCMin: %f %f %f\n\n", eBoundingBox.max.x,
	   eBoundingBox.max.y, eBoundingBox.max.z, eBoundingBox.min.x, 
	   eBoundingBox.min.y, eBoundingBox.min.z);*/
   //printf("initPos.x: %0f   initPos.y: %0f    initPos.z: %0f\n", initPos.x, initPos.y, initPos.z);
   addEntity(this);
   
   this->from = from;
}

Projectile::~Projectile()
{
}

int Projectile::getVelocity()
{
   return velocity;
}

void Projectile::setRotation(float rotationDegrees, glm::vec3 dir) {
   this->dirDegrees = rotationDegrees;
   rotate(rotationDegrees, dir);
}

glm::vec3 Projectile::getDirection()
{
   return direction;
}

void Projectile::move()
{
	if (state == AwesomeGL::MOVING)
	{
		transAmt.x = trans.x + (velocity * AwesomeGL::deltaTime.asSeconds() * -direction.x);
		transAmt.z = trans.z + (velocity * AwesomeGL::deltaTime.asSeconds() * -direction.z);
	}
	else if (state == AwesomeGL::ATTACHED) 
	{
		transAmt.x = attachedEntity->getPos().x;
		transAmt.z = attachedEntity->getPos().z;
	}

}

void Projectile::deleteProjectile()
{
   removeEntity(this);
}

void Projectile::projCollisionCheck()
{
	
	for (int i = 0; i < entityList.size(); i++)
	{
		if (this != entityList[i] && collisionCheck(entityList[i]))
		{
			if (dynamic_cast<Combatant*>(entityList[i]))
			{
				if (((Combatant*)entityList[i])->getIsHero() != isFromHero)
				{
					attachedEntity = entityList[i];
					state = AwesomeGL::ATTACHED;
					arrowHitSound.play();
					((Combatant*)attachedEntity)->decrementHealth(from);
               
               if (attackType == AwesomeGL::SPECIAL)
                  ((Combatant*)attachedEntity)->decrementHealth(from);
               
					break;
				}
			}
			else
			{
				state = AwesomeGL::ATTACHED_IO;
				break;
			}
		}
	}
}

void Projectile::Update()
{
   move();

   if (state == AwesomeGL::MOVING)
   {
		projCollisionCheck();
   }

   if (deathClock->getElapsedTime().asSeconds() >= 5)
   {
	   removeEntity(this);
   }
   translate(transAmt);
   
      eBoundingBox.min = vec3(ogBoundingBox.min.x + this->getPos().x, ogBoundingBox.min.y, ogBoundingBox.min.z + this->getPos().z);
   eBoundingBox.max = vec3(ogBoundingBox.max.x + this->getPos().x, ogBoundingBox.max.y, ogBoundingBox.max.z + this->getPos().z);
   
   /* bb[0]->translate(eBoundingBox.max);
    bb[1]->translate(eBoundingBox.min);
    bb[2]->translate(vec3(eBoundingBox.max.x, eBoundingBox.max.y, eBoundingBox.min.z));
    bb[3]->translate(vec3(eBoundingBox.max.x, eBoundingBox.min.y, eBoundingBox.min.z));
    bb[4]->translate(vec3(eBoundingBox.max.x, eBoundingBox.min.y, eBoundingBox.max.z));
    bb[5]->translate(vec3(eBoundingBox.min.x, eBoundingBox.min.y, eBoundingBox.max.z));
    bb[6]->translate(vec3(eBoundingBox.min.x, eBoundingBox.max.y, eBoundingBox.min.z));
    bb[7]->translate(vec3(eBoundingBox.min.x, eBoundingBox.max.y, eBoundingBox.max.z));
	
   */
   Entity::Update();
}

