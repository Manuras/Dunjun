#version 120

attribute vec2 vertPosition;
attribute vec3 vertColor;
attribute vec2 vertTexCoord;

varying vec3 fragColor;
varying vec2 fragTexCoord;

void main()
{
	fragColor = vertColor;
	fragTexCoord = vec2(vertTexCoord.s, 1.0 - vertTexCoord.t);
	gl_Position = vec4(vertPosition, 0.0, 1.0);
}