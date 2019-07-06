#include "main.hpp"
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
int main() {
	std::vector<float> vertices {
		 0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,   0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,   0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,
		
		-0.5f,  0.5f, -0.5f,  -0.5f,  0.5f,  0.5f,  -0.5f, -0.5f, -0.5f,
		-0.5f,  0.5f,  0.5f,  -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f,  0.5f,
		
		-0.5f,  0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,   0.5f, -0.5f,  0.5f,
		
		 0.5f,  0.5f,  0.5f,   0.5f, -0.5f,  0.5f,   0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,   0.5f,  0.5f, -0.5f,   0.5f, -0.5f, -0.5f,
		
		 0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,
		
		 0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,
	};
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	// glfwWindowHint(GLFW_MAXIMIZED, true);
	GLFWwindow* window = glfwCreateWindow(800, 600, "MazeEngine", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	std::string vertexShaderCode = read("./shaders/vert.glsl");
	std::string fragmentShaderCode = read("./shaders/frag.glsl");
	
	const char * vertexShaderSource = vertexShaderCode.c_str();
	const char * fragmentShaderSource = fragmentShaderCode.c_str();
	
	//std::cout << "Vertex Shader:\n" << vertexShaderCode << std::endl;
	//std::cout << "Fragment Shader:\n" << fragmentShaderCode << std::endl;
	
	int success;
	char infoLog[512];
	
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	unsigned vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	unsigned vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	
	std::cout << read("./todo.txt") << std::endl;
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	
	unsigned u_worldMatrix = glGetUniformLocation(shaderProgram, "u_worldMatrix");
	
	glm::mat4 projection;
	glm::mat4 view;
	
	glm::vec3 camera;
	glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 worldMatrix;
	
	float radius = 5.0f;
	
	glEnable(GL_DEPTH_TEST);
	glUseProgram(shaderProgram);
	
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
		
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		
		projection = glm::perspective(glm::radians(45.0f), (float) width / (float) height, 0.1f, 50.0f);
		
		float t = glfwGetTime();
		
		view = glm::lookAt(
			glm::vec3(sin(t) * radius, 3.0f, cos(t) * radius),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
		
		worldMatrix = projection * view;
		
		glUniformMatrix4fv(u_worldMatrix, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}