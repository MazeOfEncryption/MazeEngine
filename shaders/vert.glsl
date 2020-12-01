#version 330 core
in vec3 a_vertices;
in vec3 a_normals;
in vec2 a_UVs;
uniform mat4 u_worldMatrix;

out vec3 v_normal;
out vec3 v_fragPos;
out vec2 v_UV;

void main () {
	v_normal = a_normals;
	v_fragPos = a_vertices;
	v_UV = a_UVs;
	
	gl_Position = vec4(a_vertices, 1.0f);
}