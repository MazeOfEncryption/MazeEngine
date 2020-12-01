#ifndef MAZEENGINE_RENDER
#define MAZEENGINE_RENDER
#include "Component.hpp"
namespace MazeEngine {
	class Transform;
	class Mesh;
	class Shader;
	class Render : public Component {
		public:
			Render(Transform *transform)
				: transform(transform)
			{};
			Render(Transform *transform, Mesh *mesh)
				: transform(transform)
				, mesh(mesh)
			{};
			Render(Transform *transform, Mesh *mesh, Shader *shader)
				: transform(transform)
				, mesh(mesh)
				, shader(shader)
			{};
			~Render() {};
			void init() {}
			void update() {}
		private:
			Transform *transform;
			Mesh *mesh;
			Shader *shader;
	};
}
#endif