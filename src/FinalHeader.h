#ifdef __APPLE__
#include "GLUT/glut.h"
#include <OPENGL/gl.h>
#endif

#ifdef __unix__
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include <GL/glew.h>
#include <GL/glut.h>

#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "freeglut.lib")
#endif

#include <iostream>
#include <string>
#include <unistd.h>
#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <ctime>
#include <sys/time.h>
#include <math.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL_helper.h"
#include "MStackHelp.h"
#include "CMeshLoaderSimple.h"

#include "GeometryCreator.h"

#define treeNum 350
#define windmillNum 50
#define zombNum 80
#define graveNum1 180
#define graveNum2 60
#define graveNum3 30
#define bladeNum 50
#define blockNum 40
#define wallNum 55
#define lifeNum 60

typedef void (*NumberFunctionPointer) (vec3 location, float scale, int rotate, float textRed, float textGreen, float textBlue);

void Draw0(vec3 location, float scale, int rotate, float textRed, float textGreen, float textBlue);
void Draw1(vec3 location, float scale, int rotate, float textRed, float textGreen, float textBlue);
void Draw2(vec3 location, float scale, int rotate, float textRed, float textGreen, float textBlue);
void Draw3(vec3 location, float scale, int rotate, float textRed, float textGreen, float textBlue);
void Draw4(vec3 location, float scale, int rotate, float textRed, float textGreen, float textBlue);
void Draw5(vec3 location, float scale, int rotate, float textRed, float textGreen, float textBlue);
void Draw6(vec3 location, float scale, int rotate, float textRed, float textGreen, float textBlue);
void Draw7(vec3 location, float scale, int rotate, float textRed, float textGreen, float textBlue);
void Draw8(vec3 location, float scale, int rotate, float textRed, float textGreen, float textBlue);
void Draw9(vec3 location, float scale, int rotate, float textRed, float textGreen, float textBlue);

NumberFunctionPointer NumberFunctions[] =
{
   Draw0,
   Draw1,
   Draw2,
   Draw3,
   Draw4,
   Draw5,
   Draw6,
   Draw7,
   Draw8,
   Draw9
};

using namespace std;
using namespace glm;


////////////////
// Globals :( //
////////////////

struct OBB {
   vec3 loc;
   float width;
   float height;
   float thick;
   vec3 pointUL;
   vec3 pointUR;
   vec3 pointLL;
   vec3 pointLR;
   int rotation;
   bool hit;
};

// Parameters
unsigned int const StepSize = 10;
int WindowWidth = 900, WindowHeight = 600;

// Meshes
unsigned int const MeshCount = 14;
Mesh * Meshes[MeshCount];
unsigned int CurrentMesh;

GLuint triBuffObj, colBuffObj, indxBuffObj, normBuffObj;
int TriangleCount;

// Variable Handles
GLuint aPosition;
GLuint aNormal;
GLuint uModelMatrix;
GLuint uNormalMatrix;
GLuint uViewMatrix;
GLuint uProjMatrix;
GLuint uColor;

//Light handles
//GLuint uLightPos;
GLuint udiffuse;
GLuint uspecular;
GLuint ushine;

//Object ints
int cube1 = 0;
int cube2 = 1;
int cyl1 = 2;
int cyl2 = 3;
int cyl3 = 4;
int disc1 = 5;
int disc2 = 6;
int sph1 = 7;
int sph2 = 8;
int sph3 = 9;
int sph4 = 10;
int tor1 = 11;
int tor2 = 12;
int tor3 = 13; 

// Shader Handle
GLuint ShadeProg;

//Ground Vars
GLuint GrndBuffObj, GIndxBuffObj;
int g_GiboLen;
static const float g_groundY = 0.0;      // y coordinate of the ground
static const float g_groundSize = 100.0;   // half the ground length

