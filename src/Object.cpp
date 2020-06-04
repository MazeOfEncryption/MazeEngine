#include "Object.hpp"
void MazeEngine::Object::setMesh(MazeEngine::Mesh mesh) {
	this->mesh = mesh;
}
void MazeEngine::Object::setShader(MazeEngine::Shader shader) {
	this->shader = shader;
}
MazeEngine::Object::Object(){
	this->mass = 0.0f;
	this->drag = 0.0f;
	this->force = glm::vec3(0);
	this->acceleration = glm::vec3(0);
	this->velocity = glm::vec3(0);
	this->position = glm::vec3(0);
	this->rotation = glm::vec3(0);
}
MazeEngine::Object::Object(MazeEngine::Mesh mesh, MazeEngine::Shader shader) {
	this->mesh = mesh;
	this->shader = shader;
	this->loadMesh();
	this->loadShader();
	this->mass = 0.0f;
	this->drag = 0.0f;
	this->force = glm::vec3(0);
	this->acceleration = glm::vec3(0);
	this->velocity = glm::vec3(0);
	this->position = glm::vec3(0);
	this->rotation = glm::vec3(0);
}
void MazeEngine::Object::loadMesh() {
	this->mesh.loadMesh();
	
	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	glGenBuffers(1, &this->vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->mesh.vertices.size() * sizeof(float), this->mesh.vertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &this->normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->mesh.normals.size() * sizeof(float), this->mesh.normals.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &this->uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->mesh.UVs.size() * sizeof(float), this->mesh.UVs.data(), GL_STATIC_DRAW);
}
void MazeEngine::Object::loadShader() {
	this->a_vertices = glGetAttribLocation(this->shader.getId(), "a_vertices");
	this->a_normals = glGetAttribLocation(this->shader.getId(), "a_normals");
	this->a_UVs = glGetAttribLocation(this->shader.getId(), "a_UVs");

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(this->a_vertices, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(this->a_vertices);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->normalBuffer);
	glVertexAttribPointer(this->a_normals, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(this->a_normals);

	glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
	glVertexAttribPointer(this->a_UVs, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(this->a_UVs);
}
void MazeEngine::Object::draw () {
	MazeEngine::useShader(this->shader);
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, this->mesh.vertices.size() / 3);
}
void MazeEngine::Object::tick (float dt) {
	this->acceleration = this->force / this->mass;
	this->velocity += this->acceleration * dt - this->velocity * this->drag;
	this->position += this->velocity * dt;
}