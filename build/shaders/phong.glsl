#version 330 core
in lowp vec4 v_color;
in lowp vec3 v_normal;
in lowp vec3 v_fragPos;
in lowp vec3 v_cameraPos;
out highp vec4 color;
float rand(vec2 co) {
	return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}
void main () {
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 objectColor = vec3(1.0f, 0.2f, 0.2f);
	float ambientStrength = 0.1f;
	float specularStrength = 1.0f;
	float metallic = 128;
	float randStrength = 0.5f;
	
	vec3 normal = normalize(vec3(v_normal.x + rand(v_fragPos.xy) * randStrength, v_normal.y + rand(v_fragPos.yz) * randStrength, v_normal.z + rand(v_fragPos.xz) * randStrength));
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 1.0f) - v_fragPos);
	
	vec3 ambient = ambientStrength * lightColor;
	vec3 diffuse = max(dot(normal, lightDirection), 0.0f) * lightColor;
	
	vec3 viewDir = normalize(v_cameraPos - v_fragPos);
	
	vec3 halfVector = normalize(lightDirection + viewDir);
	vec3 specular = specularStrength * pow(max(dot(normal, halfVector), 0.0), metallic) * lightColor;
	
	vec3 light = (diffuse) * objectColor;
	
	color = vec4(light, 1.0f);
}