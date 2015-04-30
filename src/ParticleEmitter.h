#ifndef __ParticleEmitter__
#define __ParticleEmitter__

#include <iostream>
#include "AwesomeGL.h"

struct Particle{
	glm::vec3 pos, speed;
	unsigned char r,g,b,a;
	float size, angle, weight;
	float life;
	float camDist;
   
	bool operator<(const Particle& that) const {
		return this->camDist > that.camDist;
	}
};

class ParticleEmitter {
public:
   ParticleEmitter(int max, float life, float speed, glm::vec3 pos, float size = 1.0, bool repeat = false, glm::vec3 mainDir = glm::vec3(0, 10, 0), glm::vec3 grav = glm::vec3(0, 1, 0));
   ~ParticleEmitter();
   
   int findUnusedParticle();
   void sortParticles();
   void setGravity(glm::vec3 grav);
   void setSpread(float spread);
   void start();
   void stop();
   void Update();
   void setColor(glm::vec4 color);
   void setPos(glm::vec3 pos);
   void setDir(glm::vec3 dir);
   
   void randomRed(bool randRed);
   void randomGreen(bool randGreen);
   void randomBlue(bool randBlue);
   void randomAlpha(bool randAlpha);
   
   bool randRed, randGreen, randBlue, randAlpha;
   glm::vec4 color;
   Particle container[10000];
   int maxParticles;
   int lastUsedParticle;
   glm::vec3 pos;
   float life;
   float speed;
   float spread;
   float size;
   glm::vec3 mainDir;
   glm::vec3 grav;
   bool repeat;
   int numParticles;
   
   GLfloat* particlePosSizeData;
   GLubyte* particleColorData;
   
   GLuint billboard_vertex_buffer;
   GLuint particles_position_buffer;
   GLuint particles_color_buffer;
};

#endif
