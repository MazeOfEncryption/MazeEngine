#define _USE_MATH_DEFINES
#include "Transform.hpp"
// #include "Object.hpp"
// #include "Component.hpp"

using namespace MazeEngine;
int main () {
	Object player;
	Component* transform = player.createComponent<Transform>();
	player.init();
	return 0;
}