#ifndef __UI__
#define __UI__

#include "Entity.h"
#include <string>
#include "Combatant.h"

class UI {
public:
   UI(unsigned int x, unsigned int y);
   ~UI();
   
   void update();
   void countdown();
   void gameOver();

private:
	float sx;
	float sy;

	GLfloat *white;
	GLfloat *blue;
	GLfloat *green;
	GLfloat *red;

	bool startCountdown;
	sf::Clock *startClock;

};

#endif
