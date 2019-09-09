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
// Function for finding the index of an element in a vector
template <typename type>
int indexOf (type element, std::vector<type> array) {
	return std::distance(std::begin(array), std::find(std::begin(array), std::end(array), element));
}
// Boolean and GLFW callback to stop mouse input when the window is minimized
bool mouseInput = false;
void windowFocus (GLFWwindow* window, int focused) {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	mouseInput = false;
}
// GLFW callback to get key presses
std::vector<bool> keys {false, false, false, false};
void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::vector<int> keyList {GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D};
	int index = indexOf<int>(key, keyList);
	if (index < 4 && action != GLFW_REPEAT) keys[index] = action;
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
	
	glfwSetWindowFocusCallback(window, windowFocus);
	glfwSetKeyCallback(window, keyEvent);
	
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
	// Shader Error Logging
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);	
	// Shader Error Logging
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Shader Error Logging
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
	
	glm::vec3 camera = glm::vec3(0.0f, 1.0f, 1.0f);
	glm::vec3 target;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 location;
	glm::mat4 worldMatrix;
	
	double lastX, lastY;
	double posX, posY;
	double deltaX, deltaY;
	float angleX = 0.0f, angleY = 220.0f;
	float locX = 0.0f, locY = 0.0f;
	std::vector<float> speed {0.0f, 0.0f, 0.0f, 0.0f};
	float max = 0.025f, acc = 0.001f, dec = 0.001f;
	int width, height;
	float radiansX, radiansY;
	glfwGetCursorPos(window, &lastX, &lastY);
	
	glEnable(GL_DEPTH_TEST);
	glUseProgram(shaderProgram);
	
	while (!glfwWindowShouldClose(window)) {
		float t = glfwGetTime();
		glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
		
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (!mouseInput) glfwGetCursorPos(window, &lastX, &lastY);
			mouseInput = true;
		}
		if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mouseInput = false;
		}
		if (mouseInput) {
			glfwGetCursorPos(window, &posX, &posY);
			
			deltaX = posX - lastX;
			deltaY = posY - lastY;
		
			lastX = posX;
			lastY = posY;
		} else {
			deltaX = 0.0f;
			deltaY = 0.0f;
		}
		
		angleX += deltaX / 10.0f;
		angleY += deltaY / 10.0f;
		
		if (angleY > 269.9f) angleY = 269.9f;
		if (angleY < 90.1f) angleY = 90.1f;
		
		radiansX = glm::radians(angleX);
		radiansY = glm::radians(angleY);
		
		for (int x = 0; x < 4; x++) {
			speed[x] = keys[x] ? (speed[x] + acc > max ? max : speed[x] + acc) : (speed[x] - dec < 0 ? 0 : speed[x] - dec);
			float angle = angleX * M_PI / 180 - (x % 2 ? M_PI / 2 : 0);
			// float dir = ((x >> 1) % 2 == x % 2) * 2 - 1;
			float dir;
			switch(x) {
				case 0: dir = -1; break;
				case 1: dir = -1; break;
				case 2: dir =  1; break;
				case 3: dir =  1; break;
				default: break;
			}
			locX += speed[x] * sin(angle) * dir;
			locY -= speed[x] * cos(angle) * dir;
		}
		
		location = glm::translate(glm::mat4(1.0f), glm::vec3(locX, 0.0f, locY));
		
		projection = glm::perspective(glm::radians(90.0f), (float) width / (float) height, 0.1f, 50.0f);
		
		rotationX = glm::rotate(glm::mat4(1.0f), radiansX, glm::vec3( 0.0f, -1.0f, 0.0f));
		rotationY = glm::rotate(glm::mat4(1.0f), radiansY, glm::vec3(-1.0f,  0.0f, 0.0f));
		target = glm::vec3(rotationX * rotationY * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		
		view = glm::lookAt(
			camera,
			camera + target,
			up
		);
		
		worldMatrix = projection * view * location;
		
		glUniformMatrix4fv(u_worldMatrix, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		
		float dt = glfwGetTime() - t;
		float fps = 1.0f / dt;
		
		std::string title = "MazeEngine --- FPS: " + std::to_string(fps) + " --- rx: " + std::to_string(radiansX) + " ry: " + std::to_string(radiansY) + " --- W: " + std::to_string(keys[0]) + " A: " + std::to_string(keys[1]) + " S: " + std::to_string(keys[2]) + " D: " + std::to_string(keys[3]);
		glfwSetWindowTitle(window, title.c_str());
	}
	return 0;
}