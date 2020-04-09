#include "MazeEngine.hpp"
#include "Window.hpp"
int main() {
	MazeEngine::Window win = MazeEngine::Window("vert.glsl", "frag.glsl");
	// win.compileShaders();
	win.init();
	while (!win.shouldClose()) {
		win.clear();
		win.draw();
	}
	return 0;
}