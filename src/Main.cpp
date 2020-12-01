#include "Scene.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Render.hpp"
// #include "Object.hpp"
// #include "Component.hpp"

using namespace MazeEngine;
int main () {
	Scene scene;
	Object    *box             = scene.createObject<Object>();
	Transform *boxTransform    = box->createComponent<Transform>(0.0f, 0.5f, 5.0f);
	Mesh      *boxMesh         = box->createComponent<Mesh>("object.ply");
	Shader    *boxShader       = box->createComponent<Shader>("vert.glsl", "static.glsl");
	Render    *boxRender       = box->createComponent<Render>(boxTransform, boxMesh, boxShader);
	Object    *player          = scene.createObject<Object>();
	Component *playerTransform = player->createComponent<Transform>();
	scene.init();
	return 0;
}