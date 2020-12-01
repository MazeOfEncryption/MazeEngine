// #include <iostream>
#include "Transform.hpp"
// #include "Object.hpp"
// #include "Component.hpp"

using namespace MazeEngine;
int main () {
	Object obj;
	Component* trans = obj.createComponent<Transform>();
	// std::cout << trans1->getParent() << trans2->getParent() << std::endl;
	// Transform trans;
	// obj.addComponent(&trans);
	// std::cout << obj.createComponent<Transform>()->getName() << std::endl;
	// obj.Init();
	return 0;
}