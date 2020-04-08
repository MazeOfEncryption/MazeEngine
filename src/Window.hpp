#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
class Window {
	public:
		std::string read(std::string file);
	void compileShaders();
		void init();
		bool shouldClose();
		void clear();
		void draw();
		Window(std::string vert, std::string frag);
	private:
		void glfwWindowHints();
		GLFWwindow* window;
		std::string vert, frag;
		int shaderProgram;
};