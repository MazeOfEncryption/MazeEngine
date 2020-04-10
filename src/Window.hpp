#ifndef MAZEENGINE_WINDOW
#define MAZEENGINE_WINDOW
#include "Dep.hpp"
#include "Read.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
namespace MazeEngine {
	class Window {
		public:
			bool shouldClose();
			void clear();
			void draw();
			Window(std::string title, int width, int height);
		private:
			void init();
			std::string title;
			int width, height;
			void glfwWindowHints();
			GLFWwindow* window;
	};
}
#endif