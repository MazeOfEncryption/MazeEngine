#include "Scene.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Window.hpp"
#include "Shader.hpp"
#include "Render.hpp"
// #include "Object.hpp"
// #include "Component.hpp"

using namespace MazeEngine;
int main () {
	Window win = Window("Test", 800, 600);
	Scene scene;
	Object    *box             = scene.createObject<Object>();
	Transform *boxTransform    = box->createComponent<Transform>(0.0f, 0.5f, 5.0f);
	Mesh      *boxMesh         = box->createComponent<Mesh>("meshes/object.ply");
	Shader    *boxShader       = box->createComponent<Shader>("shaders/vert.glsl", "shaders/static2.glsl");
	Render    *boxRender       = box->createComponent<Render>(boxTransform, boxMesh, boxShader);
	Object    *player          = scene.createObject<Object>();
	Component *playerTransform = player->createComponent<Transform>();
	
	scene.init();
	while (win.active()) {
		win.clear();
		boxRender->draw();
		win.draw();
	}
	return 0;
}