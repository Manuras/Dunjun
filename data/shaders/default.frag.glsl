#version 120

uniform sampler2D u_tex;

varying vec2 v_texCoord;
varying vec3 v_color;

void main()
{
	vec4 texColor = texture2D(u_tex, v_texCoord).rgba;
	if (texColor.a < 0.5)
		discard;

	vec3 gamma = vec3(1.0 / 2.2);
	vec3 color = texColor.rgb * v_color;

	gl_FragColor = vec4(pow(color, gamma), 1.0);
}
