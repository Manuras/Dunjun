#version 120

uniform sampler2D uniTex;

varying vec3 fragColor;
varying vec2 fragTexCoord;

void main()
{
	vec3 texColor = texture2D(uniTex, fragTexCoord).rgb;
	vec3 gamma = vec3(1.0 / 2.2);
	vec3 color = texColor * fragColor;

	gl_FragColor = vec4(pow(color, gamma), 1.0);
}