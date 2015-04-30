#include "UI.h"

UI::UI(unsigned int x, unsigned int y)
{
	sx = 2.0f / x;
	sy = 2.0f / y;

	white = new GLfloat[4]();
	white[0] = 1;
	white[1] = 1;
	white[2] = 1;
	white[3] = 1;

	green = new GLfloat[4]();
	green[0] = 0;
	green[1] = 0;
	green[2] = 1;
	green[3] = 1;

	red = new GLfloat[4]();
	red[0] = 1;
	red[1] = 0;
	red[2] = 0;
	red[3] = 1;

	blue = new GLfloat[4]();
	blue[0] = 0;
	blue[1] = 0;
	blue[2] = 1;
	blue[3] = 1;

	startCountdown = false;
}

UI::~UI()
{
}

void UI::gameOver()
{
	glUseProgram(h_FontProg);
	glUniform4fv(h_color, 1, white);

	AwesomeGL::renderText("Game Over", AwesomeGL::arial96, -300 * sx, 50 * sy, sx, sy);

	glUseProgram(0);
}

void UI::countdown()
{
	if (!startCountdown)
	{
		startClock = new sf::Clock();
		startCountdown = true;
	}
	else
	{
		glUseProgram(h_FontProg);
	glUniform4fv(h_color, 1, white);

		if (startClock->getElapsedTime().asSeconds() < 1)
		{
			AwesomeGL::renderText("5", AwesomeGL::arial250, -75 * sx, 50 * sy, sx, sy);
		}
		else if (startClock->getElapsedTime().asSeconds() < 2)
		{
			AwesomeGL::renderText("4", AwesomeGL::arial250, -75 * sx, 50 * sy, sx, sy);
		}
		else if (startClock->getElapsedTime().asSeconds() < 3)
		{
			AwesomeGL::renderText("3", AwesomeGL::arial250, -75 * sx, 50 * sy, sx, sy);
		}
		else if (startClock->getElapsedTime().asSeconds() < 4)
		{
			AwesomeGL::renderText("2", AwesomeGL::arial250, -75 * sx, 50 * sy, sx, sy);
		}
		else if (startClock->getElapsedTime().asSeconds() < 5)
		{
			AwesomeGL::renderText("1", AwesomeGL::arial250, -75 * sx, 50 * sy, sx, sy);
         camera->cameraLock = false;
         camera->zoom(true);
		}
		else if (startClock->getElapsedTime().asSeconds() < 6)
		{
			AwesomeGL::renderText("FIGHT", AwesomeGL::arial250, -350 * sx, 50 * sy, sx, sy);
		}
		glUseProgram(0);
	}
}

void UI::update()
{
	//RENDER TEXT (FPS DISPLAY)
	glUseProgram(h_FontProg);
	glUniform4fv(h_color, 1, white);

	float fps = 1.f / AwesomeGL::deltaTime.asSeconds();
	char _Buf[2 * 32];
	sprintf(_Buf, "%2.f", fps);

	AwesomeGL::renderText(_Buf, AwesomeGL::arial48,
						 -1 + 15 * sx, -1 + 15 * sy, sx, sy);
      
      sprintf(_Buf, "Heroes");
	  AwesomeGL::renderText(_Buf, AwesomeGL::erin32, -1 + 10 * sx,   1 - 40 * sy, sx, sy);

	  for (unsigned int i = 0; i < heroList.size(); i++) {
        if (activeHero == heroList[i]) {
			glUniform4fv(h_color, 1, blue);
        }
		else {
			glUniform4fv(h_color, 1, white);
		}
		sprintf(_Buf, "Health: %d", heroList[i]->getHealth());
		AwesomeGL::renderText(_Buf, AwesomeGL::erin32, -1 + 10 * sx,   1 - (sy * ((i + 1) * 35 + 40)), sx, sy);
    }

	  glUniform4fv(h_color, 1, white);
	  sprintf(_Buf, "Enemies");
	  AwesomeGL::renderText(_Buf, AwesomeGL::erin32, -1 + 1110 * sx,   1 - 40 * sy, sx, sy);
	  for (unsigned int i = 0; i < enemyList.size(); i++) {
		glUniform4fv(h_color, 1, white);
		sprintf(_Buf, "Health: %d", enemyList[i]->getHealth());
		AwesomeGL::renderText(_Buf, AwesomeGL::erin32, -1 + 1110 * sx,   1 - (sy * ((i + 1) * 35 + 40)), sx, sy);
    }
      
      glUseProgram(0);
}
