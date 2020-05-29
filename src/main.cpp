#include "MazeEngine.hpp"
/*
* TODO:
* Standard Uniforms for shaders
* Easy way to add custom uniforms
* Move main.cpp to seperate test folder
* Rename lib to dep
* Seperate all header files and implimentation files
* Build library instead of exe(?)
* Common shaders as enums
* Better way of packaging shaders, resources, etc. (Most likely move shaders into string literals in header files)
* Keyboard handling
*/
/* begin copy-paste old code */

bool mouseInput = false;
void windowFocus (GLFWwindow* window, int focused) {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	mouseInput = false;
}

/* end copy-paste old code */
using namespace MazeEngine;
int main() {
	Window win = Window("Test", 800, 600);
	Shader shader = Shader("shaders/vert.glsl", "shaders/static.glsl");
	Mesh mesh = Mesh("meshes/plane.ply");
	// Mesh mesh = Mesh("meshes/object.ply");
	Object object = Object(mesh, shader);
	// Object object2 = Object(mesh2, shader);
	/* begin copy-paste old code */
	unsigned u_worldMatrix = glGetUniformLocation(shader.getId(), "u_worldMatrix");
	unsigned u_rotation = glGetUniformLocation(shader.getId(), "u_rotation");
	unsigned u_camera = glGetUniformLocation(shader.getId(), "u_camera");
	unsigned u_view = glGetUniformLocation(shader.getId(), "u_view");
	unsigned u_time = glGetUniformLocation(shader.getId(), "u_time");

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

	glfwGetCursorPos(win.window, &lastX, &lastY);

	/* end copy-paste old code */
	while (win.active()) {
		win.clear();
		/* begin copy-paste old code */

			// Prevent dividing aspect ratio dividing by zero error when minimized
		if (!glfwGetWindowAttrib(win.window, GLFW_ICONIFIED)) {
			glfwGetFramebufferSize(win.window, &width, &height);
			glViewport(0, 0, width, height);
		}
		
		if (glfwGetMouseButton(win.window, GLFW_MOUSE_BUTTON_LEFT)) {
			glfwSetInputMode(win.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (!mouseInput) glfwGetCursorPos(win.window, &lastX, &lastY);
			mouseInput = true;
		}
		if (glfwGetKey(win.window, GLFW_KEY_ESCAPE)) {
			glfwSetInputMode(win.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			mouseInput = false;
		}
		if (mouseInput) {
			glfwGetCursorPos(win.window, &posX, &posY);
			
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
		
		// if (angleY > 269.9f) angleY = 269.9f;
		// if (angleY < 90.1f) angleY = 90.1f;
		
		radiansX = glm::radians(angleX);
		radiansY = glm::radians(angleY);
		
		projection = glm::perspective(90.0f, (float) width / (float) height, 0.1f, 20.0f);
		rotationX = glm::rotate(glm::mat4(1.0f), radiansX, glm::vec3( 0.0f, -1.0f, 0.0f));
		rotationY = glm::rotate(glm::mat4(1.0f), radiansY, glm::vec3(-1.0f,  0.0f, 0.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
		rotation = rotationX * rotationY;
		// target = glm::vec3(rotation * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		// view = glm::lookAt(camera, camera + target, up);
		worldMatrix = projection * rotation * scale;
		
		glUniformMatrix4fv(u_worldMatrix, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glUniformMatrix4fv(u_rotation, 1, GL_FALSE, glm::value_ptr(rotation));
		glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(u_camera, 1, glm::value_ptr(camera));
		glUniform1f(u_time, glfwGetTime());

		/* end copy-paste old code */
		object.draw();
		// object2.draw();
		win.draw();
	}
	return 0;
}