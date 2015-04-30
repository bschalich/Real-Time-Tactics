#include "Entity.h"

using namespace AwesomeGL;

Entity::Entity() : frames(std::vector<std::vector<keyframe_t> >())
{
   anim_offset = 0;
   anim_step = 0.03;
}

Entity::Entity(std::string mesh, std::string texture) : frames(modelMap[mesh].frames) {
   tex = *texMap[texture];
   Model &model = modelMap[mesh];
   EntityBuffObj = model.modelVert;
   EntityIndxBuffObj = model.modelIndex;
   EntityiboLen = model.modelNumVert;
   EntityNormalBuffObj = model.modelNormal;
   EntityUVBuffObj = model.modelUV;
   BoneIndexesBuffObj = model.modelBoneIndex;
   BoneWeightsBuffObj = model.modelBoneWeight;
   
	//Bounding Box
	this->eBoundingBox.max = boundingBox.max;
	this->eBoundingBox.min = boundingBox.min;

   anim_offset = 0;
    anim_time = 0;
   anim_step = 0.03;

    translate(glm::vec3(0, 0, 0));
    scale(glm::vec3(1, 1, 1));
    rotate(90, glm::vec3(0, 1, 0));
}

/*Entity::~Entity() {
   
}*/

bool Entity::rayIntersectEntity(glm::vec3 origin, glm::vec3 direction)
{
	vec3 point1 = rayIntersectPlane(origin, direction, glm::vec3(0, 0, 1), eBoundingBox.max.z);
	if (point1.x >= this->eBoundingBox.min.x &&
		point1.x <= this->eBoundingBox.max.x &&
		point1.y >= this->eBoundingBox.min.y &&
		point1.y <= this->eBoundingBox.max.y &&
		point1.z >= this->eBoundingBox.min.z &&
		point1.z <= this->eBoundingBox.max.z)
	{
		return true;
	}

	point1 = rayIntersectPlane(origin, direction, glm::vec3(0, 1, 0), eBoundingBox.max.y);
	if (point1.x >= this->eBoundingBox.min.x &&
		point1.x <= this->eBoundingBox.max.x &&
		point1.y >= this->eBoundingBox.min.y &&
		point1.y <= this->eBoundingBox.max.y &&
		point1.z >= this->eBoundingBox.min.z &&
		point1.z <= this->eBoundingBox.max.z)
	{
		return true;
	}

	point1 = rayIntersectPlane(origin, direction, glm::vec3(1, 0, 0), eBoundingBox.max.x);
	if (point1.x >= this->eBoundingBox.min.x &&
		point1.x <= this->eBoundingBox.max.x &&
		point1.y >= this->eBoundingBox.min.y &&
		point1.y <= this->eBoundingBox.max.y &&
		point1.z >= this->eBoundingBox.min.z &&
		point1.z <= this->eBoundingBox.max.z)
	{
		return true;
	}

	point1 = rayIntersectPlane(origin, direction, glm::vec3(0, 0, -1), eBoundingBox.max.z);

	if (point1.x >= this->eBoundingBox.min.x &&
		point1.x <= this->eBoundingBox.max.x &&
		point1.y >= this->eBoundingBox.min.y &&
		point1.y <= this->eBoundingBox.max.y &&
		point1.z >= this->eBoundingBox.min.z &&
		point1.z <= this->eBoundingBox.max.z)
	{
		return true;
	}

	point1 = rayIntersectPlane(origin, direction, glm::vec3(0, -1, 0), eBoundingBox.max.y);
	if (point1.x >= this->eBoundingBox.min.x &&
		point1.x <= this->eBoundingBox.max.x &&
		point1.y >= this->eBoundingBox.min.y &&
		point1.y <= this->eBoundingBox.max.y &&
		point1.z >= this->eBoundingBox.min.z &&
		point1.z <= this->eBoundingBox.max.z)
	{
		return true;
	}

	point1 = rayIntersectPlane(origin, direction, glm::vec3(-1, 0, 0), eBoundingBox.max.x);
	if (point1.x >= this->eBoundingBox.min.x &&
		point1.x <= this->eBoundingBox.max.x &&
		point1.y >= this->eBoundingBox.min.y &&
		point1.y <= this->eBoundingBox.max.y &&
		point1.z >= this->eBoundingBox.min.z &&
		point1.z <= this->eBoundingBox.max.z)
	{
		return true;
	}

	return false;
}

