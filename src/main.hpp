#define _USE_MATH_DEFINES
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtx/string_cast.hpp>
#include <ext.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <FreeImage.h>
std::string read(std::string file);
void readStl (std::string file, std::vector<float> *vertices, std::vector<float> *normals);
void readPly (std::string file, std::vector<float> *vertices, std::vector<float> *normals);
int compileShaders();
void recompileShaders (int *program);