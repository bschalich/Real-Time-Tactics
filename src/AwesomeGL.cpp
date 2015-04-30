#include <map>

#include <stdint.h>

#include "AwesomeGL.h"
#include "Entity.h"

namespace AwesomeGL {
   // GLOBALS
   // Stuff
   sf::Clock *clock;
   sf::Clock *deltaClock;
   sf::Time deltaTime;
   RenderingHelper ModelTrans;
   Image *TextureImage;
   sf::Window *window;
   
   //Billboard Shader handles
   GLuint h_billboard;
   GLuint h_CameraRight;
   GLuint h_CameraUp;
   GLuint h_ViewProjMatrix;
   GLuint h_BillboardPos;
   GLuint h_BillboardSize;
   GLuint h_LifeLevel;
   GLuint h_BillboardTexture;
   GLuint h_BillboardSquareVertices;
   GLuint Texture;
   
   //ActiveHeroIcon Shader handles
   GLuint h_icon;
   GLuint h_CameraRightIcon;
   GLuint h_CameraUpIcon;
   GLuint h_ViewProjMatrixIcon;
   GLuint h_IconPos;
   GLuint h_IconSize;
   GLuint h_IconTexture;
   GLuint h_IconSquareVertices;
   GLuint IconTexture;
   
   //Shader handles
   GLuint h_shadeProg;
   GLuint h_aPosition;
   GLuint h_projectionMatrix;
   GLuint h_viewMatrix;
   GLuint h_modelMatrix;
   GLuint h_uColor;
   GLuint h_aNormal;
   GLuint h_MVP;
   GLuint h_shadowBiasMVP;
   GLuint h_shadowTexture;
   GLuint h_UV;
   GLuint h_shadowFlag;
   GLuint h_M_inv_trans;
   GLuint h_lightPos;
   GLuint h_modelTexture;
   GLuint h_aUV;
   GLuint h_aBoneIndexs;
   GLuint h_aBoneWeights;
   GLuint h_uBones;
   GLuint h_lightColor;
   GLuint h_skyBox;
   
   GLuint CubeBuffObj;
   GLuint CIndxBuffObj;
   GLuint CubeNormalBuffObj;
   GLuint TexBuffObj;
   int g_CiboLen;
   
   //Shadow Stuff
   GLuint shadow_FBO;
   GLuint shadowTexture;
   GLint shadowFlag = 0;
   
   //Shadow handles
   GLuint h_shadowProg;
   GLuint h_shadowMatrix;
   GLuint h_shadowModelPosition;
   GLuint h_texture;
   GLuint h_shadowModelTexture;
   GLuint h_shadowUV;
   GLuint h_shadowBoneWeights;
   GLuint h_shadowBoneIndexs;
   GLuint h_shadowBones;
   
   //Font shader
   GLuint h_FontProg;
   GLuint h_coord;
   GLuint h_tex;
   GLuint h_color;
   
   //Particle shader
   GLuint h_particleProg;
   GLuint h_particleTex;
   GLuint h_viewProjMatrix;
   GLuint h_cameraUp_worldspace;
   GLuint h_cameraRight_worldspace;
   GLuint h_squareVertices;
   GLuint h_xyzs;
   GLuint h_particleColor;
   
   //Bloom shader
   GLuint bloom_FBO;
   GLuint bloomTexture;
   GLuint depthBuffer;
   
   Camera *camera;
   OBB boundingBox;
   int score;
   std::random_device rd;
   std::mt19937 mt;
   
   std::vector<ParticleEmitter*> particleList;
   std::vector<Entity*> entityList;
   std::vector<Entity*> tileList;
   std::vector<Combatant*> cList;
   std::vector<Combatant*> heroList;
   std::vector<Combatant*> enemyList;
   std::vector<Combatant*> projectileList;
   std::vector<Tween*> tweenList;
   std::vector<Billboard*> billboardList;
   std::vector<ActiveHeroIcon*> ahIconList;
   
   sf::Clock *colorTimer;
   
   glm::vec3 tilePos;
   
   Model model_warrior;
   Model model_grid;
   Model model_tile;
   Model model_tree3;
   Model model_treeR;
   Model model_ranged;
   Model model_caster;
   Model model_arrow;
   Model model_stone;
   Model model_flower;
   Model model_grass;
   
   Combatant *activeHero;
   unsigned int activeHeroIndex;
   glm::vec3 lightDir = glm::vec3(1, 1, 1);
   
   
   GameMap *map;
   
   std::unordered_map<std::string, GLuint*> texMap;
   std::unordered_map<std::string, Model> modelMap;
   
   GLuint tex_warrior;
   GLuint tex_grid;
   GLuint tex_yellow;
   GLuint tex_stone;
   GLuint tex_ranged;
   GLuint tex_caster;
   GLuint tex_arrow;
   GLuint tex_skybox;
   GLuint tex_tree3;
   GLuint tex_redwood;
   GLuint tex_flower;
   GLuint tex_grass;
   GLuint tex_star;

   GLuint tex_warriorHUD;
   
   sf::SoundBuffer tauntSoundBuffer;
   
   sf::SoundBuffer deathSoundBuffer;
   sf::SoundBuffer startSound;
   sf::SoundBuffer endSound;
   
   sf::Sound start;
   sf::Sound arrowHitSound;
   sf::Sound deathSound;
   sf::Sound tauntSound;
   
   sf::SoundBuffer bgSoundBuffer;
   sf::Sound bgSound;
   sf::SoundBuffer music;
   sf::Sound musicSound;
   sf::Sound endMusic;
   
   int shadowSize = 2048;
   float shadowFrustum = 500;
   bool renderShadowFlag = true;
   glm::mat4 shadowProjectionMatrix;
   glm::mat4 shadowViewMatrix;
   
   glm::mat4 biasMatrix(
                        0.5, 0.0, 0.0, 0.0,
                        0.0, 0.5, 0.0, 0.0,
                        0.0, 0.0, 0.5, 0.0,
                        0.5, 0.5, 0.5, 1.0
                        );
   
   
   glm::mat4 projectionMatrix;
   glm::mat4 viewMatrix;
   
   float lightSpeed = 0.05;
   float lightX = 650;
   glm::vec3 lightPos(lightX, 0, 150);
   glm::vec3 lightColor(1, 1, 1);
   glm::vec3 zoomFactor = glm::vec3(10, 10, 10);
   glm::vec3 cameraPos = glm::vec3(0, 0, 0);
   
   GLuint fontVBO;
   FT_Face arialFace;
   FT_Face oldLondonFace;
   FT_Face swordsmanFace;
   FT_Face erinFace;
   Font *arial32;
   Font *arial48;
   Font *arial96;
   Font *arial250;
   Font *oldLondon32;
   Font *swordsman32;
   Font *erin32;
   Font *erin250;
   
   glm::mat4 getProjectionMatrix() {
      return glm::ortho(-1000.f, 1000.f, -1000.f, 1000.f, -10000.f, 4000.f) * glm::translate(glm::mat4(), cameraPos) * glm::scale(glm::mat4(), zoomFactor);
      //return glm::perspective(45.f, ratio, 0.1f, 1000.f);
   }
   
