#include "Mesh.hpp"
MazeEngine::Mesh::Mesh(){}
MazeEngine::Mesh::Mesh(std::string source) {
	this->source = source;
}
void MazeEngine::Mesh::setSource(std::string source) {
	this->source = source;
}
void MazeEngine::Mesh::loadMesh() {
	std::string extension = this->source.substr(this->source.length() - 4, 4);
	if (extension == ".ply") {
		MazeEngine::readPly(this->source, &this->vertices, &this->normals, &this->UVs);
	} else if (extension == ".stl") {
		MazeEngine::readStl(this->source, &this->vertices, &this->normals);
	} else {
		std::cout << "Error: Unsupported file format." << std::endl;
	}
}