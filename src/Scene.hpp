#ifndef MAZEENGINE_SCENE
#define MAZEENGINE_SCENE
#include "Object.hpp"
#include <vector>
#include <string>
namespace MazeEngine {
	class Object;
	class Scene {
		private:
			void addObject(Object *object);
			std::vector<Object *> Objects;
		public:
			// Init all objects
			void init();
			// Update all objects
			void update();
			// Add object
			template<typename ...Args>
			void add(Args&& ...objects) {
				(this->addObject(objects), ...);
			}
			template <class Type, class ...Types>
			Object* createObject (Types... args) {
				Object *object = new Type(args...);
				this->addObject(object);
				return object;
			}
			Scene();
			~Scene();
			template<typename ...Args>
			Scene(Args ...objects) {
				this->add(objects...);
			}
	};
}
#endif