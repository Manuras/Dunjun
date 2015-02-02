#version 120

uniform sampler2D uniTex;

varying vec3 fragColor;
varying vec2 fragTexCoord;

void main()
{
	vec3 texColor = texture2D(uniTex, fragTexCoord).rgb;
	gl_FragColor = vec4(texColor * fragColor, 1.0);
}