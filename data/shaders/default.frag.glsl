#version 120

uniform sampler2D u_tex;

varying vec3 v_color;
varying vec2 v_texCoord;

void main()
{
	vec3 texColor = texture2D(u_tex, v_texCoord).rgb;
	vec3 gamma = vec3(1.0 / 2.2);
	vec3 color = texColor * v_color;

	gl_FragColor = vec4(pow(color, gamma), 1.0);
}
