//
//  ActiveHeroIcon.cpp
//  
//
//  Created by Bennett Schalich on 5/30/14.
//
//

#include "ActiveHeroIcon.h"

ActiveHeroIcon::ActiveHeroIcon(Entity *entity)
{
   this->entity = entity;
   
   static const GLfloat g_vertex_buffer_data[] = {
      -2.5f, .0f, .0f,
      .0f, -5.0f, .0f,
      .0f, 5.0f, .0f,
      2.5f, .0f, .0f,
      /*-5.0f, -5.0f, 0.0f,
      5.0f, -5.0f, 0.0f,
      -5.0f,  5.0f, 0.0f,
      5.0f,  5.0f, 0.0f,*/
	};
   
   addAHIcon(this);
	glGenBuffers(1, &ahIcon_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, ahIcon_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
   
   isVisible = false;
}

ActiveHeroIcon::~ActiveHeroIcon()
{
   
}

void ActiveHeroIcon::setVisible(bool visible)
{
   isVisible = visible;
}

bool ActiveHeroIcon::getVisible()
{
   return isVisible;
}

Entity* ActiveHeroIcon::getEntity()
{
   return entity;
}

void ActiveHeroIcon::Update()
{
   glm::mat4 ViewMatrix = AwesomeGL::getViewMatrix();
   glm::mat4 ProjectionMatrix = AwesomeGL::getProjectionMatrix();
   
   glm::vec3 CameraPosition(glm::inverse(ViewMatrix)[3]);
   
   glm::mat4 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
   
   glUseProgram(h_icon);
   
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, tex_yellow);
   glUniform1i(h_IconTexture, 0);
   
   glUniform3f(h_CameraRightIcon, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
   glUniform3f(h_CameraUpIcon, ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
   
   glUniform3f(h_IconPos, entity->getPos().x, entity->getPos().y + 32.0f, entity->getPos().z);
   
   glUniform2f(h_IconSize, .7f, .7f);
   
   glUniformMatrix4fv(h_ViewProjMatrixIcon, 1, GL_FALSE, &ViewProjectionMatrix[0][0]);
   
   
   
   glEnableVertexAttribArray(h_IconSquareVertices);
   glBindBuffer(GL_ARRAY_BUFFER, ahIcon_vertex_buffer);
   glVertexAttribPointer(h_IconSquareVertices, 3, GL_FLOAT, GL_FALSE, 0,(void*)0);
   
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
   
   glUseProgram(0);
   glDisableVertexAttribArray(h_IconSquareVertices);
}





