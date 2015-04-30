#version 120

uniform sampler2D modelTexture;
varying vec2 textureUV;

void main(){
   float alpha = texture2D(modelTexture, textureUV).a;
   if (alpha < 0.5) {
      discard;
   }
	gl_FragDepth = gl_FragCoord.z;
}