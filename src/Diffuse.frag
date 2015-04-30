#version 120

uniform sampler2DShadow shadowTexture;
uniform sampler2D modelTexture;
uniform vec3 lightColor;
uniform int skyBox;

varying vec4 shadowPosition;
varying vec3 vPosition;
varying vec3 cameraInverse;
varying vec3 cameraLightPos;
varying vec3 vNormal;
varying vec3 vColor;
varying vec2 textureUV;

vec2 poissonDisk[16] = vec2[](
                              vec2( -0.94201624, -0.39906216 ),
                              vec2( 0.94558609, -0.76890725 ),
                              vec2( -0.094184101, -0.92938870 ),
                              vec2( 0.34495938, 0.29387760 ),
                              vec2( -0.91588581, 0.45771432 ),
                              vec2( -0.81544232, -0.87912464 ),
                              vec2( -0.38277543, 0.27676845 ),
                              vec2( 0.97484398, 0.75648379 ),
                              vec2( 0.44323325, -0.97511554 ),
                              vec2( 0.53742981, -0.47373420 ),
                              vec2( -0.26496911, -0.41893023 ),
                              vec2( 0.79197514, 0.19090188 ),
                              vec2( -0.24188840, 0.99706507 ),
                              vec2( -0.81409955, 0.91437590 ),
                              vec2( 0.19984126, 0.78641367 ),
                              vec2( 0.14383161, -0.14100790 )
                              );

// Returns a random number based on a vec3 and an int.
float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

void main() {
   float lightPower = 1.0f;
   float shine = 100000000.0f;
   int index = 0;
   
   vec3 MaterialDiffuseColor = vColor * texture2D(modelTexture, textureUV).rgb;
   float alpha =texture2D(modelTexture, textureUV).a;
   
   if (alpha < 0.5) {
      discard;
   }
   
   vec3 MaterialAmbientColor = vec3(0.4, 0.4, 0.4) * MaterialDiffuseColor;
   vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);
   
   if (skyBox == 0) {
      vec3 N = normalize(vNormal);
      vec3 L = normalize(cameraLightPos);
      
      float cosTheta = clamp(dot(N, L), 0, 1);

      vec3 V = normalize(cameraInverse);
      vec3 R = reflect(-L, N);

      float cosAlpha = clamp(dot(V, R), 0, 1);
      
      float visibility = 1.0;

      float bias = 0.005 * tan(acos(cosTheta));
      bias = clamp(bias, 0, 0.01);

      for (int i = 0; i < 4; i++) {
         index = i;

         //index = int(mod(16.0*random(floor(vPosition.xyz*1000.0), i), 16.0));


         visibility -= 0.2*(1.0-shadow2D(shadowTexture, vec3(shadowPosition.xy + poissonDisk[index]/700.0 ,  (shadowPosition.z-bias)/shadowPosition.w)).r);
      }
      gl_FragColor = vec4(MaterialAmbientColor +
			  visibility * MaterialDiffuseColor * lightColor * lightPower * cosTheta +
			  visibility * MaterialSpecularColor * lightColor * lightPower * pow(cosAlpha, shine), alpha);
   }
   else if (skyBox == 1) {
      gl_FragColor = vec4(MaterialDiffuseColor * lightColor, 1);
   }
}