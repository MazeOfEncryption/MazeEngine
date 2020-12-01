#include "Shader.hpp"
MazeEngine::Shader::Shader (std::string vert, std::string frag) {
    this->vert = vert;
    this->frag = frag;
    this->compile();
}
MazeEngine::Shader::Shader () {}
MazeEngine::Shader::~Shader () {}
void MazeEngine::Shader::setSource(std::string vert, std::string frag) {
	this->vert = vert;
    this->frag = frag;
}
void MazeEngine::Shader::compile () {
	std::string vertexShaderCode = MazeEngine::readTxt(this->vert);
	std::string fragmentShaderCode = MazeEngine::readTxt(this->frag);
	
	const char * vertexShaderSource = vertexShaderCode.c_str();
	const char * fragmentShaderSource = fragmentShaderCode.c_str();
	
	int success;
	char infoLog[512];
	
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	// Shader Error Logging
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);	
	// Shader Error Logging
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Shader Error Logging
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	this->shaderProgram = shaderProgram;
	std::cout << "Shaders loaded." << std::endl;
}
unsigned MazeEngine::Shader::getId() {
    return this->shaderProgram;
}

void MazeEngine::useShader(MazeEngine::Shader shader) {
    glUseProgram(shader.getId());
}
void MazeEngine::Shader::use() {
	glUseProgram(this->shaderProgram);
}