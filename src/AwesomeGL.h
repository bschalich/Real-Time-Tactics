#ifndef __AwesomeGL__
#define __AwesomeGL__

// This must be at the top on Windows
class Combatant;
class Tween;
class ParticleEmitter;
class Font;
class Billboard;
class Camera;
class ActiveHeroIcon;

#include "GLSL_helper.h"

#include <png.h>

#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "MStackHelp.h"

#include <random>
#include <vector>
#include <list>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>

#include "Font.h"
#include "Tween.h"
#include "ParticleEmitter.h"

#define PI 3.14159265358979323846
#define TILE_SIZE 10
#define NUM_BONES 16
#define MAX_BONES 2
#define PROJ_SPEED 4000
#define ARCHER_RANGE 60
#define MAGE_RANGE 40

#define WARRIOR_SPEED 20
#define ARCHER_SPEED 20
#define MAGE_SPEED 20

#define MAGE_AOE 20

#define WARRIOR_LOOK_RANGE 50
#define ARCHER_LOOK_RANGE 50
#define MAGE_LOOK_RANGE 50

#define WARRIOR_SPECIAL_SPEED 5

#define TEXTURE_LOAD_ERROR 0

class GameMap;

class Entity;

typedef struct Image {
   unsigned long sizeX;
   unsigned long sizeY;
   char *data;
} Image;

struct OBB {
   glm::vec3 max;
   glm::vec3 min;
};

typedef struct Plane
{
   float a, b, c, d;
}Plane;


typedef std::pair<double, glm::mat4 *> keyframe_t;

typedef struct Model {
   GLuint modelVert;
   GLuint modelIndex;
   GLuint modelNormal;
   int    modelNumVert;
   GLuint modelUV;
   GLuint modelBoneIndex;
   GLuint modelBoneWeight;
   std::vector<std::vector<keyframe_t> > frames;
} Model;

struct point {
	GLfloat x;
	GLfloat y;
	GLfloat s;
	GLfloat t;
};

struct atlas;

namespace AwesomeGL {
   
   enum Combatant_Type{WARRIOR, ARCHER, MAGE};
   enum Projectile_State{MOVING, ATTACHED, ATTACHED_IO};
   //only used for archers/projectiles
   enum AttackType {SPECIAL, NORMAL};
   // Model transformation helper
   extern RenderingHelper ModelTrans;		
   extern Image *TextureImage;

   // Create a clock for measuring the time elapsed
   extern sf::Clock *clock;
   extern sf::Clock *deltaClock;
   extern sf::Time deltaTime;
   
   // SFML Window
   extern sf::Window *window;
   
   //Billboard Shader handles
   extern GLuint h_billboard;
   extern GLuint h_CameraRight;
   extern GLuint h_CameraUp;
   extern GLuint h_ViewProjMatrix;
   extern GLuint h_BillboardPos;
   extern GLuint h_BillboardSize;
   extern GLuint h_LifeLevel;
   extern GLuint h_BillboardTexture;
   extern GLuint h_BillboardSquareVertices;
   extern GLuint Texture;
   
   //ActiveHeroIcon Shader handles
   extern GLuint h_icon;
   extern GLuint h_CameraRightIcon;
   extern GLuint h_CameraUpIcon;
   extern GLuint h_ViewProjMatrixIcon;
   extern GLuint h_IconPos;
   extern GLuint h_IconSize;
   extern GLuint h_IconTexture;
   extern GLuint h_IconSquareVertices;
   extern GLuint IconTexture;
   
   // Shader handles
   extern GLuint h_shadeProg;
   extern GLuint h_aPosition;
   extern GLuint h_projectionMatrix;
   extern GLuint h_viewMatrix;
   extern GLuint h_modelMatrix;
   extern GLuint h_uColor;
   extern GLuint h_aNormal;
   extern GLuint h_shadeProg;
   extern GLuint h_MVP;
   extern GLuint h_shadowBiasMVP;
   extern GLuint h_shadowTexture;
   extern GLuint h_UV;
   extern GLuint h_shadowFlag;
   extern GLuint h_M_inv_trans;
   extern GLuint h_lightPos;
   extern GLuint h_MVP;
   extern GLuint h_modelTexture;
   extern GLuint h_aUV;
   extern GLuint h_lightColor;
   extern GLuint h_skyBox;
   
