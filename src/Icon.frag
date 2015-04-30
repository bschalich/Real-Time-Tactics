#version 120
varying vec2 UV;

uniform sampler2D myTextureSampler;

void main(){
	gl_FragColor = texture2D(myTextureSampler, UV);
	
	if (UV.y > 0.3 && UV.y < 0.7 && UV.x > 0.04 )
		gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}