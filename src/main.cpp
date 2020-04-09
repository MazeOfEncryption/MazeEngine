#include "MazeEngine.hpp"
#include "Window.hpp"
#include "Read.hpp"
/*
* TODO:
* Create Shader Class
* Multi Shader Support
* Some sort of 3d Object Class
* Multi Object Support
* Keyboard handling
* Standard Uniforms for shaders
* Easy way to add custom uniforms
*/
int main() {
	std::vector<float> vertices, normals;

	MazeEngine::readPly("object.ply", &vertices, &normals);
	
	MazeEngine::Window win = MazeEngine::Window("vert.glsl", "static.glsl");
	std::cout << "Test." << std::endl;
	win.init();
	win.compileShaders();

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
	
	unsigned a_vertices = glGetAttribLocation(win.shaderProgram, "a_vertices");
	unsigned a_normals = glGetAttribLocation(win.shaderProgram, "a_normals");

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(a_vertices, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(a_vertices);
	
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(a_normals, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(a_normals);

	glUseProgram(win.shaderProgram);

	while (!win.shouldClose()) {
		win.clear();
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
		win.draw();
	}
	return 0;
}