vec3 Entity::rayIntersectPlane(glm::vec3 origin, glm::vec3 direction, glm::vec3 planeNormal, float planeDistance)
{
	float distanceToOrigin = glm::dot(origin, planeNormal) - planeDistance;
	 return origin + direction * (-distanceToOrigin / glm::dot(direction, planeNormal));
}

void Entity::translate(glm::vec3 coord) {
   trans = coord;
}

void Entity::scale(glm::vec3 scaleV) {
   this->scaleV = scaleV;
}

void Entity::rotate(float angle, glm::vec3 axis) {
   this->angle = angle;
   this->axis = axis;
}

bool Entity::collisionCheck(Entity *entity) {

		if (collisionPointInBox(entity->eBoundingBox, glm::vec3(this->eBoundingBox.max.x, this->eBoundingBox.max.y, this->eBoundingBox.max.z)))
		{
			return true;
		}
		if (collisionPointInBox(entity->eBoundingBox, glm::vec3(this->eBoundingBox.max.x, this->eBoundingBox.max.y, this->eBoundingBox.min.z)))
		{
			return true;
		}
		if (collisionPointInBox(entity->eBoundingBox, glm::vec3(this->eBoundingBox.max.x, this->eBoundingBox.min.y, this->eBoundingBox.max.z)))
		{
			return true;
		}
		if (collisionPointInBox(entity->eBoundingBox, glm::vec3(this->eBoundingBox.max.x, this->eBoundingBox.min.y, this->eBoundingBox.min.z)))
		{
			return true;
		}
		if (collisionPointInBox(entity->eBoundingBox, glm::vec3(this->eBoundingBox.min.x, this->eBoundingBox.max.y, this->eBoundingBox.max.z)))
		{
			return true;
		}
		if (collisionPointInBox(entity->eBoundingBox, glm::vec3(this->eBoundingBox.min.x, this->eBoundingBox.max.y, this->eBoundingBox.min.z)))
		{
			return true;
		}
		if (collisionPointInBox(entity->eBoundingBox, glm::vec3(this->eBoundingBox.min.x, this->eBoundingBox.min.y, this->eBoundingBox.max.z)))
		{
			return true;
		}
		if (collisionPointInBox(entity->eBoundingBox, glm::vec3(this->eBoundingBox.min.x, this->eBoundingBox.min.y, this->eBoundingBox.min.z)))
		{
			return true;
		}

	return false;
}

bool Entity::collisionPointInBox(EBB bBox, glm::vec3 point) {
	return (point.x <= bBox.max.x && point.x >= bBox.min.x
		   && point.y <= bBox.max.y && point.y >= bBox.min.y
		   && point.z <= bBox.max.z && point.z >= bBox.min.z);
}

glm::vec3 Entity::getPos()
{
   return trans;
}

glm::vec3 Entity::getScale() {
   return scaleV;
}

float Entity::getAngle() {
   return angle;
}

glm::vec3 Entity::getAxis() {
   return axis;
}

void Entity::setTransAmt(glm::vec3 transAmt)
{
   this->transAmt = transAmt;
}

glm::vec3 Entity::getTransAmt()
{
   return transAmt;
}

void Entity::setColor(glm::vec3 color) {
   this->color = color;
}

void Entity::moveBoundingBox(vec3 oldPos)
{

	glm::vec3 moveBy = transAmt - oldPos;
	eBoundingBox.max += moveBy;
	eBoundingBox.min += moveBy;
}

