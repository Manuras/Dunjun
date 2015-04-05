#version 120

struct Material
{
	sampler2D diffuseMap;
	vec4 diffuseColor;

	vec4 specularColor;
	float specularExponent;
};

struct Attenuation
{
	float constant;
	float linear;
	float quadratic;
};

struct PointLight
{
	vec3 position;
	vec3 intensities; // color * brightness
	Attenuation attenuation;

	float range;
};

struct Transform
{
	vec3 position;
	vec4 orientation;
	vec3 scale;
};

vec3 quaternionRotate(vec4 q, vec3 v)
{
	vec3 t = 2.0 * cross(q.xyz, v);
	return (v + q.w * t + cross(q.xyz, t));
}

uniform vec3 u_cameraPosition;
uniform Transform u_transform;


uniform Material u_material;

uniform PointLight u_light;

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
	vec3 surfaceToLight = normalize(u_light.position - v_position_ws);
	float distanceToLight = length(u_light.position - v_position_ws);

	float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));

	float specularCoefficient = 0.0;

	vec3 surfaceToCamera = normalize(u_cameraPosition - v_position_ws);

	if (diffuseCoefficient > 0.0)
	{
		specularCoefficient = pow(
		    max(0.0, dot(surfaceToCamera, reflect(-surfaceToLight, normal))),
		    u_material.specularExponent);
	}

	float attenuation =
	    u_light.attenuation.constant +
	    u_light.attenuation.linear * distanceToLight +
	    u_light.attenuation.quadratic * distanceToLight * distanceToLight;
	attenuation = 1.0 / attenuation;


	attenuation *=
	    clamp(pow(1 - pow(distanceToLight / u_light.range, 4.0), 2.0), 0, 1);

	vec3 diffuse = diffuseCoefficient * u_light.intensities.rgb;
	vec3 specular = specularCoefficient * u_light.intensities.rgb * u_material.specularColor.rgb;

	vec3 finalColor =
	    (diffuse.rgb + specular.rgb) * attenuation * surfaceColor.rgb;

	vec3 gamma = vec3(1.0 / 2.2);
	gl_FragColor = vec4(pow(finalColor, gamma), 1.0);
}
