#ifndef MAZEENGINE_SHADER
#define MAZEENGINE_SHADER
#include "Dep.hpp"
#include "Component.hpp"
#include "Read.hpp"
#include <string>
namespace MazeEngine {
    class Shader : public Component {
        public:
            Shader(std::string vert, std::string frag);
            Shader();
            ~Shader();
			void setSource(std::string vert, std::string frag);
            void compile();
            unsigned getId();
			void init() {}
			void update() {}
        private:
            std::string vert, frag;
            unsigned shaderProgram;
    };
    void useShader (Shader shader);
}
#endif