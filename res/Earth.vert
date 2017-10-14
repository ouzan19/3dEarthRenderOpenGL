#version 120
uniform sampler2D texturemap;
uniform sampler2D hmap;
varying vec2 texture_coordinate;
uniform float displevel; 
varying vec3 Norm;
varying vec3 ToLight;
varying vec4 Position;
uniform float ex;
uniform float ez;
uniform mat4 MW;

void main()
{
   texture_coordinate =vec2(gl_MultiTexCoord0);
  
 
	vec4 height =texture2D(hmap,texture_coordinate);
   vec3 N = normalize(gl_Normal);
   vec4 new_position = gl_Vertex + vec4(N*height.r*displevel,0);
   
   
   gl_Position = gl_ModelViewProjectionMatrix * new_position;
   
   
  Norm = gl_NormalMatrix * gl_Normal; 
  ToLight = vec3(MW*vec4(0,0,0,1) - (gl_ModelViewMatrix * new_position));
  Position = gl_ModelViewMatrix * new_position;
    
}