   // animation
   extern GLuint h_aBoneIndexs;
   extern GLuint h_aBoneWeights;
   extern GLuint h_uBones;

   //Shadow stuff
   extern GLuint shadow_FBO;
   extern GLuint shadowTexture;
   extern GLint shadowFlag;
   extern int shadowSize;
   extern bool renderShadowFlag;
   
   //Shadow handles
   extern GLuint h_shadowProg;
   extern GLuint h_shadowMatrix;
   extern GLuint h_shadowModelPosition;
   extern GLuint h_texture;
   extern GLuint h_shadowModelTexture;
   extern GLuint h_shadowUV;
   extern GLuint h_shadowBoneWeights;
   extern GLuint h_shadowBoneIndexs;
   extern GLuint h_shadowBones;
   
   //Font shader
   extern GLuint h_FontProg;
   extern GLuint h_coord;
   extern GLuint h_tex;
   extern GLuint h_color;
   
   //Particle shader
   extern GLuint h_particleProg;
   extern GLuint h_particleTex;
   extern GLuint h_viewProjMatrix;
   extern GLuint h_cameraUp_worldspace;
   extern GLuint h_cameraRight_worldspace;
   extern GLuint h_squareVertices;
   extern GLuint h_xyzs;
   extern GLuint h_particleColor;
   
   //Bloom shaders
   extern GLuint bloom_FBO;
   extern GLuint bloomTexture;
   extern GLuint depthBuffer;

   extern glm::vec3 lightPos;
   extern glm::vec3 lightColor;
   extern glm::vec3 zoomFactor;
   extern glm::vec3 cameraPos;
   //extern glm::vec3 tilePos;
   
   extern GLuint CubeBuffObj;
   extern GLuint CIndxBuffObj;
   extern GLuint CubeNormalBuffObj;
   extern GLuint TexBuffObj;
   extern int g_CiboLen;

   extern std::vector<ParticleEmitter*> particleList;
   extern std::vector<Entity*> entityList;
   extern std::vector<Entity*> tileList;
   extern std::vector<Combatant*> cList;
   extern std::vector<Combatant*> heroList;
   extern std::vector<Combatant*> enemyList;
   extern std::vector<Combatant*> projectileList;
   extern std::vector<Tween*> tweenList;
   extern std::vector<Billboard*> billboardList;
   extern std::vector<ActiveHeroIcon*> ahIconList;
   
   extern Model model_warrior;
   extern Model model_tile;
   extern Model model_tree3;
   extern Model model_ranged;
   extern Model model_caster;
   extern Model model_arrow;
   extern Model model_stone;
   extern Model model_flower;
   extern Model model_grass;

   extern Camera *camera;

   extern Combatant *activeHero;
   extern unsigned int activeHeroIndex;
   
   extern GameMap *map;
   
   extern std::unordered_map<std::string, GLuint*> texMap;
   extern std::unordered_map<std::string, Model> modelMap;
   
   extern GLuint tex_warrior;
   extern GLuint tex_grid;
   extern GLuint tex_yellow;
   extern GLuint tex_stone;
   extern GLuint tex_ranged;
   extern GLuint tex_caster;
   extern GLuint tex_arrow;
   extern GLuint tex_skybox;
   extern GLuint tex_tree3;
   extern GLuint tex_redwood;
   extern GLuint tex_flower;
   extern GLuint tex_grass;
   extern GLuint tex_star;
   
   extern sf::SoundBuffer warriorAttackSoundBuffer;
   extern sf::SoundBuffer archerAttackSoundBuffer;
   extern sf::SoundBuffer mageAttackSoundBuffer;
   extern sf::SoundBuffer arrowHitSoundBuffer;
   
   extern sf::SoundBuffer deathSoundBuffer;
   extern sf::SoundBuffer startSound;
   extern sf::SoundBuffer endSound;
   extern sf::SoundBuffer music;
   extern sf::SoundBuffer tauntSoundBuffer;
   
