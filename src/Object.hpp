#ifndef MAZEENGINE_OBJECT
#define MAZEENGINE_OBJECT
#include <vector>
#include <string>
namespace MazeEngine {
	class Component;
	class Scene;
	class Object {
		friend Scene;
		public:
			// Init all components
			void init();
			// Update all components
			void update();
			// Add Component
			template<typename ...Args>
			void add(Args&& ...components) {
				(this->addComponent(components), ...);
			}
			template <class Type, class ...Types>
			Type* createComponent (Types... args) {
				Type *component = new Type(args...);
				this->addComponent(component);
				return component;
			}
			Object();
			~Object();
			template<typename ...Args>
			Object(Args ...components) {
				this->add(components...);
			}
		private:
			void addComponent(Component *component);
			std::vector<Component *> Components;
			Scene *Parent = nullptr;
	};
}
#endif