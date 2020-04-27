#include "MazeEngine.hpp"
/*
* TODO:
* Split Mesh Class into Mesh and Object classes - Mesh is just vertex/normal data, Object has shader/other info too.
* Multi Object Support
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
int main() {
	MazeEngine::Window win = MazeEngine::Window("Test", 800, 600);
	MazeEngine::Shader shader = MazeEngine::Shader("shaders/vert.glsl", "shaders/static.glsl");
	MazeEngine::Mesh mesh = MazeEngine::Mesh("meshes/object.ply", shader);
	while (win.active()) {
		win.clear();
		mesh.draw();
		win.draw();
	}
	return 0;
}