void Entity::drawShadow() {
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, tex);
   glUniform1i(h_shadowModelTexture, 0);
   
   ModelTrans.loadIdentity();
   ModelTrans.pushMatrix();
   ModelTrans.translate(trans);
   ModelTrans.scale(scaleV.x, scaleV.y, scaleV.z);
   ModelTrans.rotate(angle, axis);
   glm::mat4 shadowModelMatrix = ModelTrans.modelViewMatrix;
   glm::mat4 shadowMVP = shadowProjectionMatrix * shadowViewMatrix * shadowModelMatrix;
   
   glm::mat4 bones[NUM_BONES];
   
   for (unsigned int j = 0; j < NUM_BONES; j++)
	{
		bones[j] = glm::mat4(1.0);
	}
   
   if (frames.size() > 0 && frames[0].size() > 0)
   {
      for (unsigned int i = 0; i < frames[0].size(); i++)
      {
         if (i + 1 == frames[0].size())
         {
            for (unsigned int j = 0; j < NUM_BONES; j++)
            {
               bones[j] = frames[0][i].second[j];
            }
            break;
         }
         else if (frames[0][i].first <= (anim_time + anim_offset) && frames[0][i + 1].first >= (anim_time + anim_offset))
         {
            double frame1 = ((anim_time + anim_offset) - frames[0][i].first) / (frames[0][i + 1].first - frames[0][i].first);
            double frame2 = (1.0 - frame1);
            for (unsigned int j = 0; j < NUM_BONES; j++)
            {
               bones[j] = (frames[0][i].second[j]*frame1) + (frames[0][i + 1].second[j]*frame2);
            }
            break;
         }
      }
   }
   
   anim_time += anim_step;
   if (anim_time >= 1.0)
   {
      anim_time = 0.0;
      anim_offset = 0.0;
      anim_step = 0.03;
   }
   
   glUniformMatrix4fv(h_shadowBones, NUM_BONES, GL_FALSE, (float *)bones);

   
   glUniformMatrix4fv(h_shadowMatrix, 1, GL_FALSE, glm::value_ptr(shadowMVP));
   
   //vbo
   glEnableVertexAttribArray(h_shadowModelPosition);
   glBindBuffer(GL_ARRAY_BUFFER, EntityBuffObj);
   safe_glVertexAttribPointer(h_shadowModelPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
   
   if (EntityUVBuffObj != 0) {
      safe_glEnableVertexAttribArray(h_shadowUV);
      glBindBuffer(GL_ARRAY_BUFFER, EntityUVBuffObj);
      safe_glVertexAttribPointer(h_shadowUV, 2, GL_FLOAT, GL_FALSE, 0, 0);
   }
   
   safe_glEnableVertexAttribArray(h_shadowBoneIndexs);
   glBindBuffer(GL_ARRAY_BUFFER, BoneIndexesBuffObj);
   safe_glVertexAttribPointer(h_shadowBoneIndexs, 2, GL_FLOAT, GL_FALSE, 0, 0);
   
   safe_glEnableVertexAttribArray(h_shadowBoneWeights);
   glBindBuffer(GL_ARRAY_BUFFER, BoneWeightsBuffObj);
   safe_glVertexAttribPointer(h_shadowBoneWeights, 2, GL_FLOAT, GL_FALSE, 0, 0);


   
   //ibo
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EntityIndxBuffObj);
   
   glDrawElements(GL_TRIANGLES, EntityiboLen, GL_UNSIGNED_SHORT, 0);
   
   ModelTrans.popMatrix();
   
   glDisableVertexAttribArray(h_shadowModelPosition);
}