   extern sf::Sound start;
   extern sf::Sound warriorAttackSound;
   extern sf::Sound archerAttackSound;
   extern sf::Sound mageAttackSound;
   extern sf::Sound arrowShotSound;
   extern sf::Sound arrowHitSound;
   extern sf::Sound deathSound;
   extern sf::Sound tauntSound;
   extern sf::SoundBuffer bgSoundBuffer;
   extern sf::Sound bgSound;
   

   
   extern sf::Sound musicSound;
   extern sf::Sound endMusic;
   
   
   extern sf::Clock *colorTimer;

   extern OBB boundingBox;

   extern glm::mat4 biasMatrix;
   extern glm::mat4 shadowProjectionMatrix;
   extern glm::mat4 shadowViewMatrix;
   extern glm::mat4 shadowMVP;
   extern glm::mat4 getProjectionMatrix();
   extern glm::mat4 getViewMatrix();
   extern glm::mat4 getModelMatrix();
   extern glm::mat4 projectionMatrix;
   extern glm::mat4 viewMatrix;

   extern std::random_device rd;
   extern std::mt19937 mt;

   extern int score;
   
   extern glm::vec3 lightDir;
   extern float lightSpeed;
   
   extern GLuint fontVBO;
   extern FT_Face arialFace;
   extern FT_Face oldLondonFace;
   extern FT_Face erinFace;
   extern Font *arial32;
   extern Font *arial48;
   extern Font *arial96;
   extern Font *arial250;
   extern Font *oldLondon32;
   extern Font *swordsman32;
   extern Font *erin32;
   extern Font *erin250;

   extern int png_texture_load(const char * file_name, int * width, int * height, int texid);
   extern void addParticle(ParticleEmitter *p);
   extern void removeParticle(ParticleEmitter *p);
   extern void addTween(Tween *tween);
   extern void removeTween(Tween *tween);
   extern void setUpModels();
   extern void setUpTextures();
   extern void initCube();
   extern void initGround();
   extern void drawSkyBox();
   extern GLvoid loadTexture_BMP(char* image_file, int tex_id);
   extern GLuint loadTexture_PNG(const std::string filename, int &width, int &height);
   extern void cleanUp();
   extern void removeEntity(Entity* entity);
   extern void addEntity(Entity* entity);
   extern void removeTile(Entity* entity);
   extern void addTile(Entity* entity);
   extern void addCombatant(Combatant *combatant);
   extern void removeCombatant(Combatant *combatant);
   extern void removeEnemy(Combatant *enemy);
   extern void Update();
   extern bool initGL();
   extern bool setUpShaders();
   extern void renderBillboards();
   extern void addBillboard(Billboard *billboard);
   extern void removeBillboard(Billboard *billboard);
   extern void addAHIcon(ActiveHeroIcon *ahIcon);
   extern void removeAHIcon(ActiveHeroIcon *ahIcon);
   
   /*void extractPlanesGL(Plane *planes, bool normalize);
   bool checkInside(Plane *planes, glm::vec3 pos);*/
   bool objectVisible(glm::mat4 MVPMatrix, float xPos, float, float);
   extern void removeHero(Combatant* hero);
   int loadSingleMesh(const char *filename, GLuint &vertBuff, GLuint &indexBuff, GLuint &normalBuff, GLuint &uvBuff);
   int loadSingleMesh(const char *filename,
                      GLuint &vertBuff,
                      GLuint &indexBuff,
                      GLuint &normalBuff,
                      GLuint &uvBuff,
                      GLuint &boneIndex,
                      GLuint &boneWeight,
                      std::vector<std::vector<keyframe_t> > &p_frames);
   extern bool InstallShader(std::string const & vShaderName, std::string const & fShaderName, GLuint *prog);
   extern void renderText(const char *text, Font *a, float x, float y, float sx, float sy);
   extern bool initShadowFBO();
   extern bool initBloomFBO();
   extern glm::mat4 getShadowViewMatrix();
   extern glm::mat4 getShadowProjectionMatrix();
   extern void setWin(); 
   extern void renderHUD();
}

#endif