   bool objectVisible(glm::mat4 MVPMatrix, float xPos, float yPos, float zPos)
   {
      enum term { A = 0, B, C, D };
      
      GLfloat leftPlane[4];
      leftPlane[A] = MVPMatrix[3][0]  + MVPMatrix[0][0];
      leftPlane[B] = MVPMatrix[3][1]  + MVPMatrix[0][1];
      leftPlane[C] = MVPMatrix[3][2] + MVPMatrix[0][2];
      leftPlane[D] = MVPMatrix[3][3] + MVPMatrix[0][3];
      
      GLfloat length = sqrtf(leftPlane[A] * leftPlane[A] + leftPlane[B] * leftPlane[B] + leftPlane[C] * leftPlane[C]);
      leftPlane[A] /= length;
      leftPlane[B] /= length;
      leftPlane[C] /= length;
      leftPlane[D] /= length;
      
      GLfloat distance = leftPlane[A] * xPos + leftPlane[B] * yPos + leftPlane[C] * zPos + leftPlane[D];
      printf("left distance: %.2f\n", distance);
      if (distance <= 0)
      {
         return false;
      }
      
      GLfloat rightPlane[4];
      rightPlane[A] = MVPMatrix[3][0]  - MVPMatrix[0][0];
      rightPlane[B] = MVPMatrix[3][1]  - MVPMatrix[0][1];
      rightPlane[C] = MVPMatrix[3][2] - MVPMatrix[0][2];
      rightPlane[D] = MVPMatrix[3][3] - MVPMatrix[0][3];
      
      length = sqrtf(rightPlane[A] * rightPlane[A] + rightPlane[B] * rightPlane[B] + rightPlane[C] * rightPlane[C]);
      rightPlane[A] /= length;
      rightPlane[B] /= length;
      rightPlane[C] /= length;
      rightPlane[D] /= length;
      
      distance = rightPlane[A] * xPos + rightPlane[B] * yPos + rightPlane[C] * zPos + rightPlane[D];
      printf("right distance: %.2f\n", distance);
      if (distance <= 0)
      {
         return false;
      }
      
      GLfloat bottomPlane[4];
      
      bottomPlane[A] = MVPMatrix[3][0] + MVPMatrix[1][0];
      bottomPlane[B] = MVPMatrix[3][1] + MVPMatrix[1][1];
      bottomPlane[C] = MVPMatrix[3][2] + MVPMatrix[1][2];
      bottomPlane[D] = MVPMatrix[3][3] + MVPMatrix[1][3];
      
      length = sqrtf(bottomPlane[A] * bottomPlane[A] + bottomPlane[B] * bottomPlane[B] + bottomPlane[C] * bottomPlane[C]);
      bottomPlane[A] /= length;
      bottomPlane[B] /= length;
      bottomPlane[C] /= length;
      bottomPlane[D] /= length;
      
      distance = bottomPlane[A] * xPos + bottomPlane[B] * yPos + bottomPlane[C] * zPos + bottomPlane[D];
      if (distance <= 0)
      {
         return false;
      }
      
      GLfloat topPlane[4];
      topPlane[A] = MVPMatrix[3][0] - MVPMatrix[1][0];
      topPlane[B] = MVPMatrix[3][1] - MVPMatrix[1][1];
      topPlane[C] = MVPMatrix[3][2] - MVPMatrix[1][2];
      topPlane[D] = MVPMatrix[3][3] - MVPMatrix[1][3];
      
      length = sqrtf(topPlane[A] * topPlane[A] + topPlane[B] * topPlane[B] + topPlane[C] * topPlane[C]);
      topPlane[A] /= length;
      topPlane[B] /= length;
      topPlane[C] /= length;
      topPlane[D] /= length;
      
      distance = topPlane[A] * xPos + topPlane[B] * yPos + topPlane[C] * zPos + topPlane[D];
      if (distance <= 0)
      {
         return false;
      }
      
      GLfloat nearPlane[4];
   
      nearPlane[A] = MVPMatrix[3][0] + MVPMatrix[2][0];
      nearPlane[B] = MVPMatrix[3][1] + MVPMatrix[2][1];
      nearPlane[C] = MVPMatrix[3][2] + MVPMatrix[2][2];
      nearPlane[D] = MVPMatrix[3][3] + MVPMatrix[2][3];
      
      length = sqrtf(nearPlane[A] * nearPlane[A] + nearPlane[B] * nearPlane[B] + nearPlane[C] * nearPlane[C]);
      nearPlane[A] /= length;
      nearPlane[B] /= length;
      nearPlane[C] /= length;
      nearPlane[D] /= length;
      
      distance = nearPlane[A] * xPos + nearPlane[B] * yPos + nearPlane[C] * zPos + nearPlane[D];
      if (distance <= 0)
      {
         return false;
      }
      
      GLfloat farPlane[4];
      farPlane[A] = MVPMatrix[3][0] - MVPMatrix[2][0];
      farPlane[B] = MVPMatrix[3][1] - MVPMatrix[2][1];
      farPlane[C] = MVPMatrix[3][2] - MVPMatrix[2][2];
      farPlane[D] = MVPMatrix[3][3] - MVPMatrix[2][3];
      
      length = sqrtf(farPlane[A] * farPlane[A] + farPlane[B] * farPlane[B] + farPlane[C] * farPlane[C]);
      farPlane[A] /= length;
      farPlane[B] /= length;
      farPlane[C] /= length;
      farPlane[D] /= length;
      
      distance = farPlane[A] * xPos + farPlane[B] * yPos + farPlane[C] * zPos + farPlane[D];
      if (distance <= 0)
      {
         return false;
      }
      
      return true;
   }
   
   glm::mat4 getViewMatrix() {
      //glm::vec3(50, 50, 50);
      return glm::lookAt(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
   }
   
   glm::mat4 getModelMatrix() {
      return ModelTrans.modelViewMatrix;
   }
   
   
   glm::mat4 getShadowProjectionMatrix() {
      return glm::ortho<float>(-shadowFrustum, shadowFrustum, -shadowFrustum, shadowFrustum, -shadowFrustum, shadowFrustum*1.8f);
   }
   
   glm::mat4 getShadowViewMatrix() {
      return glm::lookAt(lightPos, glm::vec3(7.5*TILE_SIZE,0,7.5*TILE_SIZE), glm::vec3(0,1,0));
   }
   
   void renderShadows() {
      shadowProjectionMatrix = getShadowProjectionMatrix();
      shadowViewMatrix = getShadowViewMatrix();
      glBindFramebuffer(GL_FRAMEBUFFER, shadow_FBO);
      glViewport(0,0,shadowSize,shadowSize); //shadow resolution
                                             //glEnable(GL_CULL_FACE);
      glCullFace(GL_FRONT);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      glUseProgram(h_shadowProg);
      
      for (unsigned int i = 0; i < entityList.size(); i++) {
         entityList[i]->drawShadow();
      }
      glUseProgram(0);
      
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glViewport(0,0,window->getSize().x ,window->getSize().y);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   }
   
   void renderModels() {
      glUseProgram(h_shadeProg);
      
      glUniform1i(h_skyBox, 0);
      glUniform1i(h_shadowFlag, shadowFlag);
      
      projectionMatrix = getProjectionMatrix();
      viewMatrix = getViewMatrix();
      
      glUniform3f(h_lightColor, lightColor.x, lightColor.y, lightColor.z);
      glUniform3f(h_lightPos, lightPos.x, lightPos.y, lightPos.z);
      
      //glEnable(GL_CULL_FACE);
      glCullFace(GL_BACK);
      for (unsigned int i = 0; i < entityList.size(); i++) {
         entityList[i]->Update();
      }
      
      glDisable(GL_CULL_FACE);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, tex_grid);
      glUniform1i(h_modelTexture, 0);
      for (unsigned int i = 0; i < tileList.size(); i++) {
         tileList[i]->Update();
         
         if (colorTimer->getElapsedTime().asSeconds() > 0.5) {
            tileList[i]->setColor(glm::vec3(0.1f, 0.7f, 0.3f));
         }
      }
      
      glActiveTexture(GL_TEXTURE1);
      glBindTexture(GL_TEXTURE_2D, shadowTexture);
      glUniform1i(h_shadowTexture, 1);
      
      glUseProgram(0);
   }
   
   void renderParticles() {
      glUseProgram(h_particleProg);
      for (unsigned int i = 0; i < particleList.size(); i++) {
         particleList[i]->Update();
      }
      glUseProgram(0);
   }
   
   void drawSkyBox() {
      glDisable(GL_DEPTH_TEST);
      glDisable(GL_CULL_FACE);
      glUseProgram(h_shadeProg);
      glUniform1i(h_skyBox, 1);
      
      ModelTrans.loadIdentity();
      ModelTrans.pushMatrix();
      ModelTrans.scale(10, 10, 10);
      ModelTrans.rotate(45, glm::vec3(0, 1, 0));
      ModelTrans.translate(glm::vec3(0*10, 0, 0*10));
      projectionMatrix = getProjectionMatrix();
      viewMatrix = getViewMatrix();
      
      glUniform3f(h_lightColor, lightColor.x, lightColor.y, lightColor.z);
      glUniform3f(h_lightPos, lightPos.x, lightPos.y, lightPos.z);
      
      glm::mat4 shadowMVP = shadowProjectionMatrix * shadowViewMatrix * getModelMatrix();
      glm::mat4 ModelMatrix = ModelTrans.modelViewMatrix;
      glm::mat4 MVP = projectionMatrix * viewMatrix * ModelMatrix;
      glm::mat4 depthBiasMVP = biasMatrix*shadowMVP;
      glm::mat3 m_inv_transp = glm::transpose(glm::inverse(glm::mat3(ModelMatrix)));
      
      glUniformMatrix3fv(h_M_inv_trans, 1, GL_FALSE, glm::value_ptr(m_inv_transp));
      glUniformMatrix4fv(h_MVP, 1, GL_FALSE, glm::value_ptr(MVP));
      glUniformMatrix4fv(h_shadowBiasMVP, 1, GL_FALSE, glm::value_ptr(depthBiasMVP));
      glUniformMatrix4fv(h_modelMatrix, 1, GL_FALSE, glm::value_ptr(ModelMatrix));
      glUniformMatrix4fv(h_viewMatrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
      
      safe_glEnableVertexAttribArray(h_aPosition);
      glBindBuffer(GL_ARRAY_BUFFER, CubeBuffObj);
      safe_glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
      
       safe_glEnableVertexAttribArray(h_aNormal);
       glBindBuffer(GL_ARRAY_BUFFER, CubeNormalBuffObj);
       safe_glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
       
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, tex_skybox);
      safe_glUniform1i(h_modelTexture, 0);
      
      safe_glEnableVertexAttribArray(h_UV);
      glBindBuffer(GL_ARRAY_BUFFER, TexBuffObj);
      safe_glVertexAttribPointer(h_UV, 2, GL_FLOAT, GL_FALSE, 0, 0);
      
      glUniform3f(h_uColor, 1.0, 1.0, 1.0);
      
      //glDrawArrays(GL_QUADS, 0, 6*4);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CIndxBuffObj);
      glDrawElements(GL_TRIANGLES, g_CiboLen, GL_UNSIGNED_SHORT, 0);
      ModelTrans.popMatrix();
      
      glDisableVertexAttribArray(h_aPosition);
      glDisableVertexAttribArray(h_aNormal);
      glDisableVertexAttribArray(h_UV);
      glUseProgram(0);
      glEnable(GL_DEPTH_TEST);
   }

