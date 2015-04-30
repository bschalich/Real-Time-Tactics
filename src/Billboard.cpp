//
//  Billboard.cpp
//  
//
//  Created by Bennett Schalich on 5/13/14.
//
//

#include "Billboard.h"

Billboard::Billboard(Entity *entity, int health)
{
   this->entity = entity;
   
   static const GLfloat g_vertex_buffer_data[] = {
      -5.0f, -5.0f, 0.0f,
      5.0f, -5.0f, 0.0f,
      -5.0f,  5.0f, 0.0f,
      5.0f,  5.0f, 0.0f,
	};

	glGenBuffers(1, &billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
   
   addBillboard(this);
   this->health = health;
   this->oldHealth = health;
   thisHealth = health;
   tween = new Tween(&thisHealth, Tween::IN_SINE, oldHealth, 1, .5);
   
   //printf("buildboardList size: %d\n", billboardList.size());
}

void Billboard::setHealth(int health)
{
   this->health = health;
}

void Billboard::setOldHealth(int oldHealth)
{
   this->oldHealth = oldHealth;
}

void Billboard::startTween()
{
   //printf("oldHealth: %.2f\n", oldHealth);
   //printf("health: %.2f\n", health);
   tween->setStartVal(oldHealth);
   tween->setEndVal(health);
   tween->reset();
   //printf("reset oldHealth: %.2f\n", oldHealth);
  // printf("reset health: %.2f\n", health);
   tween->start();
}

void Billboard::Update()
{
   glm::mat4 ViewMatrix = AwesomeGL::getViewMatrix();
   glm::mat4 ProjectionMatrix = AwesomeGL::getProjectionMatrix();
   
   glm::vec3 CameraPosition(glm::inverse(ViewMatrix)[3]);
   
   glm::mat4 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
   
   glUseProgram(h_billboard);
   
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, tex_yellow);
   glUniform1i(h_BillboardTexture, 0);
   
   glUniform3f(h_CameraRight, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
   glUniform3f(h_CameraUp, ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
   
   glUniform3f(h_BillboardPos, entity->getPos().x, entity->getPos().y + 25.0f, entity->getPos().z);
   
   glUniform2f(h_BillboardSize, thisHealth * .15f, 0.125f);
   
   /*float LifeLevel = 0;
   glUniform1f(h_LifeLevel, LifeLevel);*/
   
   glUniformMatrix4fv(h_ViewProjMatrix, 1, GL_FALSE, &ViewProjectionMatrix[0][0]);
   
   
   glEnableVertexAttribArray(h_BillboardSquareVertices);
   glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
   glVertexAttribPointer(h_BillboardSquareVertices, 3, GL_FLOAT, GL_FALSE, 0,(void*)0);
   
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
   glUseProgram(0);
   glDisableVertexAttribArray(h_BillboardSquareVertices);
}