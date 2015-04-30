#ifndef __Entity__
#define __Entity__

#include <iostream>
#include "AwesomeGL.h"
#include <iterator>
#include <vector>
#include <string>

class Entity {
public:
    Entity(std::string mesh, std::string texture);
   
   //virtual ~Entity();
   void translate(glm::vec3 coord);
   void scale(glm::vec3 scaleV);
   void rotate(float angle, glm::vec3 axis);
   virtual void Update();
   void setTransAmt(glm::vec3 transAmt);

   GLuint tex;

    struct EBB {
		glm::vec3 max;
		glm::vec3 min;
   };

	EBB eBoundingBox;
	EBB ogBoundingBox;
   
   void setColor(glm::vec3 color);
   glm::vec3 getPos();
   glm::vec3 getScale();
   float getAngle();
   glm::vec3 getAxis();
   bool collisionCheck(Entity *entity);
   bool collisionPointInBox(EBB bBox, glm::vec3 point);
   void moveBoundingBox(vec3 oldPos);
   glm::vec3 getTransAmt();
   
   GLuint EntityBuffObj, EntityIndxBuffObj, EntityNormalBuffObj, EntityUVBuffObj;
   GLuint BoneIndexesBuffObj, BoneWeightsBuffObj;
   std::vector<std::vector<keyframe_t> > frames;
   double anim_offset;
   double anim_time;
   double anim_step;

	int EntityiboLen;
   void drawShadow();
   bool rayIntersectEntity(glm::vec3 origin, glm::vec3 direction);

   glm::vec3 trans;

protected:
   glm::vec3 transAmt;
   glm::vec3 scaleV;
   float angle;
   glm::vec3 axis;
   glm::vec3 color;
   
   Entity();

   vec3 rayIntersectPlane(glm::vec3 origin, glm::vec3 direction, glm::vec3 planeNormal, float planeDistance);
};


#endif
