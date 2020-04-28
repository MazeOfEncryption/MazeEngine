#ifndef MAZEENGINE_OBJECT
#define MAZEENGINE_OBJECT
#include "Dep.hpp"
#include "Read.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include <string>
#include <vector>
namespace MazeEngine {
	class Object {
		public:
			Object();
			Object(MazeEngine::Mesh mesh, MazeEngine::Shader shader);
			void setMesh(MazeEngine::Mesh mesh);
			void setShader(MazeEngine::Shader shader);
			void loadMesh();
			void loadShader();
			void draw();
			glm::vec3 position, rotation;
		private:
			MazeEngine::Mesh mesh;
			MazeEngine::Shader shader;
			unsigned vao, vertexBuffer, normalBuffer, uvBuffer, a_vertices, a_normals, a_UVs;
	};
}
#endif