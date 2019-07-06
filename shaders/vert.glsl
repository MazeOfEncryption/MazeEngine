#version 330 core
in vec3 a_vertices;
uniform mat4 u_worldMatrix;
out vec4 v_color;
void main () {
	v_color = vec4(a_vertices + vec3(0.5), 1);
	gl_Position = u_worldMatrix * vec4(a_vertices, 1);
}