   void dayNnite() {
      static bool lightSpeedSet = true;
      static float lightSpeedMod = 0;
      
      lightPos.x += lightSpeed * lightDir.x;
      lightPos.y += lightSpeed * lightDir.y;
      
      if (lightPos.y < -50) {
         renderShadowFlag = false;
      }
      else {
         renderShadowFlag = true;
      }
      
      if (lightPos.y < -20 && !lightSpeedSet) {
         lightSpeed = 0.9;
      }
      else if (!lightSpeedSet){
         lightSpeed = 0.05;
      }
      
      if (lightPos.y < 35 && lightPos.y > -45) {
         if (lightDir.y == -1) {
            if (lightColor.y > 0.4) {
               lightColor.x -= 0.0005 + lightSpeedMod;
               lightColor.y -= 0.001 + lightSpeedMod;
               lightColor.z -= 0.001 + lightSpeedMod;
            }
            else {
               lightColor.x -= 0.001;
               lightColor -= 0.001 + lightSpeedMod;
            }
            if (lightColor.x < 0.05) {
               lightColor = vec3(0.05, 0.05, 0.05);
            }
         }
         if (lightDir.y == 1) {
            if (lightColor.x < 0.6) {
               lightColor.x += 0.0012 + lightSpeedMod;
               lightColor.y += 0.0005 + lightSpeedMod;
               lightColor.z += 0.0005 + lightSpeedMod;
            }
            else {
               lightColor.y += 0.004;
               lightColor.z += 0.004;
               lightColor.x += 0.0025;
            }
            if (lightColor.y > 0.9) {
               lightColor = vec3(1, 0.9, 0.90);
            }
         }
      }
      
      if (lightPos.x >= lightX && lightPos.x <= lightX+lightSpeed) {
         lightDir.x = -1;
      }
      else if (lightPos.x <= -lightX && lightPos.x <= lightX+lightSpeed) {
         lightDir.x = 1;
      }
      
      if (lightPos.y >= lightX && lightPos.y <= lightX+lightSpeed) {
         lightDir.y = -1;
      }
      else if (lightPos.y <= -lightX && lightPos.y <= -lightX+lightSpeed) {
         lightDir.y = 1;
      }
   }
   
   void Update() {
      //render shadows
      renderShadows();
     
#ifdef __APPLE__ 
      //draw skybox
      drawSkyBox();
#endif

      //render models
      renderModels();
      
      renderParticles();
      
      dayNnite();

	  //renderHUD();
   }

   void renderHUD()
   {
	/*   glGenBuffers(1, &billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
   */

	   glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		gluOrtho2D(0.0f, window->getSize().x, window->getSize().y, 0.0f);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.375, 0.375, 0.0);

		glDisable(GL_DEPTH_TEST);
		/*glUseProgram(h_shadeProg);
        glUniform1i(h_skyBox, 1);

		glColor3f(0.0,0.0,1.0);
		glBegin(GL_QUADS);
			glVertex2f(50,50);
			glVertex2f(50,100);
			glVertex2f(100,100);
			glVertex2f(100,50);
		glEnd();

		safe_glEnableVertexAttribArray(h_aPosition);
      glBindBuffer(GL_ARRAY_BUFFER, CubeBuffObj);
      safe_glVertexAttribPointer(h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
      
       safe_glEnableVertexAttribArray(h_aNormal);
       glBindBuffer(GL_ARRAY_BUFFER, CubeNormalBuffObj);
       safe_glVertexAttribPointer(h_aNormal, 3, GL_FLOAT, GL_FALSE, 0, 0);
       
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, tex_warriorHUD);
      safe_glUniform1i(h_modelTexture, 0);
      
      safe_glEnableVertexAttribArray(h_UV);
      glBindBuffer(GL_ARRAY_BUFFER, TexBuffObj);
      safe_glVertexAttribPointer(h_UV, 2, GL_FLOAT, GL_FALSE, 0, 0);
      
      glUniform3f(h_uColor, 1.0, 1.0, 1.0);
      
      //glDrawArrays(GL_QUADS, 0, 6*4);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CIndxBuffObj);
      glDrawElements(GL_TRIANGLES, g_CiboLen, GL_UNSIGNED_SHORT, 0);
      //ModelTrans.popMatrix();
      
      glDisableVertexAttribArray(h_aPosition);
      glDisableVertexAttribArray(h_aNormal);
      glDisableVertexAttribArray(h_UV); */
		glm::mat4 ViewMatrix = AwesomeGL::getViewMatrix();
   glm::mat4 ProjectionMatrix = AwesomeGL::getProjectionMatrix();
   
   glm::vec3 CameraPosition(glm::inverse(ViewMatrix)[3]);
   
