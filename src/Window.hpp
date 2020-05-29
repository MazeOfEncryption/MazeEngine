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
			bool active();
			void clear();
			void draw();
			Window(std::string title, int width, int height);
			GLFWwindow* window;
			double startTime, time, dt;
		private:
			void init();
			std::string title;
			int width, height;
			void glfwWindowHints();
	};
}
#endif