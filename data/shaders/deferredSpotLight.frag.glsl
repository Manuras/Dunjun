#version 120

#include <Lighting.head.glsl>

uniform sampler2D u_specular;
uniform sampler2D u_normal;
uniform sampler2D u_depth;

uniform mat4 u_cameraInverse;

uniform SpotLight u_light;

varying vec2 v_texCoord;


vec4 calculateSpotLight(float lightToSurfaceAngle,
                        vec3 surfaceToLight,
                        float distanceToLight,
                        vec3 normal)
{
	float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));

	float attenuation =
	    u_light.point.attenuation.constant +
	    u_light.point.attenuation.linear * distanceToLight +
	    u_light.point.attenuation.quadratic * distanceToLight * distanceToLight;
	attenuation = 1.0 / attenuation;

	attenuation *= clamp(
	    square(1.0 - (square(distanceToLight / u_light.point.range))), 0.0, 1.0);

	// TODO(bill): More efficient looking spotlight fading
	attenuation *= clamp(
	    square(1.0 - pow((lightToSurfaceAngle / u_light.coneAngle), 10.0)), 0.0, 1.0);

	vec4 diffuse = vec4(0.0);

	diffuse.rgb = diffuseCoefficient * u_light.point.base.intensities.rgb * attenuation;
	diffuse.a = 1.0;

	return diffuse;
}

void main()
{
	vec3 specularColor = texture2D(u_specular, v_texCoord).rgb;
	vec3 normalEncoded = texture2D(u_normal, v_texCoord).xyz;
	float depth = texture2D(u_depth, v_texCoord).r;

	vec3 position = calculatePositionFromDepth(v_texCoord, gl_FragCoord.w, depth, u_cameraInverse);
	vec3 normal = normalize(2.0 * normalEncoded - vec3(1.0));

	vec3 surfaceToLight = normalize(u_light.point.position - position);
	float distanceToLight = length(u_light.point.position - position);
	float lightToSurfaceAngle = acos(dot(-surfaceToLight, normalize(u_light.direction)));

	vec4 lightColor =
	    calculateSpotLight(lightToSurfaceAngle, surfaceToLight, distanceToLight, normal);

	gl_FragColor = lightColor;
}
