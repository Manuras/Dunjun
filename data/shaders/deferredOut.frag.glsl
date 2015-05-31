#version 120

uniform sampler2D u_diffuse;
uniform sampler2D u_lighting;

varying vec2 v_texCoord;

void main()
{
	vec3 diffuseColor  = texture2D(u_diffuse,  v_texCoord).rgb;
	vec3 lightingColor = texture2D(u_lighting, v_texCoord).rgb;

	vec3 finalColor = diffuseColor * lightingColor;
	vec3 gamma = vec3(1.0/2.2);

	gl_FragColor = vec4(pow(finalColor, gamma), 1.0);
}
