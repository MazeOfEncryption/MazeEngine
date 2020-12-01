#include "Object.hpp"
#include "Component.hpp"
#include <memory>
MazeEngine::Object::Object() {}
MazeEngine::Object::~Object() {}
void MazeEngine::Object::init() {
	for (auto &component : this->Components) {
		component->init();
	}
}
void MazeEngine::Object::update() {
	for (auto &component : this->Components) {
		component->update();
	}
}
void MazeEngine::Object::addComponent(Component *component) {
	this->Components.push_back(component);
	component->Parent = this;
}