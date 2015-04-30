#include "ParticleEmitter.h"

using namespace AwesomeGL;

ParticleEmitter::ParticleEmitter(int max, float life, float speed, glm::vec3 pos, float size, bool repeat, glm::vec3 mainDir, glm::vec3 grav) {
   maxParticles = max;
   this->grav = grav;
   this->speed = speed;
   this->pos = pos;
   this->life = life;
   spread = 1.5f;
   this->mainDir = mainDir;
   this->size = size;
   lastUsedParticle = 0;
   for (int i = 0; i < maxParticles; i++) {
      container[i].life = 1.0f;
      container[i].camDist = -1.0f;
      container[i].speed = glm::vec3(1);
      container[i].a = 0;
   }
   
   this->repeat = repeat;
   numParticles = 0;
   randRed = randGreen = randBlue = randAlpha = false;
   
   color = glm::vec4(rand() ^ 256, rand() ^ 256, rand() ^ 256, (rand() ^ 256) / 3);
   
   particlePosSizeData = new GLfloat[maxParticles * 4];
   particleColorData = new GLubyte[maxParticles * 4];
   
	GLfloat g_vertex_buffer_data[] = {
      -0.5f, -0.5f, 0.0f,
      0.5f, -0.5f, 0.0f,
      -0.5f,  0.5f, 0.0f,
      0.5f,  0.5f, 0.0f,
	};
   
   for (int i = 0; i < 12; i++) {
      g_vertex_buffer_data[i] *= size;
   }
	
	glGenBuffers(1, &billboard_vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
   
	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
   
	glGenBuffers(1, &particles_color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
	glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
}

ParticleEmitter::~ParticleEmitter() {
   
}

void ParticleEmitter::randomRed(bool randRed) {
   this->randRed = randRed;
}

void ParticleEmitter::randomGreen(bool randGreen) {
   this->randGreen = randGreen;
}

void ParticleEmitter::randomBlue(bool randBlue) {
   this->randBlue = randBlue;
}

void ParticleEmitter::randomAlpha(bool randAlpha) {
   this->randAlpha = randAlpha;
}

void ParticleEmitter::setDir(glm::vec3 dir) {
   mainDir = dir;
}

void ParticleEmitter::setPos(glm::vec3 pos) {
   this->pos = pos;
}

void ParticleEmitter::setSpread(float spread) {
   this->spread = spread;
}

void ParticleEmitter::setGravity(glm::vec3 grav) {
   this->grav = grav;
}

int ParticleEmitter::findUnusedParticle() {
   for (int i = lastUsedParticle; i < maxParticles; i++) {
      if (container[i].life < 0) {
         lastUsedParticle = i;
         return i;
      }
   }
   
   for (int i = 0; i < lastUsedParticle; i++) {
      if (container[i].life < 0) {
         lastUsedParticle = i;
         return i;
      }
   }
   
   return 0;
}

void ParticleEmitter::setColor(glm::vec4 color) {
   this->color = color;
}

void ParticleEmitter::start() {
   addParticle(this);
}

void ParticleEmitter::stop() {
   removeParticle(this);
}

void ParticleEmitter::sortParticles() {
   std::sort(&container[0], &container[maxParticles]);
}

void ParticleEmitter::Update() {
   
   glm::mat4 ViewMatrix = getViewMatrix();
   glm::vec3 camPos(glm::inverse(ViewMatrix)[3]);
   glm:: mat4 VP = getProjectionMatrix() * ViewMatrix;
   
   int newParticles;// = (int)(deltaTime.asSeconds() * 10000.0);
   /*if (newParticles > (int) (0.016f * 10000.0))
    newParticles = (int)(0.016f * 10000.0);
    */
   //newParticles
   newParticles = (maxParticles/100)/life;
   if (newParticles < 1) {
      newParticles = 1;
   }
   //newParticles = 16;
   
   numParticles += newParticles;
   if (repeat == true) {
      for (int i = 0; i < newParticles; i++) {
         int index = findUnusedParticle();
         container[index].life = life;
         container[index].pos = pos;
         
         //bad random direction generation, but whatevs
         glm::vec3 randomDir = glm::vec3(
                                         (rand()%2000 - 1000.0f)/1000.0f,
                                         (rand()%2000 - 1000.0f)/1000.0f,
                                         (rand()%2000 - 1000.0f)/1000.0f
                                         );
         
         container[index].speed = mainDir + randomDir * spread;
         
         if (randRed)
            container[index].r = rand() ^ 256;
         else
            container[index].r = color.x;
         
         if (randGreen)
            container[index].g = rand() ^ 256;
         else
            container[index].g = color.y;
         
         if (randBlue)
            container[index].b = rand() ^ 256;
         else
            container[index].b = color.z;
         
         if (randAlpha)
            container[index].a = rand() ^ 256;
         else
            container[index].a = color.w;
         
         container[index].size = (rand() % 1000)/2000.0f + 0.1f;
      }
   }
   else {
      for (int i = 0; i < newParticles && numParticles < maxParticles; i++) {
         int index = findUnusedParticle();
         container[index].life = life;
         container[index].pos = pos;
         
         //bad random direction generation, but whatevs
         glm::vec3 randomDir = glm::vec3(
                                         (rand()%2000 - 1000.0f)/1000.0f,
                                         (rand()%2000 - 1000.0f)/1000.0f,
                                         (rand()%2000 - 1000.0f)/1000.0f
                                         );
         
         container[index].speed = mainDir + randomDir * spread;
         
         if (randRed)
            container[index].r = rand() ^ 256;
         else
            container[index].r = color.x;
         
         if (randGreen)
            container[index].g = rand() ^ 256;
         else
            container[index].g = color.y;
         
         if (randBlue)
            container[index].b = rand() ^ 256;
         else
            container[index].b = color.z;
         
         if (randAlpha)
            container[index].a = rand() ^ 256;
         else
            container[index].a = color.w;
         container[index].size = (rand() % 1000)/2000.0f + 0.1f;
      }
   }
   int particleCount = 0;
   for (int i = 0; i < maxParticles; i++) {
      
      Particle& p = container[i];
      
      if (p.life > 0.0f) {
         p.life -= deltaTime.asSeconds();
         
         if (p.life > 0.0f) {
            p.speed += grav * (float)deltaTime.asSeconds() * speed;
            p.pos += p.speed * (float)deltaTime.asSeconds();
            p.camDist = glm::length(p.pos - camPos);
            
            particlePosSizeData[4 * particleCount + 0] = p.pos.x;
            particlePosSizeData[4 * particleCount + 1] = p.pos.y;
            particlePosSizeData[4 * particleCount + 2] = p.pos.z;
            
            particlePosSizeData[4 * particleCount + 3] = p.size;
            
            particleColorData[4 * particleCount + 0] = p.r;
            particleColorData[4 * particleCount + 1] = p.g;
            particleColorData[4 * particleCount + 2] = p.b;
            particleColorData[4 * particleCount + 3] = p.a;
         }
         else {
            p.camDist = -1.0f;
         }
         
         particleCount++;
      }
      else {
         p.camDist = -1.0f;
      }
   }
   
   sortParticles();
   
   glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
   glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, particleCount * sizeof(GLfloat) * 4, particlePosSizeData);
   
   glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
   glBufferData(GL_ARRAY_BUFFER, maxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, particleCount * sizeof(GLubyte) * 4, particleColorData);
   
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, tex_yellow);
   glUniform1i(h_particleTex, 0);
   
   glUniform3f(h_cameraRight_worldspace, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
   glUniform3f(h_cameraUp_worldspace   , ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);
   
   glUniformMatrix4fv(h_viewProjMatrix, 1, GL_FALSE, &VP[0][0]);
   
   glEnableVertexAttribArray(h_squareVertices);
   glBindBuffer(GL_ARRAY_BUFFER, billboard_vertex_buffer);
   glVertexAttribPointer(h_squareVertices, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
   
   glEnableVertexAttribArray(h_xyzs);
   glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
   glVertexAttribPointer(h_xyzs, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
   
   glEnableVertexAttribArray(h_particleColor);
   glBindBuffer(GL_ARRAY_BUFFER, particles_color_buffer);
   glVertexAttribPointer(h_particleColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, (void*)0);
   
   glVertexAttribDivisorARB(h_squareVertices, 0);
   glVertexAttribDivisorARB(h_xyzs, 1);
   glVertexAttribDivisorARB(h_particleColor, 1);
   
   glDrawArraysInstancedARB(GL_TRIANGLE_STRIP, 0, 4, particleCount);
   
   glVertexAttribDivisorARB(h_squareVertices, 0);
   glVertexAttribDivisorARB(h_xyzs, 0);
   glVertexAttribDivisorARB(h_particleColor, 0);
   
   glDisableVertexAttribArray(h_squareVertices);
   glDisableVertexAttribArray(h_xyzs);
   glDisableVertexAttribArray(h_particleColor);
   
   if (repeat == false && newParticles >= maxParticles && container[maxParticles-1].life <= 0.0f) {
      stop();
   }
}