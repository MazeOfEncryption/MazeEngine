#ifndef MAZEENGINE_TRANSFORM
#define MAZEENGINE_TRANSFORM
#include "Dep.hpp"
#include "Component.hpp"
namespace MazeEngine {
	class Transform : public Component {
		public:
			glm::vec3 pos;
			glm::vec3 rot;
			glm::vec3 scale;
			Transform() {};
			Transform(glm::vec3 pos)
				: pos(pos)
			{};
			Transform(glm::vec3 pos, glm::vec3 rot)
				: pos(pos)
				, rot(rot)
			{};
			Transform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
				: pos(pos)
				, rot(rot)
				, scale(scale)
			{};
			Transform(float px, float py, float pz)
				: pos(glm::vec3(px, py, pz))
			{};
			Transform(float px, float py, float pz, float rx, float ry, float rz)
				: pos(glm::vec3(px, py, pz))
				, rot(glm::vec3(rx, ry, rz))
			{};
			Transform(float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz)
				: pos(glm::vec3(px, py, pz))
				, rot(glm::vec3(rx, ry, rz))
				, scale(glm::vec3(sx, sy, sz))
			{};
			~Transform() {};
			void init() {}
			void update() {}
		private:
	};
}
#endif