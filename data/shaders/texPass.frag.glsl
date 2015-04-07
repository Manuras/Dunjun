#version 120

uniform sampler2D u_tex;

varying vec2 v_texCoord;

void main()
{
	vec4 texColor = texture2D(u_tex, v_texCoord);

	gl_FragColor = texColor;
}
