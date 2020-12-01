#define _USE_MATH_DEFINES
#include "Transform.hpp"
// #include "Object.hpp"
// #include "Component.hpp"

using namespace MazeEngine;
int main () {
	Object obj;
	Component* transform = obj.createComponent<Transform>();
	obj.init();
	return 0;
}