#include "main.hpp"
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
	if (key == GLFW_KEY_W && action == GLFW_PRESS && (mods >> 1) & 1) glfwSetWindowShouldClose(window, GLFW_TRUE);
	if (key == GLFW_KEY_R && action == GLFW_PRESS) reloadShaders = true;
}
unsigned u_worldMatrix, u_rotation, u_camera, u_view;
void getLocations(int *shaderProgram) {
	u_worldMatrix = glGetUniformLocation(*shaderProgram, "u_worldMatrix");
	u_rotation = glGetUniformLocation(*shaderProgram, "u_rotation");
	u_camera = glGetUniformLocation(*shaderProgram, "u_camera");
	u_view = glGetUniformLocation(*shaderProgram, "u_view");
}
unsigned vectorFloatBuffer (std::vector<float> *vector, int *shaderProgram, std::string location) {
	unsigned buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, vector->size() * sizeof(float), vector->data(), GL_STATIC_DRAW);
	unsigned a_location = glGetAttribLocation(*shaderProgram, location.c_str());
	glVertexAttribPointer(a_location, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(a_location);
	return buffer;
}
typedef struct plane {
	glm::vec4 normal;
	plane (glm::vec3 a, glm::vec3 b, glm::vec3 c) {
		normal = glm::vec4(glm::normalize(glm::cross(a - b, c - b)), -glm::dot(glm::cross(a - b, c - b), a));
	}
	float distance (glm::vec3 point) {
		return abs(normal.x * point.x + normal.y * point.y + normal.z * point.z + normal.w);
	}
	float getX (float y, float z) {
		return (-normal.y * y - normal.z * z - normal.w) / normal.x;
	}
	float getY (float x, float z) {
		return (-normal.x * x - normal.z * z - normal.w) / normal.y;
	}
	float getZ (float x, float y) {
		return (-normal.x * x - normal.y * y - normal.w) / normal.z;
	}
} plane;
int notmain() {
	std::vector<float> vertices {
		-1.0f, -1.0f,  0.0f,
		-1.0f,  1.0f,  0.0f,
		 1.0f, -1.0f,  0.0f,
		-1.0f,  1.0f,  0.0f,
		 1.0f, -1.0f,  0.0f,
		 1.0f,  1.0f,  0.0f,
	};
	std::vector<float> normals {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};
	std::vector<float> UV {
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
	};
	// readStl("./meshes/object2.stl", &vertices, &normals);
	// readPly("./meshes/object6.ply", &vertices, &normals);
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	// glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
	// glfwWindowHint(GLFW_MAXIMIZED, true);
	GLFWwindow* window = glfwCreateWindow(800, 600, "MazeEngine", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetWindowFocusCallback(window, windowFocus);
	glfwSetKeyCallback(window, keyEvent);
	gladLoadGL();
	
	glEnable(GL_DEBUG_OUTPUT);
	
	int shaderProgram = compileShaders();
	
	unsigned vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	unsigned vertexBuffer = vectorFloatBuffer(&vertices, &shaderProgram, "a_vertices");
	unsigned normalBuffer = vectorFloatBuffer(&normals, &shaderProgram, "a_normals");
	unsigned uvBuffer = vectorFloatBuffer(&UV, &shaderProgram, "a_UV");
	// unsigned vao2;
	// glGenVertexArrays(1, &vao2);
	// glBindVertexArray(vao2);
	
	// glm::vec3 a(1.0f, 0.0f, 1.0f);
	// glm::vec3 b(0.0f, 0.1f, 0.0f);
	// glm::vec3 c(0.0f, 0.0f, 1.0f);
	// plane p(a, b, c);
	// float y1 = p.getY(-1.0f, -1.0f);
	// float y2 = p.getY(-1.0f,  1.0f);
	// float y3 = p.getY( 1.0f, -1.0f);
	// float y4 = p.getY( 1.0f,  1.0f);
	// std::vector<float> vertices2 = {-1.0f, y1, -1.0f, -1.0f, y2, 1.0f, 1.0f, y3, -1.0f, -1.0f, y2, 1.0f, 1.0f, y3, -1.0f, 1.0f, y4, 1.0f};
	// unsigned vertexBuffer2 = vectorFloatBuffer(&vertices2, &shaderProgram, "a_vertices");
	
	std::string name = "./image.tiff";
	const char *path = name.c_str();
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(path, 0);
	FIBITMAP *image = FreeImage_Load(fif, path, BMP_DEFAULT);
	unsigned char *bits = FreeImage_GetBits(image);
	unsigned imageWidth = FreeImage_GetWidth(image);
	unsigned imageHeight = FreeImage_GetHeight(image);
	unsigned bpp = FreeImage_GetBPP(image);
	std::cout << "Width: " << imageWidth << ", Height: " << imageHeight << ", BPP: " << bpp << std::endl;
	unsigned gl_texID;
	glGenTextures(1, &gl_texID);
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, imageWidth, imageHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, bits);
	FreeImage_Unload(image);
	
	// std::cout << read("./todo.txt") << std::endl;
	
	getLocations(&shaderProgram);
	
	glm::mat4 projection, view;
	glm::vec3 camera = glm::vec3(0.0f, 1.0f, 1.0f);
	glm::vec3 target;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 rotationX, rotationY, rotation, worldMatrix;
	
	double lastX, lastY, posX, posY, deltaX, deltaY;
	float angleX = 0.0f, angleY = 220.0f, locX = 0.0f, locY = 0.0f, max = 3.0f, acc = 0.5f, dec = 0.5f;
	float fps = 0.0f, fpsSmoothing = 0.99f, dt = 0.0f, radiansX, radiansY;
	std::vector<float> speed {0.0f, 0.0f, 0.0f, 0.0f};
	int width, height;
	
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
		
		// Prevent dividing aspect ratio dividing by zero error when minimized
		if (!glfwGetWindowAttrib(window, GLFW_ICONIFIED)) {
			glfwGetFramebufferSize(window, &width, &height);
			glViewport(0, 0, width, height);
		}
		
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
			// camera.x -= speed[x] * sin(angle) * dir * dt;
			// camera.z += speed[x] * cos(angle) * dir * dt;
		}
		
		projection = glm::perspective(glm::radians(90.0f), (float) width / (float) height, 0.1f, 50.0f);
		rotationX = glm::rotate(glm::mat4(1.0f), radiansX, glm::vec3( 0.0f, -1.0f, 0.0f));
		rotationY = glm::rotate(glm::mat4(1.0f), radiansY, glm::vec3(-1.0f,  0.0f, 0.0f));
		rotation = rotationX * rotationY;
		target = glm::vec3(rotation * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		view = glm::lookAt(camera, camera + target,	up);
		worldMatrix = projection * view;
		worldMatrix = glm::mat4(1.0f);
		
		glUniformMatrix4fv(u_worldMatrix, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glUniformMatrix4fv(u_rotation, 1, GL_FALSE, glm::value_ptr(rotation));
		glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(u_camera, 1, glm::value_ptr(camera));
		
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
		// glBindVertexArray(vao2);
		// glDrawArrays(GL_TRIANGLES, 0, vertices2.size() / 3);
		
		glfwSwapBuffers(window);
		// glFlush();
		glfwPollEvents();
		
		dt = glfwGetTime() - t;
		fps = (1.0f / dt) * fpsSmoothing + fps * (1.0f - fpsSmoothing);
		
		std::ostringstream oss;
		oss << "MazeEngine --- FPS: " << fps << " DT: " << dt;
		oss << " --- rx: " << radiansX << " ry: " << radiansY;
		oss << " --- W: " << keys[0] << " A: " << keys[1] << " S: " << keys[2] << " D: " << keys[3];
		std::string title = oss.str();
		glfwSetWindowTitle(window, title.c_str());
	}
	return 0;
}
int *x = 1;
int *y;
memcpy();