// Program Variables
float Accumulator = 0;
float CameraHeight;
float gameSpeed;
float gameScale = 1.0;
int incr = 0;
float xText = 0;
int lvlRange = 150;
int lvl1Start = 165;
int lvl2Start = lvl1Start + lvlRange + 30;
int lvl3Start = lvl2Start + lvlRange + 30;
float beginTextColor = 0.5;
float HUDmoveX = 0;
float HUDSpeed = .11;
float moveSpeed = .11;
float score = 0.0;
bool gameOver = false;
struct timeval tv;
float moveTimer = 0;
float moveStep = .1;
float oldTime = 0;
float scaledMove = 0;
bool gamePaused = false;

//View Vars
vec3 camLocation, camLook, upV;
vec3 v = vec3(0, 0, 0), u = vec3(0, 0, 0);
vec3 move = vec3(0, 0, 0);
float lookX = 0, lookY = 1.2, lookZ = 1;
float locX = 0, locY = 1.5, locZ = -1.5;
int rw = 0;
bool robotWalk = false;
float locRX = 0, locRY = .8, locRZ = 1.5, jumpR = 0;
int rotateR = 180;

float c_x = 0, c_y = 0, c_z = 0, c_alpha = 0, c_beta = 90 * 3.14159 / 180;
std::map<unsigned char, bool> state;


//Tree vars
std::map<int, float> treeFallMap;
std::map<int, float> treeFallMap2;
struct OBB TreeOBBs[treeNum];
float TreeHeight[treeNum];
float TreeLocX[treeNum];
float TreeLocZ[treeNum];
float TreeFallSpeed[treeNum];
float TreeFallLoc[treeNum];

//Player vars
struct OBB player;
float robotRed = 0.5;
float robotGreen = 0.5;
float robotBlue = 0.5;
bool jumpFlag = true;

//Life vars
int lives = 10;
struct OBB LifeOBB[lifeNum];
bool LifeF[lifeNum];
float LifeX[lifeNum];
float LifeZ[lifeNum];
bool lifeFlag = false;
int lifeUpDur = 0;

bool hitFlag =  false;
int hitDur = 0;
float speedUpDur = 0.0;

//Zomb vars
float Accum = 0;
struct OBB ZombOBBs[zombNum];
float ZombX[zombNum];
float ZombZ[zombNum];
float ZombSpeed[zombNum];
vec3 WallZomb[2];

//Grave vars
struct OBB GraveOBB1[graveNum1];
struct OBB GraveOBB2[graveNum2];
struct OBB GraveOBB3[graveNum3];
float Grave1X[graveNum1];
float Grave2X[graveNum2];
float Grave3X[graveNum3];
float Grave1Z[graveNum1];
float Grave2Z[graveNum2];
float Grave3Z[graveNum3];

//Windmill vars
struct OBB WindOBB1[windmillNum];
struct OBB WindOBB2[windmillNum];
float WindmillSpin[windmillNum];
float WindmillX[windmillNum];
float WindmillZ[windmillNum];

//Blade Vars
struct OBB BladeOBB[bladeNum];
float BladeX[bladeNum];
float BladeZ[bladeNum];
float BladeSpeed[bladeNum];
int BladeMoveDist[bladeNum];
float spin;

//Block Vars
struct OBB BlockOBB[blockNum];
float BlockX[blockNum];
float BlockZ[blockNum];
int BlockSpeed[blockNum];
float drop;
float cosDrop;

//Wall vars
vec3 WallL[wallNum];
vec3 WallR[wallNum];

RenderingHelper ModelTrans;
//vec3 lightPos = vec3(0, 2, -40);

//Funcs
void initGround();
void moveJump();
bool detectColsnXY(struct OBB object);
void DrawGrave3(vec3 location, int j);
void DrawGrave2(vec3 location, int j);
void DrawGrave1(vec3 location, int j);
void DrawZombie(vec3 location, float rotateY, float scaleAll, float walkSpeed, int j);
void DrawRobot();
void DrawLife(float x, float z);
void DrawTree(float x, float z, float height, int j);
void Initialize();
void initTrees();
void initWind();
void initBunny();
void initZombs();
void initGraves();
void initLives();
void SetModel();
