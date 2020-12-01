#ifndef MAZEENGINE_TRANSFORM
#define MAZEENGINE_TRANSFORM
#include "Component.hpp"
#include <iostream>
namespace MazeEngine {
	class Transform : public Component {
		public:
			std::string getName() {
				return "Transform";
			}
			float x, y, z;
			// Transform(){};
			// ~Transform() {};
			void init() {
				std::cout << "Transform initialized." << std::endl;
			}
			void update() {}
		private:
	};
}
#endif