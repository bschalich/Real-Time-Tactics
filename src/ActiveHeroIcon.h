//
//  ActiveHeroIcon.h
//  
//
//  Created by Bennett Schalich on 5/30/14.
//
//

#ifndef ____ActiveHeroIcon__
#define ____ActiveHeroIcon__


#include "Entity.h"
#include "AwesomeGL.h"

using namespace AwesomeGL;

class ActiveHeroIcon
{
public:
   ActiveHeroIcon(Entity *entity);
   ~ActiveHeroIcon();
   
   void Update();
   void setVisible(bool visible);
   bool getVisible();
   Entity* getEntity();

private:
   GLuint ahIcon_vertex_buffer;
   Entity *entity;
   bool isVisible;
};

#endif /* defined(____ActiveHeroIcon__) */
