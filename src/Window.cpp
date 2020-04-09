#include "Window.hpp"
#include "Read.hpp"
void MazeEngine::Window::compileShaders() {
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
void MazeEngine::Window::glfwWindowHints() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
}
void MazeEngine::Window::init() {
    glfwInit();
	Window::glfwWindowHints();
	this->window = glfwCreateWindow(960, 540, "MazeCV", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glEnable(GL_DEBUG_OUTPUT);
} 
bool MazeEngine::Window::shouldClose() {
	return glfwWindowShouldClose(this->window);
}
void MazeEngine::Window::clear() {
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void MazeEngine::Window::draw() {
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}
MazeEngine::Window::Window(std::string vert, std::string frag) {
	std::cout << "Constructor Called" << std::endl;
	this->vert = vert;
	this->frag = frag;
}