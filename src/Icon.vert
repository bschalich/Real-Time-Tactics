#version 120
attribute vec3 squareVertices;

varying vec2 UV;

uniform vec3 CameraRight_worldspace;
uniform vec3 CameraUp_worldspace;
uniform mat4 VP;
uniform vec3 IconPos;
uniform vec2 IconSize;

void main()
{
	vec3 particleCenter_wordspace = IconPos;
	
	vec3 vertexPosition_worldspace =
   particleCenter_wordspace
   + CameraRight_worldspace * squareVertices.x * IconSize.x
   + CameraUp_worldspace * squareVertices.y * IconSize.y;
   
	gl_Position = VP * vec4(vertexPosition_worldspace, 1.0f);
   
	UV = squareVertices.xy + vec2(0.5, 0.5);
}
