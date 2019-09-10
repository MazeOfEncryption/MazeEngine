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
bool reloadShaders = false;
void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::vector<int> keyList {GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D};
	int index = indexOf<int>(key, keyList);
	if (index < 4 && action != GLFW_REPEAT) keys[index] = action;
	if (key == GLFW_KEY_R && action == GLFW_PRESS) reloadShaders = true;
}
int compileShaders() {
	std::string vertexShaderCode = read("./shaders/vert.glsl");
	std::string fragmentShaderCode = read("./shaders/frag.glsl");
	
	const char * vertexShaderSource = vertexShaderCode.c_str();
	const char * fragmentShaderSource = fragmentShaderCode.c_str();
	
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
	
	return shaderProgram;
}
void recompileShaders (int *program) {
	glDeleteProgram(*program);
	*program = compileShaders();
	std::cout << "Reloaded Shaders." << std::endl;
}
unsigned a_vertices, a_normals, u_worldMatrix, u_location, u_rotation, u_camera;
void getLocations(int *shaderProgram) {
	a_vertices = glGetAttribLocation(*shaderProgram, "a_vertices");
	a_normals = glGetAttribLocation(*shaderProgram, "a_normals");
	u_worldMatrix = glGetUniformLocation(*shaderProgram, "u_worldMatrix");
	u_location = glGetUniformLocation(*shaderProgram, "u_location");
	u_rotation = glGetUniformLocation(*shaderProgram, "u_rotation");
	u_camera = glGetUniformLocation(*shaderProgram, "u_camera");
}
int main() {
	std::vector<float> vertices {
		 0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,   0.5f, -0.5f, -0.5f, // back
		-0.5f,  0.5f, -0.5f,   0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, -0.5f, // normals  0  0 -1
		
		-0.5f,  0.5f, -0.5f,  -0.5f,  0.5f,  0.5f,  -0.5f, -0.5f, -0.5f, // left
		-0.5f,  0.5f,  0.5f,  -0.5f, -0.5f, -0.5f,  -0.5f, -0.5f,  0.5f, // normals -1  0  0
		
		-0.5f,  0.5f,  0.5f,  -0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f, // front
		-0.5f, -0.5f,  0.5f,   0.5f,  0.5f,  0.5f,   0.5f, -0.5f,  0.5f, // normals  0  0  1
		
		 0.5f,  0.5f,  0.5f,   0.5f, -0.5f,  0.5f,   0.5f,  0.5f, -0.5f, // right
		 0.5f, -0.5f,  0.5f,   0.5f,  0.5f, -0.5f,   0.5f, -0.5f, -0.5f, // normals  1  0  0
		
		 0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f, // top
		-0.5f,  0.5f, -0.5f,   0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f, // normals  0  1  0
		
		 0.5f, -0.5f, -0.5f,  -0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f, // bottom
		-0.5f, -0.5f, -0.5f,   0.5f, -0.5f,  0.5f,  -0.5f, -0.5f,  0.5f, // normals  0 -1  0
	};
	std::vector<float> normals {
		 0.0f,  0.0f, -1.0f,   0.0f,  0.0f, -1.0f,   0.0f,  0.0f, -1.0f,
		 0.0f,  0.0f, -1.0f,   0.0f,  0.0f, -1.0f,   0.0f,  0.0f, -1.0f,
		 
		-1.0f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,
		-1.0f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,  -1.0f,  0.0f,  0.0f,
		
		 0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  1.0f,
		 0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  1.0f,   0.0f,  0.0f,  1.0f,
		 
		 1.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,
		 1.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,   1.0f,  0.0f,  0.0f,
		 
		 0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  0.0f,
		 0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  0.0f,
		 
		 0.0f, -1.0f,  0.0f,   0.0f, -1.0f,  0.0f,   0.0f, -1.0f,  0.0f,
		 0.0f, -1.0f,  0.0f,   0.0f, -1.0f,  0.0f,   0.0f, -1.0f,  0.0f,
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
	
	int shaderProgram = compileShaders();
	
	unsigned vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	unsigned vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	
	unsigned normalBuffer;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
	
	std::cout << read("./todo.txt") << std::endl;
	
	getLocations(&shaderProgram);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(a_vertices, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(a_vertices);
	
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(a_normals, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(a_normals);
	
	glm::mat4 projection;
	glm::mat4 view;
	
	glm::vec3 camera = glm::vec3(0.0f, 1.0f, 1.0f);
	glm::vec3 target;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 rotationX;
	glm::mat4 rotationY;
	glm::mat4 rotation;
	glm::mat4 location;
	glm::mat4 worldMatrix;
	
	double lastX, lastY;
	double posX, posY;
	double deltaX, deltaY;
	float angleX = 0.0f, angleY = 220.0f;
	float locX = 0.0f, locY = 0.0f;
	std::vector<float> speed {0.0f, 0.0f, 0.0f, 0.0f};
	float max = 3.0f, acc = 0.5f, dec = 0.5f;
	int width, height;
	float fps = 0.0f, dt = 0.0f;
	float radiansX, radiansY;
	glfwGetCursorPos(window, &lastX, &lastY);
	
	glEnable(GL_DEPTH_TEST);
	glUseProgram(shaderProgram);
	
	while (!glfwWindowShouldClose(window)) {
		float t = glfwGetTime();
		
		if (reloadShaders) {
			recompileShaders(&shaderProgram);
			getLocations(&shaderProgram);
			glUseProgram(shaderProgram);
			reloadShaders = false;
		}
		
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
			// If keys true add acc, else sub dec, coerce between zero and max
			speed[x] = keys[x] ? (speed[x] + acc > max ? max : speed[x] + acc) : (speed[x] - dec < 0 ? 0 : speed[x] - dec);
			// Compute angle, subtract 90 deg if sideways 
			float angle = angleX * M_PI / 180 - (x % 2 ? M_PI / 2 : 0);
			// Compute direction
			float dir = x < 2 ? -1 : 1;
			// Add speed in direction in dt
			camera += speed[x] * sin(angle) * dir * dt * glm::vec3(0.0f, 0.0f, 0.0f);
			camera -= speed[x] * cos(angle) * dir * dt * glm::vec3(0.0f, 0.0f, 0.0f);
		}
		
		location = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		projection = glm::perspective(glm::radians(90.0f), (float) width / (float) height, 0.1f, 50.0f);
		rotationX = glm::rotate(glm::mat4(1.0f), radiansX, glm::vec3( 0.0f, -1.0f, 0.0f));
		rotationY = glm::rotate(glm::mat4(1.0f), radiansY, glm::vec3(-1.0f,  0.0f, 0.0f));
		rotation = rotationX * rotationY;
		target = glm::vec3(rotation * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		view = glm::lookAt(camera, camera + target,	up);
		worldMatrix = projection * view * location;
		
		glUniformMatrix4fv(u_worldMatrix, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glUniformMatrix4fv(u_location, 1, GL_FALSE, glm::value_ptr(location));
		glUniformMatrix4fv(u_rotation, 1, GL_FALSE, glm::value_ptr(rotation));
		glUniform3fv(u_rotation, 1, glm::value_ptr(camera));
		
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		
		dt = glfwGetTime() - t;
		fps = 1.0f / dt;
		
		std::ostringstream oss;
		oss << "MazeEngine --- FPS: " << fps << " DT: " << dt;
		oss << " --- rx: " << radiansX << " ry: " << radiansY;
		oss << " --- W: " << keys[0] << " A: " << keys[1] << " S: " << keys[2] << " D: " << keys[3];
		std::string title = oss.str();
		glfwSetWindowTitle(window, title.c_str());
	}
	return 0;
}