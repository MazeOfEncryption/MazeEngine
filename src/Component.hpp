#ifndef MAZEENGINE_COMPONENT
#define MAZEENGINE_COMPONENT
#include "Object.hpp"
namespace MazeEngine {
	class Object;
	class Component {
		friend Object;
		public:
			Component() {};
			virtual ~Component() {};
			virtual void init() = 0;
			virtual void update() = 0;

			Object* getParent(){return Parent;}
		private:
			Object *Parent = nullptr;
	};
	template <class Type, class ...Types>
	Component* createComponent (Types... args) {
		Component *component = new Type(args...);
		return component;
	};
}
#endif