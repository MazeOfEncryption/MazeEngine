#include "main.hpp"
// Function to read a file into a string
std::string read(std::string file) {
	std::ifstream in (file);
	if (in.fail()) {
		std::cout << "ERROR::IFSTREAM::FAIL" << std::endl;
		return "";
	}
	std::stringstream stream;
	stream << in.rdbuf();
	return stream.str();
}
// Function for copying bytes from a string to some type t
template <typename type>
type stringBytes (std::string input) {
	type output;
	const char *bytes = input.c_str();
	memcpy(&output, bytes, sizeof(type));
	return output;
}
void readStl (std::string file, std::vector<float> *vertices, std::vector<float> *normals) {
	std::string object = read(file);
	std::string header = object.substr(0, 80);
	std::cout << "Header: " << header << std::endl;
	std::string lengthString = object.substr(80, 4);
	unsigned length = stringBytes<unsigned>(lengthString);
	std::cout << "Length: " << length << std::endl;
	int position = 84;
	float newNormals[3];
	for (unsigned x = 0; x < length; x++) {
		memset(newNormals, 0, sizeof(newNormals));
		for (int y = 0; y < 3; y++) {
			std::string normalString = object.substr(position, sizeof(float));
			position += sizeof(float);
			float normal = stringBytes<float>(normalString);
			newNormals[y] = normal;
		}
		for (int y = 0; y < 3; y++) normals->insert(normals->end(), std::begin(newNormals), std::end(newNormals));
		for (int y = 0; y < 9; y++) {
			std::string vertexString = object.substr(position, sizeof(float));
			position += sizeof(float);
			float vertex = stringBytes<float>(vertexString);
			vertices->push_back(vertex);
		}
		position += 2;
	}
}
typedef struct {
	float x, y, z;
} tuple;
typedef struct {
	tuple vertex, normal;
} point;
void readPly (std::string file, std::vector<float> *vertices, std::vector<float> *normals) {
	std::ifstream in(file);
	std::string block;
	int pointCount;
	int faceCount;
	std::vector<point> points;
	while (in >> block) {
		if (block == "element") {
			in >> block;
			if (block == "vertex") {
				in >> block;
				pointCount = stoi(block);
			}
			if (block == "face") {
				in >> block;
				faceCount = stoi(block);
			}
		}
		if (block == "end_header") break;
	}
	for (int i = 0; i < pointCount; i++) {
		point point;
		in >> point.vertex.x >> point.vertex.y >> point.vertex.z >> point.normal.x >> point.normal.y >> point.normal.z;
		points.push_back(point);
	}
	for (int i = 0; i < faceCount * 4; i++) {
		if (!(i % 4)) {
			in >> block;
			if (stoi(block) != 3) {
				std::cout << "ERROR::PLY::NGON" << std::endl;
			}
		} else {
			in >> block;
			point point = points[stoi(block)];
			vertices->push_back(point.vertex.x);
			vertices->push_back(point.vertex.y);
			vertices->push_back(point.vertex.z);
			normals->push_back(point.normal.x);
			normals->push_back(point.normal.y);
			normals->push_back(point.normal.z);
		}
	}
	std::cout << points.size() << std::endl;
	std::cout << "Points: " << pointCount << std::endl;
	std::cout << "Faces: " << faceCount << std::endl;
}