#version 120

#include <Lighting.head.glsl>

uniform sampler2D u_specular;
uniform sampler2D u_normal;

uniform DirectionalLight u_light;

varying vec2 v_texCoord;

vec4 calculateDirectionalLight(DirectionalLight light, vec3 normal)
{
	float diffuseCoefficient = max(0.0, dot(normal, -light.direction));

	vec4 diffuse = vec4(0.0);

	diffuse.rgb = diffuseCoefficient * light.base.intensities.rgb;
	diffuse.a = 1.0;

	return diffuse;
}

void main()
{
	vec3 specularColor = texture2D(u_specular, v_texCoord).rgb;
	vec3 normalEncoded = texture2D(u_normal, v_texCoord).xyz;

	vec3 normal = normalize(2.0 * normalEncoded - vec3(1.0));

	vec4 lightColor = calculateDirectionalLight(u_light, normal);

	gl_FragColor = lightColor;
}
