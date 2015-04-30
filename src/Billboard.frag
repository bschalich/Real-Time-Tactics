#version 120

varying vec2 UV;

uniform sampler2D myTextureSampler;

uniform float LifeLevel;

void main(){
	gl_FragColor = texture2D(myTextureSampler, UV);
	
	if (UV.y > 0.3 && UV.y < 0.7 && UV.x > 0.04 )
		gl_FragColor = vec4(0.2, 0.8, 0.2, 1.0);
}