void Entity::Update() {
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, tex);
   glUniform1i(h_modelTexture, 0);
   glUniform1f(h_skyBox, 0);

   ModelTrans.loadIdentity();
   ModelTrans.pushMatrix();
   ModelTrans.translate(trans);
   ModelTrans.scale(scaleV.x, scaleV.y, scaleV.z);
   ModelTrans.rotate(angle, axis);
   
   glm::mat4 shadowMVP = shadowProjectionMatrix * shadowViewMatrix * getModelMatrix();
   glm::mat4 shadowBiasMatrix = biasMatrix*shadowMVP;
   glm::mat4 MVP = projectionMatrix * viewMatrix * getModelMatrix();
   glm::mat3 m_inv_transp = glm::transpose(glm::inverse(glm::mat3(ModelTrans.modelViewMatrix)));
      
   glUniformMatrix4fv(h_MVP, 1, GL_FALSE, glm::value_ptr(MVP));
   glUniformMatrix3fv(h_M_inv_trans, 1, GL_FALSE, glm::value_ptr(m_inv_transp));
   glUniformMatrix4fv(h_shadowBiasMVP, 1, GL_FALSE, glm::value_ptr(shadowBiasMatrix));
   glUniformMatrix4fv(h_viewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
   glUniformMatrix4fv(h_modelMatrix, 1, GL_FALSE, glm::value_ptr(getModelMatrix()));
   glUniformMatrix4fv(h_lightPos, 1, GL_FALSE, glm::value_ptr(lightPos));
   
   glm::mat4 bones[NUM_BONES];

   for (unsigned int j = 0; j < NUM_BONES; j++)
	{
		bones[j] = glm::mat4(1.0);
	}

   if (frames.size() > 0 && frames[0].size() > 0)
   {
       for (unsigned int i = 0; i < frames[0].size(); i++)
       {
           if (i + 1 == frames[0].size())
           {
               for (unsigned int j = 0; j < NUM_BONES; j++)
               {
                   bones[j] = frames[0][i].second[j];
               }
               break;
           }
           else if (frames[0][i].first <= (anim_time + anim_offset) && frames[0][i + 1].first >= (anim_time + anim_offset))
           {
               double frame1 = ((anim_time + anim_offset) - frames[0][i].first) / (frames[0][i + 1].first - frames[0][i].first);
               double frame2 = (1.0 - frame1);
               for (unsigned int j = 0; j < NUM_BONES; j++)
               {
                   bones[j] = (frames[0][i].second[j]*frame1) + (frames[0][i + 1].second[j]*frame2);
               }
               break;
           }
       }
   }


   glUniformMatrix4fv(h_uBones, NUM_BONES, GL_FALSE, (float *)bones);

   safe_glEnableVertexAttribArray(h_aPosition);
   glBindBuffer(GL_ARRAY_BUFFER, EntityBuffObj);
   safe_glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
   
   safe_glEnableVertexAttribArray(h_aBoneIndexs);
   glBindBuffer(GL_ARRAY_BUFFER, BoneIndexesBuffObj);
   safe_glVertexAttribPointer(h_aBoneIndexs, 2, GL_FLOAT, GL_FALSE, 0, 0);
   
   safe_glEnableVertexAttribArray(h_aBoneWeights);
   glBindBuffer(GL_ARRAY_BUFFER, BoneWeightsBuffObj);
   safe_glVertexAttribPointer(h_aBoneWeights, 2, GL_FLOAT, GL_FALSE, 0, 0);
   
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EntityIndxBuffObj);
   
   safe_glEnableVertexAttribArray(h_aNormal);
   glBindBuffer(GL_ARRAY_BUFFER, EntityNormalBuffObj);
   safe_glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
   
   if (EntityUVBuffObj != 0) {
       safe_glEnableVertexAttribArray(h_aUV);
       glBindBuffer(GL_ARRAY_BUFFER, EntityUVBuffObj);
       safe_glVertexAttribPointer(h_aUV, 2, GL_FLOAT, GL_FALSE, 0, 0);
   }
   
   glUniform3f(h_uColor, color.x, color.y, color.z);
   /*if (objectVisible(AwesomeGL::getProjectionMatrix() * AwesomeGL::getViewMatrix() * AwesomeGL::getModelMatrix(), getPos().x, getPos().y, getPos().z))*/
      glDrawElements(GL_TRIANGLES, EntityiboLen, GL_UNSIGNED_SHORT, 0);
   
   ModelTrans.popMatrix();

   glDisableVertexAttribArray(h_aPosition);
   glDisableVertexAttribArray(h_aNormal);
   glDisableVertexAttribArray(h_aUV);
   glDisableVertexAttribArray(h_aBoneIndexs);
   glDisableVertexAttribArray(h_aBoneWeights);
}
