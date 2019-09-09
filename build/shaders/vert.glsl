#version 330 core
in vec3 a_vertices;
in vec3 a_normals;
uniform mat4 u_worldMatrix;
uniform mat4 u_location;
uniform mat4 u_rotation;
uniform vec3 u_camera;
out vec3 v_normals;
out vec4 v_color;
out vec3 v_surfaceToLight;
out vec3 v_camera;
void main () {
	v_color = vec4(a_vertices + vec3(0.5f), 1.0f);
	v_normals = mat3(u_worldMatrix) * a_normals;
	vec3 surface = (u_location * vec4(a_vertices, 1.0f)).xyz;
	v_surfaceToLight = (vec4(0.0f, 2.0f, -1.0f, 1.0f)).xyz - surface;
	v_camera = u_camera - surface;
	gl_Position = u_worldMatrix * vec4(a_vertices, 1.0f);
}