#ifndef MAZEENGINE_WINDOW
#define MAZEENGINE_WINDOW
#include "MazeEngine.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
namespace MazeEngine {
	class Window {
		public:
			std::string read(std::string file);
			void compileShaders();
			void init();
			bool shouldClose();
			void clear();
			void draw();
			Window(std::string vert, std::string frag);
			int shaderProgram;
		private:
			void glfwWindowHints();
			GLFWwindow* window;
			std::string vert, frag;
	};
}
#endif