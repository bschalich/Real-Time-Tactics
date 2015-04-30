#version 120

attribute vec3 shadowModelPosition;
attribute vec2 aUV;
attribute vec2 aBoneIndexes;
attribute vec2 aBoneWeights;

varying vec2 textureUV;

uniform mat4 shadowMVP;
uniform mat4 uBones[16];


void main(){
   textureUV = aUV;
   
   vec4 Vertex = vec4(shadowModelPosition, 1.0);
   int boneIndex1 = int(aBoneIndexes.x);
   int boneIndex2 = int(aBoneIndexes.y);
   
   
   //mat4 Trans = mat4(1.0) * (1.0 - aBoneWeights.x - aBoneWeights.y);
   //Trans += uBones[boneIndex1] * aBoneWeights.x;
   //Trans += uBones[boneIndex2] * aBoneWeights.y;
   
   //Vertex = (Trans * Vertex);
   
	gl_Position = shadowMVP * Vertex;
}

