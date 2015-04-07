#version 120

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

uniform sampler2D u_diffuse;
uniform sampler2D u_specular;
uniform sampler2D u_normal;
uniform sampler2D u_depth;

uniform mat4 u_cameraInverse;

uniform PointLight u_light;

varying vec2 v_texCoord;

float square(float x) { return x; }

vec3 calculatePositionFromDepth(float depth)
{
	float x_hs = 2.0 * v_texCoord.x - 1.0;
	float y_hs = 2.0 * v_texCoord.y - 1.0;
	float z_hs = 2.0 * depth - 1.0;

	vec4 position_hs = vec4(x_hs, y_hs, z_hs, 1.0) / gl_FragCoord.w;

	vec4 position_ws = u_cameraInverse * position_hs;

	return position_ws.xyz / position_ws.w;
}

vec4 calculatePointLight(vec3 surfaceToLight,
                         float distanceToLight,
                         vec3 normal)
{
	float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));

	float attenuation =
	    u_light.attenuation.constant +
	    u_light.attenuation.linear * distanceToLight +
	    u_light.attenuation.quadratic * distanceToLight * distanceToLight;
	attenuation = 1.0 / attenuation;

	attenuation *= clamp(
	    square(1.0 - (square(distanceToLight / u_light.range))), 0, 1);

	vec4 diffuse = vec4(0.0);

	diffuse.rgb = diffuseCoefficient * u_light.intensities.rgb * attenuation;
	diffuse.a = 1.0;

	return diffuse;
}

void main()
{
	vec3 diffuseColor = texture2D(u_diffuse, v_texCoord).rgb;
	vec3 specularColor = texture2D(u_specular, v_texCoord).rgb;
	vec3 normalEncoded = texture2D(u_normal, v_texCoord).xyz;
	float depth = texture2D(u_depth, v_texCoord).r;

	vec3 position = calculatePositionFromDepth(depth);
	vec3 normal = normalize(2.0 * normalEncoded - vec3(1.0));

	vec3 surfaceToLight = normalize(u_light.position - position);
	float distanceToLight = length(u_light.position - position);

	vec4 lightColor =
	    calculatePointLight(surfaceToLight, distanceToLight, normal);

	vec3 gamma = vec3(1.0 / 2.2);
	gl_FragColor = vec4(pow(diffuseColor * lightColor.rgb, gamma), 1.0);
}