   glm::mat4 ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
		glUseProgram(h_billboard);
   
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, tex_warriorHUD);
   glUniform1i(h_BillboardTexture, 0);
   
   glUniform3f(h_CameraRight, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
   glUniform3f(h_CameraUp, ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
   
   //glUniform3f(h_BillboardPos, entity->getPos().x, entity->getPos().y + 30.0f, entity->getPos().z);
   
   //glUniform2f(h_BillboardSize, thisHealth * .25f, 0.125f);
   
   /*float LifeLevel = 0;
   glUniform1f(h_LifeLevel, LifeLevel);*/
   
   glUniformMatrix4fv(h_ViewProjMatrix, 1, GL_FALSE, &ViewProjectionMatrix[0][0]);
   
   
   glEnableVertexAttribArray(h_BillboardSquareVertices);
   //glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
   glVertexAttribPointer(h_BillboardSquareVertices, 3, GL_FLOAT, GL_FALSE, 0,(void*)0);
   
   glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
   glUseProgram(0);
   glDisableVertexAttribArray(h_BillboardSquareVertices);


      glUseProgram(0); 

		//glDepthFunc(GL_LEQUAL);
		glEnable(GL_DEPTH_TEST);
   }
   
   void addBillboard(Billboard *billboard)
   {
      billboardList.push_back(billboard);
   }
   
   void removeBillboard(Billboard *billboard)
   {
      //printf("Remove Billboard\n");
      for (unsigned int i = 0; i < billboardList.size(); i++)
      {
         if (billboardList[i] == billboard)
         {
            billboardList.erase(billboardList.begin() + i);
            break;
         }
      }
   }
   
   void removeHero(Combatant* hero) {
      for (unsigned int i = 0; i < heroList.size(); i++)
      {
         if (heroList[i] == hero)
         {
            heroList.erase(heroList.begin() + i);
            break;
         }
      }
   }
   
   void addAHIcon(ActiveHeroIcon *ahIcon)
   {
      ahIconList.push_back(ahIcon);
   }
   
   void removeAHIcon(ActiveHeroIcon *ahIcon)
   {
      for (unsigned int i = 0; i < ahIconList.size(); i++)
      {
         if (ahIconList[i] == ahIcon)
         {
            ahIconList.erase(ahIconList.begin() + i);
            break;
         }
      }
   }
   
   void addTween(Tween *tween)
   {
      tweenList.push_back(tween);
   }
   
   void removeTween(Tween *tween) {
      for (unsigned int i = 0; i < tweenList.size(); i++) {
         if (tweenList[i] == tween) {
            tweenList.erase(tweenList.begin() + i);
            break;
         }
      }
   }
   
   void removeTile(Entity* entity) {
      for (unsigned int i = 0; i < tileList.size(); i++) {
         if (tileList[i] == entity) {
            tileList.erase(tileList.begin() + i);
            break;
         }
      }
   }
   
   void addTile(Entity* entity) {
      tileList.push_back(entity);
   }
   
   void addEntity(Entity* entity) {
      entityList.push_back(entity);
   }
   
   void addParticle(ParticleEmitter* p) {
      particleList.push_back(p);
   }
   
   void removeParticle(ParticleEmitter* p) {
      for (unsigned int i = 0; i < particleList.size(); i++) {
         if (particleList[i] == p) {
            particleList.erase(particleList.begin() + i);
            break;
         }
      }
   }
   
   void removeEntity(Entity* entity) {
      for (unsigned int i = 0; i < entityList.size(); i++) {
         if (entityList[i] == entity) {
            entityList.erase(entityList.begin() + i);
            break;
         }
      }
   }
   
   void addCombatant(Combatant *combatant)
   {
      cList.push_back(combatant);
   }
   
   void removeCombatant(Combatant *combatant)
   {
      for (unsigned int i = 0; i < cList.size(); i++)
      {  //std::cout << cList[i] << std::endl;
         if (cList[i] == combatant)
         {
            cList.erase(cList.begin() + i);
            break;
         }
      }
   }
   
   void removeEnemy(Combatant *enemy)
   {
      for (unsigned int i = 0; i < cList.size(); i++)
      {  //std::cout << cList[i] << std::endl;
         //printf("D\n");
         if (enemyList[i] == enemy)
         {
            enemyList.erase(enemyList.begin() + i);
            break;
         }
      }
   }
   
   point mkPt(float arg0, float arg1, float arg2, float arg3)
   {
      point p = { arg0, arg1, arg2, arg3 };
      return p;
   }
   
   void renderText(const char *text, Font *a, float x, float y, float sx, float sy) {
      const uint8_t *p;
      
      glDisable(GL_CULL_FACE);
      
      /* Use the texture containing the atlas */
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, a->tex);
      glUniform1i(h_tex, 0);
      
      /* Set up the VBO for our vertex data */
      glEnableVertexAttribArray(h_coord);
      glBindBuffer(GL_ARRAY_BUFFER, fontVBO);
      glVertexAttribPointer(h_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
      
      point *coords = new point[6 * strlen(text)];
      int c = 0;
      
      /* Loop through all characters */
      for (p = (const uint8_t *)text; *p; p++) {
         /* Calculate the vertex and texture coordinates */
         float x2 = x + a->c[*p].bl * sx;
         float y2 = -y - a->c[*p].bt * sy;
         float w = a->c[*p].bw * sx;
         float h = a->c[*p].bh * sy;
         
         /* Advance the cursor to the start of the next character */
         x += a->c[*p].ax * sx;
         y += a->c[*p].ay * sy;
         
         /* Skip glyphs that have no pixels */
         if (!w || !h)
            continue;
         
         coords[c++] = mkPt(
                            x2, -y2, a->c[*p].tx, a->c[*p].ty);
         coords[c++] = mkPt(
                            x2 + w, -y2, a->c[*p].tx + a->c[*p].bw / a->w, a->c[*p].ty);
         coords[c++] = mkPt(
                            x2, -y2 - h, a->c[*p].tx, a->c[*p].ty + a->c[*p].bh / a->h);
         coords[c++] = mkPt(
                            x2 + w, -y2, a->c[*p].tx + a->c[*p].bw / a->w, a->c[*p].ty);
         coords[c++] = mkPt(
                            x2, -y2 - h, a->c[*p].tx, a->c[*p].ty + a->c[*p].bh / a->h);
         coords[c++] = mkPt(
                            x2 + w, -y2 - h, a->c[*p].tx + a->c[*p].bw / a->w, a->c[*p].ty + a->c[*p].bh / a->h);
      }
      
      /* Draw all the character on the screen in one go */
      glBufferData(GL_ARRAY_BUFFER, sizeof(point) * 6 * strlen(text), coords, GL_DYNAMIC_DRAW);
      glDrawArrays(GL_TRIANGLES, 0, c);
      
      delete coords;
      
      glDisableVertexAttribArray(h_coord);
   }
   
   void setWin() {
      /*glUseProgram(h_FontProg);
       
       GLfloat white[4] = {1, 1, 1, 1};
       glUniform4fv(h_color, 1, white);
       float sx = 2.0f / window->getSize().x;
       float sy = 2.0f / window->getSize().y;
       char buf[2 * 32];
       sprintf(buf, "You Win!");
       
       FT_Set_Pixel_Sizes(arial.face, 0, 100);
       
       AwesomeGL::renderText(buf,
       -1 + (window->getSize().x - 900) * sx,   1 - 150 * sy, sx, sy, &arial);
       glDisable(h_FontProg);*/
   }
   
   void cleanUp() {
      glDeleteProgram(h_shadeProg);
      glDeleteProgram(h_shadowProg);
      glDeleteProgram(h_FontProg);
      glDeleteFramebuffers(1, &shadow_FBO);
      glDeleteTextures(1, &shadowTexture);
   }
   
   
   
   bool initShadowFBO() {
      shadow_FBO = 0;
      glGenFramebuffers(1, &shadow_FBO);
      glBindFramebuffer(GL_FRAMEBUFFER, shadow_FBO);
      
      glGenTextures(1, &shadowTexture);
      glBindTexture(GL_TEXTURE_2D, shadowTexture);
      glTexImage2D(GL_TEXTURE_2D, 0,GL_DEPTH_COMPONENT16, shadowSize, shadowSize, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
      
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTexture, 0);
      
      glDrawBuffer(GL_NONE);
      glReadBuffer(GL_NONE);
      
      if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
         return false;
      return true;
   }
   
   bool initBloomFBO() {
      bloom_FBO = 0;
      glGenFramebuffers(1, &bloom_FBO);
      glBindFramebuffer(GL_FRAMEBUFFER, bloom_FBO);
      
      glGenTextures(1, &bloomTexture);
      glBindTexture(GL_TEXTURE_2D, bloomTexture);
      glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA8, window->getSize().x, window->getSize().y, 0,GL_RGBA, GL_UNSIGNED_BYTE, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
      //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
      
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bloomTexture, 0);
      
      
      glGenRenderbuffers(1, &depthBuffer);
      glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_ATTACHMENT, window->getSize().x, window->getSize().y);
      
      if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
         return false;
      return true;
   }
   
   bool initGL() {
	   FT_Library freetypeLib;
      
      if (FT_Init_FreeType(&freetypeLib)) {
         fprintf(stderr, "Error initializing FreeType 2");
      }
      int error = FT_New_Face(freetypeLib, "Fonts/ArialBold.ttf", 0, &arialFace);
      if (error == FT_Err_Unknown_File_Format) {
         fprintf(stderr, "Unsupported font format");
      }
      else if (error) {
         fprintf(stderr, "Font file ArialBold.ttf coult not be opened or read\n");
      }
      
      error = FT_New_Face(freetypeLib, "Fonts/OldLondon.ttf", 0, &oldLondonFace);
      if (error == FT_Err_Unknown_File_Format) {
         fprintf(stderr, "Unsupported font format");
      }
      else if (error) {
         fprintf(stderr, "Font file OldLondon.ttf coult not be opened or read\n");
      }
      
      error = FT_New_Face(freetypeLib, "Fonts/SEVESBRG.ttf", 0, &swordsmanFace);
      if (error == FT_Err_Unknown_File_Format) {
         fprintf(stderr, "Unsupported font format");
      }
      else if (error) {
         fprintf(stderr, "Font file SEVESBRG.ttf coult not be opened or read\n");
      }
      
      error = FT_New_Face(freetypeLib, "Fonts/eringobragh.ttf", 0, &erinFace);
      if (error == FT_Err_Unknown_File_Format) {
         fprintf(stderr, "Unsupported font format");
      }
      else if (error) {
         fprintf(stderr, "Font file eringobragh.ttf coult not be opened or read\n");
      }
      
      glGenBuffers(1, &fontVBO);
      
      arial32 = new Font(arialFace, 32);
      arial48 = new Font(arialFace, 48);
      arial96 = new Font(arialFace, 96);
      arial250 = new Font(arialFace, 250);
      //oldLondon32 = new Font(oldLondonFace, 32);
      //swordsman32 = new Font(swordsmanFace, 32);
      erin32 = new Font(erinFace, 32);
      erin250 = new Font(erinFace, 250);
      
      //-----------------------------------------
      
      // Set the color and depth clear values
      //glClearDepth(1.f);
      glClearColor (0.0, 0.0, 0.0, 0.0f); //0.5f, 0.7f, 0.9f, 1.0f
   	glEnable(GL_CULL_FACE);
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LESS);
      
      //FOR FONTS, ENABLES ALPHA CHANNELS
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      //glDepthMask(GL_TRUE);
      
      ModelTrans.useModelViewMatrix();
      ModelTrans.loadIdentity();
      
      if (!initShadowFBO()) {
         fprintf(stderr, "Error initializing shadow FBO\n");
         return false;
      }
      
      /*if (!initBloomFBO()) {
         fprintf(stderr, "Error initializing bloom FBO\n");
         return false;
      }*/

      
      if (!setUpShaders()) {
         fprintf(stderr, "Error initializing shaders\n");
         return false;
      }
      
      //initCube();
      initGround();
      setUpTextures();
      setUpModels();
      
      return true;
   }
   
   void setUpTextures() {
      glGenTextures(1, &tex_grid);
      loadTexture_BMP((char *) "Models/grid.bmp", tex_grid);
      
      glGenTextures(1, &tex_yellow);
      loadTexture_BMP((char *) "Models/yellow.bmp", tex_yellow);

	  glGenTextures(1, &tex_stone);
      loadTexture_BMP((char *) "Models/stone_texture.bmp", tex_stone);
      
      glGenTextures(1, &tex_warrior);
      loadTexture_BMP((char *) "Models/Warrior.bmp", tex_warrior);
      
      glGenTextures(1, &tex_ranged);
      loadTexture_BMP((char *) "Models/Ranged.bmp", tex_ranged);
      
      glGenTextures(1, &tex_caster);
      loadTexture_BMP((char *) "Models/Caster.bmp", tex_caster);
      
      glGenTextures(1, &tex_arrow);
      loadTexture_BMP((char *) "Models/Arrow.bmp", tex_arrow);
      
      glGenTextures(1, &tex_skybox);
	  loadTexture_BMP((char *) "Models/clouds.bmp", tex_skybox);

	  glGenTextures(1, &tex_warriorHUD);
      loadTexture_BMP((char *) "UI/knighthead.bmp", tex_warriorHUD);

	  glGenTextures(1, &tex_stone);
	  loadTexture_BMP((char *) "Models/stone_texture.bmp", tex_stone);

	  glGenTextures(1, &tex_flower);
	  loadTexture_BMP((char *) "Models/flower.bmp", tex_flower);

	  glGenTextures(1, &tex_grass);
	  loadTexture_BMP((char *) "Models/grass.bmp", tex_grass);
     
#ifndef _WIN32
      int width, height; 
      tex_tree3 = loadTexture_PNG("Models/Branch_3.png", width, height);
      texMap.insert(std::make_pair("Tree3", &tex_tree3));

#else
      texMap.insert(std::make_pair("Tree3", &tex_yellow));
#endif
      
      glGenTextures(1, &tex_star);
      tex_star = loadTexture_PNG("Models/star.png", width, height);
	  

      texMap.insert(std::make_pair("Models/grid.bmp", &tex_grid));
      texMap.insert(std::make_pair("Models/yellow.bmp", &tex_yellow));
	  texMap.insert(std::make_pair("Models/stone_texture.bmp", &tex_stone));
      texMap.insert(std::make_pair("Models/Warrior.bmp", &tex_warrior));
      texMap.insert(std::make_pair("Models/Ranged.bmp", &tex_ranged));
      texMap.insert(std::make_pair("Models/Caster.bmp", &tex_caster));
      texMap.insert(std::make_pair("Models/Arrow.bmp", &tex_arrow));
      //texMap.insert(std::make_pair("Models/Temperate_grass.png", &tex_temperate_grass));
      texMap.insert(std::make_pair("Models/SubTrop_Redwood.png", &tex_redwood));
	  texMap.insert(std::make_pair("Models/flower.bmp", &tex_flower));
	  texMap.insert(std::make_pair("Models/grass.bmp", &tex_grass));
      texMap.insert(std::make_pair("Models/star.png", &tex_star));

   }
   
   void setUpModels() {
      model_warrior.modelNumVert = AwesomeGL::loadSingleMesh("Models/Warrior.dae", model_warrior.modelVert, model_warrior.modelIndex, model_warrior.modelNormal, model_warrior.modelUV, model_warrior.modelBoneIndex, model_warrior.modelBoneWeight, model_warrior.frames);
      modelMap.insert(std::make_pair("Models/Warrior.dae", model_warrior));
      
      model_tile.modelNumVert = AwesomeGL::loadSingleMesh("Models/Tile.dae", model_tile.modelVert, model_tile.modelIndex, model_tile.modelNormal, model_tile.modelUV, model_tile.modelBoneIndex, model_tile.modelBoneWeight, model_tile.frames);
      modelMap.insert(std::make_pair("Models/Tile.dae", model_tile));
      
      model_tree3.modelNumVert = AwesomeGL::loadSingleMesh("Models/Tree_3.obj", model_tree3.modelVert, model_tree3.modelIndex, model_tree3.modelNormal, model_tree3.modelUV, model_tree3.modelBoneIndex, model_tree3.modelBoneWeight, model_tree3.frames);
      modelMap.insert(std::make_pair("Models/Tree_3.obj", model_tree3));
      
      model_treeR.modelNumVert = AwesomeGL::loadSingleMesh("Models/Prop_Redwood1.obj", model_treeR.modelVert, model_treeR.modelIndex, model_treeR.modelNormal, model_treeR.modelUV, model_treeR.modelBoneIndex, model_treeR.modelBoneWeight, model_treeR.frames);
      modelMap.insert(std::make_pair("Models/Prop_Redwood1.obj", model_treeR));
      
      model_ranged.modelNumVert = AwesomeGL::loadSingleMesh("Models/Ranged.dae", model_ranged.modelVert, model_ranged.modelIndex, model_ranged.modelNormal, model_ranged.modelUV, model_ranged.modelBoneIndex, model_ranged.modelBoneWeight, model_ranged.frames);
      modelMap.insert(std::make_pair("Models/Ranged.dae", model_ranged));
      
      model_caster.modelNumVert = AwesomeGL::loadSingleMesh("Models/Caster.dae", model_caster.modelVert, model_caster.modelIndex, model_caster.modelNormal, model_caster.modelUV, model_caster.modelBoneIndex, model_caster.modelBoneWeight, model_caster.frames);
      modelMap.insert(std::make_pair("Models/Caster.dae", model_caster));
      
      model_arrow.modelNumVert = AwesomeGL::loadSingleMesh("Models/Arrow.obj", model_arrow.modelVert, model_arrow.modelIndex, model_arrow.modelNormal, model_arrow.modelUV, model_arrow.modelBoneIndex, model_arrow.modelBoneWeight, model_arrow.frames);
      modelMap.insert(std::make_pair("Models/Arrow.obj", model_arrow));

	  model_stone.modelNumVert = AwesomeGL::loadSingleMesh("Models/rock.obj", model_stone.modelVert, model_stone.modelIndex, model_stone.modelNormal, model_stone.modelUV, model_stone.modelBoneIndex, model_stone.modelBoneWeight, model_stone.frames);
      modelMap.insert(std::make_pair("Models/rock.obj", model_stone));
      
	  model_flower.modelNumVert = AwesomeGL::loadSingleMesh("Models/flower.obj", model_flower.modelVert, model_flower.modelIndex, model_flower.modelNormal, model_flower.modelUV, model_flower.modelBoneIndex, model_flower.modelBoneWeight, model_flower.frames);
      modelMap.insert(std::make_pair("Models/flower.obj", model_flower));
      
	  model_grass.modelNumVert = AwesomeGL::loadSingleMesh("Models/grass.obj", model_grass.modelVert, model_grass.modelIndex, model_grass.modelNormal, model_grass.modelUV, model_grass.modelBoneIndex, model_grass.modelBoneWeight, model_grass.frames);
      modelMap.insert(std::make_pair("Models/grass.obj", model_grass));
   }
   
   bool setUpShaders() {
      if (! AwesomeGL::InstallShader("Diffuse.vert", "Diffuse.frag", &h_shadeProg)) {
         fprintf(stderr, "Error installing shader!\n");
         return false;
      }
      h_aPosition = safe_glGetAttribLocation(h_shadeProg, "aPosition");
      h_aNormal = safe_glGetAttribLocation(h_shadeProg, "aNormal");
      h_aUV = safe_glGetAttribLocation(h_shadeProg, "aUV");
      h_aBoneIndexs = safe_glGetAttribLocation(h_shadeProg, "aBoneIndexes");
      h_aBoneWeights = safe_glGetAttribLocation(h_shadeProg, "aBoneWeights");
      h_uBones = safe_glGetUniformLocation(h_shadeProg, "uBones");
      //h_projectionMatrix = safe_glGetUniformLocation(h_shadeProg, "projectionMatrix");
      h_viewMatrix = safe_glGetUniformLocation(h_shadeProg, "V");
      h_modelMatrix = safe_glGetUniformLocation(h_shadeProg, "M");
      h_uColor = safe_glGetUniformLocation(h_shadeProg, "color");
      h_shadowBiasMVP = safe_glGetUniformLocation(h_shadeProg, "shadowBiasMVP");
      h_shadowTexture = safe_glGetUniformLocation(h_shadeProg, "shadowTexture");
      h_M_inv_trans = safe_glGetUniformLocation(h_shadeProg, "M_inv_trans");
      h_lightPos = safe_glGetUniformLocation(h_shadeProg, "lightPos");
      h_MVP = safe_glGetUniformLocation(h_shadeProg, "MVP");
      h_modelTexture = safe_glGetUniformLocation(h_shadeProg, "modelTexture");
      h_lightColor = safe_glGetUniformLocation(h_shadeProg, "lightColor");
      //h_shadowFlag = safe_glGetUniformLocation(h_shadeProg, "shadowFlag");
      h_skyBox = safe_glGetUniformLocation(h_shadeProg, "skyBox");
      
      
      if (! AwesomeGL::InstallShader("Fonts.vert", "Fonts.frag", &h_FontProg)) {
         fprintf(stderr, "Error installing Font shader!\n");
         return false;
      }
      h_coord = safe_glGetAttribLocation(h_FontProg, "coord");
      h_tex = safe_glGetUniformLocation(h_FontProg, "tex");
      h_color = safe_glGetUniformLocation(h_FontProg, "color");
      
      if (! InstallShader("Shadow.vert", "Shadow.frag", &h_shadowProg)) {
         fprintf(stderr, "Error installing shader!\n");
         return false;
      }
      h_shadowMatrix = safe_glGetUniformLocation(h_shadowProg, "shadowMVP");
      h_shadowModelPosition = safe_glGetAttribLocation(h_shadowProg, "shadowModelPosition");
      h_shadowModelTexture = safe_glGetUniformLocation(h_shadowProg, "modelTexture");
      h_shadowUV = safe_glGetAttribLocation(h_shadowProg, "aUV");
      h_shadowBoneIndexs = safe_glGetAttribLocation(h_shadowProg, "aBoneIndexes");
      h_shadowBoneWeights = safe_glGetAttribLocation(h_shadowProg, "aBoneWeights");
      h_shadowBones = safe_glGetUniformLocation(h_shadowProg, "uBones");

      
      if (! InstallShader("Particle.vert", "Particle.frag", &h_particleProg)) {
         fprintf(stderr, "Error installing shader!\n");
         return false;
      }
      h_squareVertices = safe_glGetAttribLocation(h_particleProg, "squareVertices");
      h_xyzs = safe_glGetAttribLocation(h_particleProg, "xyzs");
      h_particleColor = safe_glGetAttribLocation(h_particleProg, "color");
      h_cameraRight_worldspace = safe_glGetUniformLocation(h_particleProg, "camRight");
      h_cameraUp_worldspace = safe_glGetUniformLocation(h_particleProg, "camUp");
      h_viewProjMatrix = safe_glGetUniformLocation(h_particleProg, "VP");
      h_particleTex  = safe_glGetUniformLocation(h_particleProg, "particleTex");
      
      if (! AwesomeGL::InstallShader("Billboard.vert", "Billboard.frag", &h_billboard))
      {
         fprintf(stderr, "Error installing Billboard Shader\n");
         return false;
      }
      
      h_CameraRight  = glGetUniformLocation(h_billboard, "CameraRight_worldspace");
      h_CameraUp = glGetUniformLocation(h_billboard, "CameraUp_worldspace");
      h_ViewProjMatrix = glGetUniformLocation(h_billboard, "VP");
      h_BillboardPos = glGetUniformLocation(h_billboard, "BillboardPos");
      h_BillboardSize = glGetUniformLocation(h_billboard, "BillboardSize");
      h_LifeLevel = glGetUniformLocation(h_billboard, "LifeLevel");
      
      h_BillboardTexture  = glGetUniformLocation(h_billboard, "myTextureSampler");
      
      h_BillboardSquareVertices = glGetAttribLocation(h_billboard, "squareVertices");
      
      if (! AwesomeGL::InstallShader("Icon.vert", "Icon.frag", &h_icon))
      {
         fprintf(stderr, "Error installing Billboard Shader\n");
         return false;
      }
      
      h_CameraRightIcon  = glGetUniformLocation(h_icon, "CameraRight_worldspace");
      h_CameraUpIcon = glGetUniformLocation(h_icon, "CameraUp_worldspace");
      h_ViewProjMatrixIcon = glGetUniformLocation(h_icon, "VP");
      h_IconPos = glGetUniformLocation(h_icon, "IconPos");
      h_IconSize = glGetUniformLocation(h_icon, "IconSize");
      
      h_IconTexture  = glGetUniformLocation(h_icon, "myTextureSampler");
      
      h_IconSquareVertices = glGetAttribLocation(h_icon, "squareVertices");
      
      return true;
   }
   
   void initGround() {
      
      // A x-z plane at y = 0 of dimension [-50, 50]^2
      float GrndPos[] = {
         -50, -50, 0,
         -50, 50,  0,
         50, 50,  0,
         50, -50, 0
      };
      
      
      static GLfloat GroundTex[] = {
         1, 0,
         0, 1,
         1, 1,
         1, 0
      };
      
      unsigned short idx[] = {0, 1, 2, 0, 2, 3};
      
      
      g_CiboLen = 6;
      glGenBuffers(1, &CubeBuffObj);
      glBindBuffer(GL_ARRAY_BUFFER, CubeBuffObj);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GrndPos), GrndPos, GL_STATIC_DRAW);
      
      glGenBuffers(1, &CIndxBuffObj);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CIndxBuffObj);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);
      
      glGenBuffers(1, &TexBuffObj);
      glBindBuffer(GL_ARRAY_BUFFER, TexBuffObj);
      glBufferData(GL_ARRAY_BUFFER, sizeof(GroundTex), GroundTex, GL_STATIC_DRAW);
   }
   
   int loadSingleMesh(const aiMesh *mesh,
                      GLuint &vertBuff,
                      GLuint &indexBuff,
                      GLuint &normalBuff,
                      GLuint &uvBuff)
   {
      //Set up bounding box
      boundingBox.max.x = mesh->mVertices[0].x;
      boundingBox.min.x = mesh->mVertices[0].x;
      boundingBox.max.y = mesh->mVertices[0].y;
      boundingBox.min.y = mesh->mVertices[0].y;
      boundingBox.max.z = mesh->mVertices[0].z;
      boundingBox.min.z = mesh->mVertices[0].z;
      
      for (unsigned int i = 0; i < mesh->mNumVertices; i++)
      {
         //Bounding box check
         if (mesh->mVertices[i].x > boundingBox.max.x) {
            boundingBox.max.x = mesh->mVertices[i].x;
         }
         if (mesh->mVertices[i].x < boundingBox.min.x) {
            boundingBox.min.x = mesh->mVertices[i].x;
         }
         if (mesh->mVertices[i].y > boundingBox.max.y) {
            boundingBox.max.y = mesh->mVertices[i].y;
         }
         if (mesh->mVertices[i].y < boundingBox.min.y) {
            boundingBox.min.y = mesh->mVertices[i].y;
         }
         if (mesh->mVertices[i].z > boundingBox.max.z) {
            boundingBox.max.z = mesh->mVertices[i].z;
         }
         if (mesh->mVertices[i].z < boundingBox.min.z) {
            boundingBox.min.z = mesh->mVertices[i].z;
         }
      }
      
      std::vector<GLushort> faces;
      for (unsigned int i = 0; i < mesh->mNumFaces; i++)
      {
         for (unsigned int j = 1; j + 1 < mesh->mFaces[i].mNumIndices; j += 2)
         {
            faces.push_back((GLushort)mesh->mFaces[i].mIndices[    0]);
            faces.push_back((GLushort)mesh->mFaces[i].mIndices[j + 0]);
            faces.push_back((GLushort)mesh->mFaces[i].mIndices[j + 1]);
         }
      }
      
      float *texCoords = NULL;
      if (mesh->HasTextureCoords(0)) {
         texCoords = (float *)malloc(sizeof(float)*2*mesh->mNumVertices);
         for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            texCoords[i*2] = mesh->mTextureCoords[0][i].x;
            texCoords[i*2+1] = mesh->mTextureCoords[0][i].y;
         }
      }
      
      glGenBuffers(1, &vertBuff);
      glBindBuffer(GL_ARRAY_BUFFER, vertBuff);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      
      glGenBuffers(1, &indexBuff);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuff);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * faces.size(), &faces[0], GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      
      glGenBuffers(1, &normalBuff);
      glBindBuffer(GL_ARRAY_BUFFER, normalBuff);
      glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      
      if (texCoords) {
         glGenBuffers(1, &uvBuff);
         glBindBuffer(GL_ARRAY_BUFFER, uvBuff);
         glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2*mesh->mNumVertices, texCoords, GL_STATIC_DRAW);
         glBindBuffer(GL_ARRAY_BUFFER, 0);
      } else {
         texCoords = 0;
      }
      
      return faces.size();
   }
   
   int loadSingleMesh(const char *filename,
                      GLuint &vertBuff,
                      GLuint &indexBuff,
                      GLuint &normalBuff,
                      GLuint &uvBuff)
   {
      const struct aiScene *scene = aiImportFile(filename, aiProcessPreset_TargetRealtime_MaxQuality);
      aiMesh *mesh = scene->mMeshes[0];
      return loadSingleMesh(mesh, vertBuff, indexBuff, normalBuff, uvBuff);
   }
   
   glm::mat4 aiMatrix4x4ToMat4(const aiMatrix4x4 &mat)
   {
      return glm::mat4(mat.a1, mat.b1, mat.c1, mat.d1,
                       mat.a2, mat.b2, mat.c2, mat.d2,
                       mat.a3, mat.b3, mat.c3, mat.d3,
                       mat.a4, mat.b4, mat.c4, mat.d4);
   }
   
   glm::vec3 aiVector3DToVec3(const aiVector3D &vec)
   {
      return glm::vec3(vec.x, vec.y, vec.z);
   }
   
   glm::quat aiQuaternionToQuat(const aiQuaternion &quat)
   {
      /*return glm::quat(quat.x, quat.y, quat.z, quat.w);*/
      return glm::quat(quat.w, quat.x, quat.y, quat.z);
   }
   
   void readAnimation(const aiScene *scene, const aiMesh *mesh, const aiAnimation *animation, const aiNode *current, double time, glm::mat4 transform, glm::mat4 *frames)
   {
      aiNodeAnim *nodeAnimation = NULL;
      for (unsigned int cindex = 0; cindex < animation->mNumChannels; cindex++)
      {
         if (animation->mChannels[cindex]->mNodeName == current->mName)
         {
            nodeAnimation = animation->mChannels[cindex];
            break;
         }
      }
      
      if (nodeAnimation == NULL)
      {
         glm::mat4 def(aiMatrix4x4ToMat4(current->mTransformation));
         transform = transform * def;
      }
      else
      {
         for (unsigned int pindex = 0; pindex < nodeAnimation->mNumPositionKeys; pindex++)
         {
            if (pindex + 1 == nodeAnimation->mNumPositionKeys || nodeAnimation->mPositionKeys[pindex + 1].mTime > time)
            {
               transform = transform * glm::translate(aiVector3DToVec3(nodeAnimation->mPositionKeys[pindex].mValue));
               break;
            }
         }
         for (unsigned int rindex = 0; rindex < nodeAnimation->mNumRotationKeys; rindex++)
         {
            if (rindex + 1 == nodeAnimation->mNumRotationKeys || nodeAnimation->mRotationKeys[rindex + 1].mTime > time)
            {
               transform = transform * glm::toMat4(aiQuaternionToQuat(nodeAnimation->mRotationKeys[rindex].mValue));
               break;
            }
         }
         for (unsigned int sindex = 0; sindex < nodeAnimation->mNumScalingKeys; sindex++)
         {
            if (sindex + 1 == nodeAnimation->mNumScalingKeys || nodeAnimation->mScalingKeys[sindex + 1].mTime > time)
            {
               transform = transform * glm::scale(aiVector3DToVec3(nodeAnimation->mScalingKeys[sindex].mValue));
               break;
            }
         }
      }
      
      for (unsigned int bindex = 0; bindex < mesh->mNumBones; bindex++)
      {
         if (current->mName == mesh->mBones[bindex]->mName)
         {
            frames[bindex] = transform * aiMatrix4x4ToMat4(mesh->mBones[bindex]->mOffsetMatrix);
         }
      }
      
      for (unsigned int cindex = 0; cindex < current->mNumChildren; cindex++)
      {
         readAnimation(scene, mesh, animation, current->mChildren[cindex], time, transform, frames);
      }
   }
   
   int loadSingleMesh(const char *filename,
                      GLuint &vertBuff,
                      GLuint &indexBuff,
                      GLuint &normalBuff,
                      GLuint &uvBuff,
                      GLuint &boneIndex,
                      GLuint &boneWeight,
                      std::vector<std::vector<keyframe_t> > &p_frames)
   {
      const aiScene *scene = aiImportFile(filename, aiProcessPreset_TargetRealtime_MaxQuality & (~aiProcess_Debone));
      const aiMesh *mesh = scene->mMeshes[0];
      
      int count = loadSingleMesh(mesh, vertBuff, indexBuff, normalBuff, uvBuff);
      
      unsigned short *bone_counts = new unsigned short[mesh->mNumVertices]();
      glm::vec2 *bone_indexes = new glm::vec2[mesh->mNumVertices]();
      glm::vec2 *bone_weights = new glm::vec2[mesh->mNumVertices]();
      
      /*printf("number of bones %u\n", mesh->mNumBones);*/
      for (unsigned int i = 0; i < mesh->mNumBones; i++)
      {
         for (unsigned int j = 0; j < mesh->mBones[i]->mNumWeights; j++)
         {
            unsigned int vertex_id = mesh->mBones[i]->mWeights[j].mVertexId;
            /*printf("vertex %u with bone %u for weight %f\n", vertex_id, i, mesh->mBones[i]->mWeights[j].mWeight);*/
            
            if (bone_counts[vertex_id] == 0)
            {
               bone_indexes[vertex_id].x = (float)i;
               bone_weights[vertex_id].x = mesh->mBones[i]->mWeights[j].mWeight;
            }
            if (bone_counts[vertex_id] == 1)
            {
               bone_indexes[vertex_id].y = (float)i;
               bone_weights[vertex_id].y = mesh->mBones[i]->mWeights[j].mWeight;
            }
            bone_counts[vertex_id]++;
         }
      }
      
      for (unsigned int i = 0; i < scene->mNumAnimations; i++)
      {
         std::set<double> times;
         for (unsigned int j = 0; j < scene->mAnimations[i]->mNumChannels; j++)
         {
            for (unsigned int k = 0; k < scene->mAnimations[i]->mChannels[j]->mNumPositionKeys; k++)
            {
               times.insert(scene->mAnimations[i]->mChannels[j]->mPositionKeys[k].mTime);
            }
            for (unsigned int k = 0; k < scene->mAnimations[i]->mChannels[j]->mNumRotationKeys; k++)
            {
               times.insert(scene->mAnimations[i]->mChannels[j]->mRotationKeys[k].mTime);
            }
            for (unsigned int k = 0; k < scene->mAnimations[i]->mChannels[j]->mNumScalingKeys; k++)
            {
               times.insert(scene->mAnimations[i]->mChannels[j]->mScalingKeys[k].mTime);
            }
         }
         
         p_frames.push_back(std::vector<std::pair<double, glm::mat4 *> >());
         
         unsigned int j = 0;
         for (auto time = times.begin(); time != times.end(); time++, j++)
         {
            /*printf("Keyframe for %f\n", *time);*/
            p_frames[i].push_back(std::pair<double, glm::mat4 *>(*time, new glm::mat4[NUM_BONES]()));
            readAnimation(scene,
                          mesh,
                          scene->mAnimations[i],
                          scene->mRootNode,
                          *time,
                          glm::mat4(1.0f),
                          p_frames[i][j].second);
         }
      }
      
      glGenBuffers(1, &boneIndex);
      glBindBuffer(GL_ARRAY_BUFFER, boneIndex);
      glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * mesh->mNumVertices, bone_indexes, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      
      glGenBuffers(1, &boneWeight);
      glBindBuffer(GL_ARRAY_BUFFER, boneWeight);
      glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * mesh->mNumVertices, bone_weights, GL_STATIC_DRAW);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      
      delete bone_counts;
      delete bone_indexes;
      delete bone_weights;
      
      return count;
   }
   
   bool InstallShader(std::string const & vShaderName, std::string const & fShaderName, GLuint *prog)
   {
      GLuint VS; // handles to shader object
      GLuint FS; // handles to frag shader object
      GLint vCompiled, fCompiled, linked; // status of shader

      printf("Compiling %s and %s\n", vShaderName.c_str(), fShaderName.c_str());
      
      VS = glCreateShader(GL_VERTEX_SHADER);
      FS = glCreateShader(GL_FRAGMENT_SHADER);
      
      // load the source
      char const * vSource = textFileRead(vShaderName);
      char const * fSource = textFileRead(fShaderName);
      glShaderSource(VS, 1, & vSource, NULL);
      glShaderSource(FS, 1, & fSource, NULL);
   
#ifdef _WIN32
      GLboolean canCompile;
      glGetBooleanv(GL_SHADER_COMPILER, &canCompile);
      if (!canCompile) {
         fprintf(stderr, "Can't compile\n");
      }
      if (!glIsShader(VS) || !glIsShader(FS)) {
         fprintf(stderr, "Not a shader\n");
      }
#endif
      glCompileShader(VS);
      printOpenGLError();
      glGetShaderiv(VS, GL_COMPILE_STATUS, & vCompiled);
      printShaderInfoLog(VS);
      
      // compile shader and print log
      glCompileShader(FS);
      printOpenGLError();
      glGetShaderiv(FS, GL_COMPILE_STATUS, & fCompiled);
      printShaderInfoLog(FS);
      
      if (! vCompiled || ! fCompiled)
      {
         std::cerr << "Error compiling either shader " << vShaderName << " or " << fShaderName << std::endl;
         return false;
      }
      
      // create a program object and attach the compiled shader
      *prog = glCreateProgram();
      glAttachShader(*prog, VS);
      glAttachShader(*prog, FS);
      
      glLinkProgram(*prog);
      
      // check shader status requires helper functions
      printOpenGLError();
      glGetProgramiv(*prog, GL_LINK_STATUS, &linked);
      printProgramInfoLog(*prog);
      
      glUseProgram(*prog);
      return true;
   }
   
   
   /* BMP file loader loads a 24-bit bmp file only */
   
   /*
    * getint and getshort are help functions to load the bitmap byte by byte
    */
   static unsigned int getint(FILE *fp) {
      int c, c1, c2, c3;
      
      /*  get 4 bytes */
      c = getc(fp);
      c1 = getc(fp);
      c2 = getc(fp);
      c3 = getc(fp);
      
      return ((unsigned int) c) +
      (((unsigned int) c1) << 8) +
      (((unsigned int) c2) << 16) +
      (((unsigned int) c3) << 24);
   }
   
   static unsigned int getshort(FILE *fp){
      int c, c1;
      
      /* get 2 bytes*/
      c = getc(fp);
      c1 = getc(fp);
      
      return ((unsigned int) c) + (((unsigned int) c1) << 8);
   }
   
   
   /*  quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  */
   
   int ImageLoad(char *filename, Image *image) {
      FILE *file;
      unsigned long size;                 /*  size of the image in bytes. */
      unsigned long i;                    /*  standard counter. */
      unsigned short int planes;          /*  number of planes in image (must be 1)  */
      unsigned short int bpp;             /*  number of bits per pixel (must be 24) */
      char temp;                          /*  used to convert bgr to rgb color. */
      
      /*  make sure the file is there. */
      if ((file = fopen(filename, "rb"))==NULL) {
         fprintf(stderr, "File Not Found : %s\n",filename);
         return 0;
      }
      
      /*  seek through the bmp header, up to the width height: */
      fseek(file, 18, SEEK_CUR);
      
      /*  No 100% errorchecking anymore!!! */
      
      /*  read the width */    image->sizeX = getint (file);
      
      /*  read the height */
      image->sizeY = getint (file);
      
      /*  calculate the size (assuming 24 bits or 3 bytes per pixel). */
      size = image->sizeX * image->sizeY * 3;
      
      /*  read the planes */
      planes = getshort(file);
      if (planes != 1) {
         fprintf(stderr, "Planes from %s is not 1: %u\n", filename, planes);
         return 0;
      }
      
      /*  read the bpp */
      bpp = getshort(file);
      if (bpp != 24) {
         fprintf(stderr, "Bpp from %s is not 24: %u\n", filename, bpp);
         return 0;
      }
      
      /*  seek past the rest of the bitmap header. */
      fseek(file, 24, SEEK_CUR);
      
      /*  read the data.  */
      image->data = (char *) malloc(size);
      if (image->data == NULL) {
         fprintf(stderr, "Error allocating memory for color-corrected image data");
         return 0;
      }
      
      if ((i = fread(image->data, size, 1, file)) != 1) {
         fprintf(stderr, "Error reading image data from %s.\n", filename);
         return 0;
      }
      
      for (i=0;i<size;i+=3) { /*  reverse all of the colors. (bgr -> rgb) */
         temp = image->data[i];
         image->data[i] = image->data[i+2];
         image->data[i+2] = temp;
      }
      
      fclose(file); /* Close the file and release the filedes */
      
      /*  we're done. */
      return 1;
   }
   
   //routines to load in a bmp files - must be 2^nx2^m and a 24bit bmp
   GLvoid loadTexture_BMP(char* image_file, int texID) {
      
      TextureImage = (Image *) malloc(sizeof(Image));
      if (TextureImage == NULL) {
         fprintf(stderr, "Error allocating space for image");
         exit(1);
      }
      if (!ImageLoad(image_file, TextureImage)) {
         fprintf(stderr, "failed to load image '%s'\n", image_file);
         exit(1);
      }
      /*  2d texture, level of detail 0 (normal), 3 components (red, green, blue),            */
      /*  x size from image, y size from image,                                              */
      /*  border 0 (normal), rgb color data, unsigned byte data, data  */
      glBindTexture(GL_TEXTURE_2D, texID);
      glTexImage2D(GL_TEXTURE_2D, 0, 3,
                   TextureImage->sizeX, TextureImage->sizeY,
                   0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST); /*  cheap scaling when image bigger than texture */
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); /*  cheap scaling when image smalled than texture*/
      
   }

   
   GLuint loadTexture_PNG(const std::string filename, int &width, int &height)
   {
      //header for testing if it is a png
      png_byte header[8];
      
      //open file as binary
      FILE *fp = fopen(filename.c_str(), "rb");
      if (!fp) {
         return TEXTURE_LOAD_ERROR;
      }
      
      //read the header
      fread(header, 1, 8, fp);
      
      //test if png
      int is_png = !png_sig_cmp(header, 0, 8);
      if (!is_png) {
         fclose(fp);
         return TEXTURE_LOAD_ERROR;
      }
      
      //create png struct
      png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
                                                   NULL, NULL);
      if (!png_ptr) {
         fclose(fp);
         return (TEXTURE_LOAD_ERROR);
      }
      
      //create png info struct
      png_infop info_ptr = png_create_info_struct(png_ptr);
      if (!info_ptr) {
         png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
         fclose(fp);
         return (TEXTURE_LOAD_ERROR);
      }
      
      //create png info struct
      png_infop end_info = png_create_info_struct(png_ptr);
      if (!end_info) {
         png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
         fclose(fp);
         return (TEXTURE_LOAD_ERROR);
      }
      
      //png error stuff, not sure libpng man suggests this.
      if (setjmp(png_jmpbuf(png_ptr))) {
         png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
         fclose(fp);
         return (TEXTURE_LOAD_ERROR);
      }
      
      //init png reading
      png_init_io(png_ptr, fp);
      
      //let libpng know you already read the first 8 bytes
      png_set_sig_bytes(png_ptr, 8);
      
      // read all the info up to the image data
      png_read_info(png_ptr, info_ptr);
      
      //variables to pass to get info
      int bit_depth, color_type;
      png_uint_32 twidth, theight;
      
      // get info about png
      png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
                   NULL, NULL, NULL);
      
      //update width and height based on png info
      width = twidth;
      height = theight;
      
      // Update the png info struct.
      png_read_update_info(png_ptr, info_ptr);
      
      // Row size in bytes.
      int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
      
      // Allocate the image_data as a big block, to be given to opengl
      png_byte *image_data = new png_byte[rowbytes * height];
      if (!image_data) {
         //clean up memory and close stuff
         png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
         fclose(fp);
         return TEXTURE_LOAD_ERROR;
      }
      
      //row_pointers is for pointing to image_data for reading the png with libpng
      png_bytep *row_pointers = new png_bytep[height];
      if (!row_pointers) {
         //clean up memory and close stuff
         png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
         delete[] image_data;
         fclose(fp);
         return TEXTURE_LOAD_ERROR;
      }
      // set the individual row_pointers to point at the correct offsets of image_data
      for (int i = 0; i < height; ++i)
         row_pointers[height - 1 - i] = image_data + i * rowbytes;
      
      //read the png into image_data through row_pointers
      png_read_image(png_ptr, row_pointers);
      
      //Now generate the OpenGL texture object
      GLuint texture;
      glGenTextures(1, &texture);
      glBindTexture(GL_TEXTURE_2D, texture);
      glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, width, height, 0,
                   GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) image_data);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      
      //clean up memory and close stuff
      png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
      delete[] image_data;
      delete[] row_pointers;
      fclose(fp);
      
      return texture;
   }
}
