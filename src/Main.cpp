#define _USE_MATH_DEFINES
#include "Scene.hpp"
#include "Transform.hpp"
// #include "Object.hpp"
// #include "Component.hpp"

using namespace MazeEngine;
int main () {
	Scene scene;
	Object *player = scene.createObject<Object>();
	Component *transform = player->createComponent<Transform>();
	scene.init();
	return 0;
}