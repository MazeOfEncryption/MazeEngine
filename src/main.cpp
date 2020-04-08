#include "Window.hpp"
int main() {
	Window win = Window("vert.glsl", "frag.glsl");
	// win.compileShaders();
	win.init();
	while (!win.shouldClose()) {
		win.clear();
		win.draw();
	}
	return 0;
}