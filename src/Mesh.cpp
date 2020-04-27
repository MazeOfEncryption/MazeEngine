#include "Mesh.hpp"
MazeEngine::Mesh::Mesh(std::string source) {
	this->source = source;
}
void MazeEngine::Mesh::setSource(std::string source) {
	this->source = source;
}
void MazeEngine::Mesh::setShader(MazeEngine::Shader shader) {
	this->shader = shader;
}
MazeEngine::Mesh::Mesh(){};
MazeEngine::Mesh::Mesh(std::string source, MazeEngine::Shader shader){
	this->source = source;
	this->shader = shader;
	this->loadMesh();
	this->loadShader();
};
void MazeEngine::Mesh::loadMesh() {
	std::string extension = this->source.substr(this->source.length() - 4, 4);
	if (extension == ".ply") {
		MazeEngine::readPly(this->source, &this->vertices, &this->normals);
	} else if (extension == ".stl") {
		MazeEngine::readStl(this->source, &this->vertices, &this->normals);
	} else {
		std::cout << "Error: Unsupported file format." << std::endl;
	}
	
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(float), this->vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &this->normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(float), this->normals.data(), GL_STATIC_DRAW);
}
void MazeEngine::Mesh::loadShader() {
	this->a_vertices = glGetAttribLocation(this->shader.getId(), "a_vertices");
	this->a_normals = glGetAttribLocation(this->shader.getId(), "a_normals");

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(this->a_vertices, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(this->a_vertices);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
	glVertexAttribPointer(this->a_normals, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(this->a_normals);
};
void MazeEngine::Mesh::draw () {
	MazeEngine::useShader(this->shader);
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, this->vertices.size() / 3);
}