#ifndef MAZEENGINE_RENDER
#define MAZEENGINE_RENDER
#include "Component.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
namespace MazeEngine {
	class Transform;
	class Render : public Component {
		public:
			Render(Transform *transform)
				: transform(transform)
			{}
			Render(Transform *transform, Mesh *mesh)
				: transform(transform)
				, mesh(mesh)
			{}
			Render(Transform *transform, Mesh *mesh, Shader *shader)
				: transform(transform)
				, mesh(mesh)
				, shader(shader)
			{}
			Render() {}
			~Render() {}
			void init();
			void update() {}
			void draw();
		private:
			Transform *transform;
			Mesh *mesh;
			Shader *shader;
			unsigned vao, vertexBuffer, normalBuffer, uvBuffer, a_vertices, a_normals, a_UVs;
	};
}
#endif