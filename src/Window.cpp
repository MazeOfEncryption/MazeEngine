#include "Window.hpp"
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
	const char *title = this->title.c_str();
	this->window = glfwCreateWindow(this->width, this->height, title, NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glEnable(GL_DEBUG_OUTPUT);
} 
bool MazeEngine::Window::active() {
	return !glfwWindowShouldClose(this->window);
}
void MazeEngine::Window::clear() {
	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void MazeEngine::Window::draw() {
	this->time = glfwGetTime();
	this->dt = this->time - this->startTime;
	this->startTime = this->time;
	glfwSwapBuffers(this->window);
	glfwPollEvents();
}
MazeEngine::Window::Window(std::string title, int width, int height) {
	std::cout << "Window constructor called." << std::endl;
	this->title = title;
	this->width = width;
	this->height = height;
	this->startTime = 0.0;
	this->dt = 0.0;
	this->time = 0.0;
	this->init();
}