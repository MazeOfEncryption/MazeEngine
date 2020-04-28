#ifndef MAZEENGINE_MESH
#define MAZEENGINE_MESH
#include "Dep.hpp"
#include "Read.hpp"
#include <string>
#include <vector>
namespace MazeEngine {
	class Mesh {
		public:
			Mesh();
			Mesh(std::string src);
			void setSource(std::string source);
			void loadMesh();
			std::vector<float> vertices, normals, UVs;
		private:
			std::string source;
	};
}
#endif