#version 330 core
in vec3 a_vertices;
in vec3 a_normals;
uniform mat4 u_worldMatrix;
uniform mat4 u_rotation;
uniform mat4 u_view;
uniform vec3 u_camera;
out vec3 v_normal;
out vec4 v_color;
out vec3 v_fragPos;
out vec3 v_cameraPos;
void main () {
	v_color = vec4(a_vertices + vec3(0.5f), 1.0f);
	v_normal = a_normals;
	
	v_fragPos = a_vertices;
	v_cameraPos = u_camera;
	
	gl_Position = u_worldMatrix * vec4(a_vertices, 1.0f);
}