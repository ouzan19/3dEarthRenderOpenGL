#version 120

uniform sampler2D hmap;
varying vec2 texture_coordinate;
uniform float displevel;
uniform sampler2D texturemap;

varying vec3 Norm;
varying vec3 ToLight;
varying vec4 Position;

void main()
{
    vec4 color = texture2D(texturemap,texture_coordinate);
    
  vec3 norm = normalize(Norm);
	// Light vector
	vec3 lightv = normalize(ToLight);
	vec3 viewv = -normalize(Position.xyz);
	vec3 halfv = normalize(lightv + viewv);
	/* diffuse reflection */
	vec4 diffuse = max(0.0, dot(lightv, norm))*vec4(1,1,1,1);

	/* ambient reflection */

	vec4 ambient = vec4(0.25,0.25,0.25,1)*vec4(0.3,0.3,0.3,1);

	/* specular reflection */
	vec4 specular = vec4(0.0, 0.0, 0.0, 1.0);
	if( dot(lightv, viewv) > 0.0) {
		specular = pow(max(0.0, dot(norm, halfv)),100)*vec4(1,1,1,1);
	}
	vec3 c = clamp( vec3(ambient + diffuse + specular), 0.0, 1.0);

	gl_FragColor = color*vec4(c,1);
	
}
