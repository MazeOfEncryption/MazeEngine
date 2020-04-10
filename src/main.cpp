#include "MazeEngine.hpp"
/*
* TODO:
* Some sort of 3d Object Class
* Multi Object Support
* Standard Uniforms for shaders
* Easy way to add custom uniforms
* Move main.cpp to seperate test folder
* Rename lib to dep
* Seperate all header files and implimentation files
* Build library instead of exe(?)
* Common shaders as enums
* Better way of packaging shaders, resources, etc. (Most likely move shaders into string literals in header files)
* Keyboard handling
*/
int main() {
	std::vector<float> vertices, normals;

	MazeEngine::readPly("meshes/object.ply", &vertices, &normals);
	
	MazeEngine::Window win = MazeEngine::Window("Test", 800, 600);

	MazeEngine::Shader shader = MazeEngine::Shader("shaders/vert.glsl", "shaders/static.glsl");
	MazeEngine::useShader(shader);

	unsigned vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	unsigned normalBuffer;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
	
	unsigned a_vertices = glGetAttribLocation(shader.getId(), "a_vertices");
	unsigned a_normals = glGetAttribLocation(shader.getId(), "a_normals");

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(a_vertices, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(a_vertices);
	
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(a_normals, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(a_normals);

	while (!win.shouldClose()) {
		win.clear();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
		win.draw();
	}
	return 0;
}