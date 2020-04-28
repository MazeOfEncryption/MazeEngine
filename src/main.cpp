#include "MazeEngine.hpp"
/*
* TODO:
* Standard Uniforms for shaders
* Easy way to add custom uniforms
* Move main.cpp to seperate test folder
* Rename lib to dep
* Seperate all header files and implimentation files
* Build library instead of exe(?)
* Common shaders as enums
* Better way of packaging shaders, resources, etc. (Most likely move shaders into string literals in header files)
* Keyboard handling
*/
using namespace MazeEngine;
int main() {
	Window win = Window("Test", 800, 600);
	Shader shader = Shader("shaders/vert.glsl", "shaders/static.glsl");
	Mesh mesh = Mesh("meshes/object.ply");
	// Mesh mesh2 = Mesh("meshes/object2.ply");
	Object object = Object(mesh, shader);
	// Object object2 = Object(mesh2, shader);
	while (win.active()) {
		win.clear();
		object.draw();
		// object2.draw();
		win.draw();
	}
	return 0;
}