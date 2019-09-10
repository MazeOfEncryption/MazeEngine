#version 330 core
in lowp vec4 v_color;
in lowp vec3 v_normal;
in lowp vec3 v_fragPos;
in lowp vec3 v_cameraPos;
out highp vec4 color;
void main () {
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 objectColor = vec3(1.0f, 0.2f, 0.2f);
	float ambientStrength = 0.1f;
	float specularStrength = 0.5f;
	float metallic = 32;
	
	vec3 normal = normalize(v_normal);
	vec3 lightDirection = normalize(vec3(0.2f, 1.0f, 0.3f) - v_fragPos);
	
	vec3 ambient = ambientStrength * lightColor;
	vec3 diffuse = max(dot(normal, lightDirection), 0.0f) * lightColor;
	
	vec3 viewDir = normalize(v_cameraPos - v_fragPos);
	vec3 reflectDir = reflect(-lightDirection, normal);  
	vec3 specular = specularStrength * pow(max(dot(viewDir, reflectDir), 0.0), metallic) * lightColor;
	
	vec3 light = (ambient + diffuse + specular) * objectColor;
	
	color = vec4(light, 1.0f);
}