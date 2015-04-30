#include "MapTile.h"

using namespace AwesomeGL;

GLuint mapVert;
GLuint mapIndex;
GLuint mapNormal;
int    mapNumVert;
GLuint mapUV;

MapTile::MapTile(int x, int z)
{
   EntityBuffObj = mapVert;
   EntityNormalBuffObj = mapNormal;
   EntityIndxBuffObj = mapIndex;
   EntityiboLen = mapNumVert;
   EntityUVBuffObj = mapUV;
   
   translate(glm::vec3(x*10, 0, z*10));
   scale(glm::vec3(0.1f, 0.1f, 0.1f));
   setColor(glm::vec3(0.1f, 0.7f, 0.3f));
   
   mt.seed(rd.operator()());
   intDist = std::uniform_int_distribution<int>(0, 100);
   //rand() % 80 + 300;
   trans.y = 300 + z*20;
   xPos = x;
   zPos = z;
   
   Tween *down = new Tween(&trans.y, Tween::OUT_SINE, trans.y, 0, 2.5);
   down->start();

   object = NULL;
   occupied = false;
   addTile(this);
}

MapTile::~MapTile() {
   
}

bool MapTile::checkOccupied() {
   return occupied;
}

void MapTile::setOccupied(bool oc) {
   occupied = oc;
}

void MapTile::setObject(std::string mesh, std::string texture, double height, glm::vec3 scale, bool occupy)
{
   if (object)
   {
      removeEntity(object);
      delete(object);
   }
   
   //printf("xPos: %d    zPos: %d\n", xPos, zPos);

   object = new Entity(mesh, texture);
   object->scale(scale);

   object->eBoundingBox.max *= scale;
   object->eBoundingBox.min *= scale;

    printf("Max: %f %f %f\n", object->eBoundingBox.max.x, object->eBoundingBox.max.y, object->eBoundingBox.max.z);
    printf("Min: %f %f %f\n", object->eBoundingBox.min.x, object->eBoundingBox.min.y, object->eBoundingBox.min.z);
   
	object->translate(glm::vec3(xPos * TILE_SIZE, height, zPos * TILE_SIZE));
   object->trans.y = intDist(mt) + 300;
   Tween *down = new Tween(&object->trans.y, Tween::OUT_SINE, trans.y, height, 2.5, 1.5);
   down->start();

   object->eBoundingBox.min = vec3(object->eBoundingBox.min.x + object->getPos().x, object->eBoundingBox.min.y + 25, object->eBoundingBox.min.z + object->getPos().z);
   object->eBoundingBox.max = vec3(object->eBoundingBox.max.x + object->getPos().x, object->eBoundingBox.max.y + 50, object->eBoundingBox.max.z + object->getPos().z);

	/*object->bb[0] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    object->bb[0]->scale(vec3(.01, .01, .01));
	object->bb[0]->setColor(vec3(1, 0, 0));
    object->bb[0]->translate(object->eBoundingBox.max);
    
    object->bb[1] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    object->bb[1]->scale(vec3(.01, .01, .01));
    object->bb[1]->translate(object->eBoundingBox.min);
    
    object->bb[2] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    object->bb[2]->scale(vec3(.01, .01, .01));
    object->bb[2]->translate(vec3(object->eBoundingBox.max.x, object->eBoundingBox.max.y, object->eBoundingBox.min.z));
    
    object->bb[3] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    object->bb[3]->scale(vec3(.01, .01, .01));
    object->bb[3]->translate(vec3(eBoundingBox.max.x, object->eBoundingBox.min.y, object->eBoundingBox.min.z));
    
    object->bb[4] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    object->bb[4]->scale(vec3(.01, .01, .01));
    object->bb[4]->translate(vec3(object->eBoundingBox.max.x, object->eBoundingBox.min.y, object->eBoundingBox.max.z));
    
    object->bb[5] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    object->bb[5]->scale(vec3(.01, .01, .01));
    object->bb[5]->translate(vec3(object->eBoundingBox.min.x, object->eBoundingBox.min.y, object->eBoundingBox.max.z));
    
    object->bb[6] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    object->bb[6]->scale(vec3(.01, .01, .01));
    object->bb[6]->translate(vec3(object->eBoundingBox.min.x, object->eBoundingBox.max.y, object->eBoundingBox.min.z));
    
    object->bb[7] = new Entity("Models/Warrior.dae", "Models/yellow.bmp");
    object->bb[7]->scale(vec3(.01, .01, .01));
    object->bb[7]->translate(vec3(object->eBoundingBox.min.x, object->eBoundingBox.max.y, object->eBoundingBox.max.z));
    
    addEntity(object->bb[0]);
    addEntity(object->bb[1]);
    addEntity(object->bb[2]);
    addEntity(object->bb[3]);
    addEntity(object->bb[4]);
    addEntity(object->bb[5]);
    addEntity(object->bb[6]);
    addEntity(object->bb[7]);
	*/
   
   object->setColor(vec3(0.2, 0.7, 0.2));
   addEntity(object);
   this->occupied = occupy;
}

Entity* MapTile::getObject()
{
   return object;
}

void MapTile::Update() {
   ModelTrans.loadIdentity();
   ModelTrans.pushMatrix();
   ModelTrans.translate(trans);
   ModelTrans.scale(scaleV.x, scaleV.y, scaleV.z);
   
   glm::mat4 shadowMVP = getShadowProjectionMatrix() * getShadowViewMatrix() * getModelMatrix();
   glm::mat4 shadowBiasMatrix = biasMatrix*shadowMVP;
   glm::mat4 MVP = projectionMatrix * viewMatrix * getModelMatrix();
   glm::mat3 m_inv_transp = glm::transpose(glm::inverse(glm::mat3(ModelTrans.modelViewMatrix)));
   
   glUniformMatrix4fv(h_MVP, 1, GL_FALSE, glm::value_ptr(MVP));
   glUniformMatrix3fv(h_M_inv_trans, 1, GL_FALSE, glm::value_ptr(m_inv_transp));
   glUniformMatrix4fv(h_shadowBiasMVP, 1, GL_FALSE, glm::value_ptr(shadowBiasMatrix));
   //glUniformMatrix4fv(h_projectionMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
   glUniformMatrix4fv(h_viewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
   glUniformMatrix4fv(h_modelMatrix, 1, GL_FALSE, glm::value_ptr(getModelMatrix()));
   glUniformMatrix4fv(h_lightPos, 1, GL_FALSE, glm::value_ptr(lightPos));

   
   safe_glEnableVertexAttribArray(h_aPosition);
   glBindBuffer(GL_ARRAY_BUFFER, mapVert);
   safe_glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mapIndex);
   safe_glEnableVertexAttribArray(h_aNormal);
   glBindBuffer(GL_ARRAY_BUFFER, mapNormal);
   safe_glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
   
   safe_glEnableVertexAttribArray(h_aUV);
   glBindBuffer(GL_ARRAY_BUFFER, mapUV);
   safe_glVertexAttribPointer(h_aUV, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

   glUniform3f(h_uColor, color.x, color.y, color.z);
   
   glDrawElements(GL_TRIANGLES, mapNumVert, GL_UNSIGNED_SHORT, 0);
   ModelTrans.popMatrix();
   
   glDisableVertexAttribArray(h_aNormal);
   glDisableVertexAttribArray(h_aPosition);
}