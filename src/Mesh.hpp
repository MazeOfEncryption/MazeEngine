#ifndef MAZEENGINE_MESH
#define MAZEENGINE_MESH
#include "Dep.hpp"
#include "Read.hpp"
#include "Shader.hpp"
#include <string>
#include <vector>
namespace MazeEngine {
	class Mesh {
		public:
			Mesh(std::string src);
			Mesh(std::string src, MazeEngine::Shader shader);
			Mesh();
			void setSource(std::string source);
			void setShader(MazeEngine::Shader shader);
			void loadShader();
			void loadMesh();
			void draw();
		private:
			MazeEngine::Shader shader;
			std::vector<float> vertices, normals;
			std::string source;
			unsigned vao, vertexBuffer, normalBuffer, a_vertices, a_normals;
	};
}
#endif