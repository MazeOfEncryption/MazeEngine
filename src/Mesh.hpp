#ifndef MAZEENGINE_MESH
#define MAZEENGINE_MESH
#include "Dep.hpp"
#include "Component.hpp"
#include "Read.hpp"
#include <string>
#include <vector>
namespace MazeEngine {
	class Mesh : public Component {
		public:
			Mesh() {}
			Mesh(std::string src);
			void setSource(std::string source);
			void loadMesh();
			void init();
			void update() {}
			std::vector<float> vertices, normals, UVs;
		private:
			std::string source;
	};
}
#endif