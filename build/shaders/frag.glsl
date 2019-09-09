#version 330 core
in lowp vec4 v_color;
in lowp vec3 v_normals;
in lowp vec3 v_surfaceToLight;
in lowp vec3 v_camera;
out highp vec4 color;
void main () {
	vec3 normals = normalize(v_normals);
	
	vec3 surfaceToLight = normalize(v_surfaceToLight);
	vec3 camera = normalize(v_camera);
	vec3 halfVector = normalize(surfaceToLight + camera);
	
	float light = dot(normals, surfaceToLight);
	float specular = 0.0f;
	if (light > 0.0f) {
		specular = pow(dot(normals, halfVector), 150.0f);
	}
	
	color = vec4(vec3(0.5f), 1.0f);
	color.rgb *= light;
	color.rgb += specular;
}