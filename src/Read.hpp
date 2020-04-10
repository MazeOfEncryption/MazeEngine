#ifndef MAZEENGINE_READ
#define MAZEENGINE_READ
#define _USE_MATH_DEFINES
#include "Dep.hpp"
#include <gtx/string_cast.hpp>
#include <ext.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
namespace MazeEngine {
	std::string readTxt (std::string file);
	void readStl (std::string file, std::vector<float> *vertices, std::vector<float> *normals);
	void readPly (std::string file, std::vector<float> *vertices, std::vector<float> *normals);
}
#endif