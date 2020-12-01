#ifndef MAZEENGINE_TRANSFORM
#define MAZEENGINE_TRANSFORM
#include "Dep.hpp"
#include "Component.hpp"
namespace MazeEngine {
	class Transform : public Component {
		public:
			glm::vec3 position;
			glm::vec3 rotation;
			glm::vec3 scale;
			// Transform(){};
			// ~Transform() {};
			void init() {}
			void update() {}
		private:
	};
}
#endif