#version 120

#include <Common.head.glsl>
#include <Material.head.glsl>

uniform vec3 u_cameraPosition;
uniform Transform u_transform;

uniform Material u_material;

varying vec3 v_position_ws;

varying vec3 v_position;
varying vec2 v_texCoord;
varying vec3 v_color;
varying vec3 v_normal;

void main()
{
	vec4 texColor = texture2D(u_material.diffuseMap, v_texCoord).rgba;
	if (texColor.a < 0.5)
		discard;

	vec3 surfaceColor = u_material.diffuseColor.rgb * texColor.rgb * v_color;

	vec3 normal =
	    normalize(quaternionRotate(u_transform.orientation, v_normal));

	gl_FragData[0].rgb = surfaceColor.rgb;
	gl_FragData[1].rgb = u_material.specularColor.rgb;
	gl_FragData[2].xyz = 0.5 * (normal + vec3(1.0));
}
