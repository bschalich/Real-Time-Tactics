#include "GameMap.h"

using namespace AwesomeGL;

GameMap::GameMap() {
	mapNumVert = AwesomeGL::loadSingleMesh("Models/Tile.dae", mapVert, mapIndex, mapNormal, mapUV);
	float randomHeights[5] = {.5, .7, .6, .65, .4};
	float randomRockHeights[4] = {2.0, 3.7, 2.8, 3.2};

	char *line = new char[10];
   std::ifstream file ("Maps/map1.txt");
   for (int i = 0; i < MAP_LENGTH; i++)
   {
      for (int j = 0; j < MAP_WIDTH; j++)
      {
         tile[i][j] = new MapTile(i, j);

	   file.read(line, 1);
	   while (line[0] == '\n')
	   {
		   file.read(line, 1);
	   }
	   if (line[0] == 'T')
	   {
		   tile[i][j]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
	   }
	   else if (line[0] == 'R')
	   {
		   tile[i][j]->setObject("Models/rock.obj", "Models/stone_texture.bmp", -5, glm::vec3(1.3, randomRockHeights[rand() % 4], 1.3), true);
		   tile[i][j]->getObject()->setColor(glm::vec3(1, 1, 1));
		   tile[i][j]->getObject()->rotate(rand() % 360, vec3(0, 1, 0));
	   }
	   else if (line[0] == 'F')
	   {
		   tile[i][j]->setObject("Models/flower.obj", "Models/flower.bmp", -5, glm::vec3(1, 1, 1), false);
		   tile[i][j]->getObject()->setColor(glm::vec3(1, 0.8, 0.2));
		   tile[i][j]->getObject()->rotate(rand() % 360, vec3(0, 1, 0));
	   }
	   /*else if (line[0] == 'G')
	   {
		   tile[i][j]->setObject("Models/grass.obj", "Models/grass.bmp", -5, glm::vec3(10, 10, 10), false);
		   //tile[i][j]->getObject()->setColor(glm::vec3(1, 0.8, 0.2));
		   tile[i][j]->getObject()->rotate(rand() % 360, vec3(0, 1, 0));
	   }*/
      }
   }

   /*tile[5][5]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[8][10]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[18][2]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[3][9]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[16][6]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[16][8]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[0][3]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[0][4]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[18][14]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[14][13]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[10][8]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[12][6]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[3][19]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);

   tile[2][1]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[6][15]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[4][7]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[5][19]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[16][15]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[14][17]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   tile[9][5]->setObject("Models/Tree_3.obj", "Tree3", -12, glm::vec3(.1, randomHeights[rand() % 5], .1), true);
   */
   //tile[5][5]->setObject("Models/Tree_1.obj", -10, glm::vec3(.1, .5, .1), true);
   //printf("5 5 getObject: %d\n", tile[5][5]->getObject());
   //printf("0 5 getObject: %d\n", tile[0][5]->getObject());
}

bool GameMap::isOccupied(int row, int col) {
   return tile[row][col]->checkOccupied();
}

MapTile* GameMap::getTile(int i, int j) {
   return tile[i][j];
}

GameMap::~GameMap() {
   
}
