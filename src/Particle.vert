#version 120

attribute vec3 squareVertices;
attribute vec4 xyzs;
attribute vec4 color;

varying vec2 UV;
varying vec4 particlecolor;

uniform vec3 camRight;
uniform vec3 camUp;
uniform mat4 VP;

void main()
{
	float particleSize = xyzs.w;
	vec3 particleCenter = xyzs.xyz;
	
	vec3 vPosition = particleCenter
   + camRight * squareVertices.x * particleSize
   + camUp * squareVertices.y * particleSize;
   
	gl_Position = VP * vec4(vPosition, 1.0f);
   
	UV = squareVertices.xy + vec2(0.5, 0.5);
	particlecolor = color;
}

