#version 120

varying vec2 UV;
varying vec4 particlecolor;

uniform sampler2D particleTex;

void main(){
   vec4 tex = texture2D( particleTex, UV );
   float alpha = tex.a;
   
   if (alpha < 0.2) {
      discard;
   }
	gl_FragColor = tex * particlecolor;
   
}