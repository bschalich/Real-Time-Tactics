#version 120

attribute vec3 aPosition;
attribute vec3 aNormal;
attribute vec2 aUV;

attribute vec2 aBoneIndexes;
attribute vec2 aBoneWeights;

uniform mat4 V;
uniform mat4 M;
uniform vec3 color;
uniform mat4 shadowBiasMVP;
uniform mat3 M_inv_trans;
uniform vec3 lightPos;
uniform mat4 MVP;

uniform mat4 uBones[16];

varying vec4 shadowPosition;
varying vec3 vPosition;
varying vec3 cameraInverse;
varying vec3 cameraLightPos;
varying vec3 vNormal;
varying vec3 vColor;
varying vec2 textureUV;


void main() {
   vec4 Vertex = vec4(aPosition, 1.0);
   vec4 Normal = vec4(aNormal, 0.0);
   int boneIndex1 = int(aBoneIndexes.x);
   int boneIndex2 = int(aBoneIndexes.y);
   
   mat4 Trans = mat4(1.0) * (1.0 - aBoneWeights.x - aBoneWeights.y);
   Trans += uBones[boneIndex1] * aBoneWeights.x;
   Trans += uBones[boneIndex2] * aBoneWeights.y;
   
   Vertex = (Trans * Vertex);
   Normal = (Trans * Normal);

   shadowPosition = shadowBiasMVP * Vertex;
   vPosition = (M * Vertex).xyz;
   cameraInverse = vec3(0, 0, 0) - (V * Vertex).xyz;
   cameraLightPos = (V * vec4(lightPos, 0)).xyz;
   vNormal = (V * mat4(M_inv_trans) * Normal).xyz;
   textureUV = aUV;
   vColor = color;
   //vColor = vec3(aBoneWeights.x, aBoneWeights.y, 1.0 - aBoneWeights.x - aBoneWeights.y);
   //vColor = vec3(boneIndex1 / 16.0, mod(boneIndex1, 4) / 4.0, mod(boneIndex1, 2) / 2.0);
   
   gl_Position = MVP * Vertex;
}