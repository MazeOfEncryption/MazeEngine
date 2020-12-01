#include "Scene.hpp"
MazeEngine::Scene::Scene() {}
MazeEngine::Scene::~Scene() {}
void MazeEngine::Scene::init() {
	for (auto &object : this->Objects) {
		object->init();
	}
}
void MazeEngine::Scene::update() {
	for (auto &object : this->Objects) {
		object->update();
	}
}
void MazeEngine::Scene::addObject(Object *object) {
	this->Objects.push_back(object);
	object->Parent = this;
}