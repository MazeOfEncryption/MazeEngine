#define _USE_MATH_DEFINES
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
// Function for finding the index of an element in a vector
template <typename type>
int indexOf (type element, std::vector<type> array) {
	return std::distance(std::begin(array), std::find(std::begin(array), std::end(array), element));
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

/* end copy-paste old code */
using namespace MazeEngine;
int main() {
	Window win = Window("Test", 800, 600);
	Shader shader = Shader("shaders/vert.glsl", "shaders/static.glsl");
	Mesh mesh = Mesh("meshes/plane.ply");
	// Mesh mesh = Mesh("meshes/object.ply");
	Object object = Object(mesh, shader);
	Object player = Object();
	player.position = glm::vec3(0.0f, 0.0f, 1.0f);
	player.mass = 0.0125f;
	player.drag = 0.15f;
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
	float angleX = 0.0f, angleY = 220.0f, locX = 0.0f, locY = 0.0f, max = 3.0f, acc = 0.5f, dec = 0.25f;
	float fps = 0.0f, fpsSmoothing = 0.99f, lastTime = 0.0f;
	float gravity = 2.5f, jumpSpeed = 0.0f, jumpAcc = 50.0f;
	std::vector<float> speed {1.0f, 1.0f, 1.0f, 1.0f};
	int width, height;

	glfwSetWindowFocusCallback(win.window, windowFocus);
	glfwSetKeyCallback(win.window, keyEvent);
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
			
			angleX += (posX - lastX) / 10.0f;
			angleY += (posY - lastY) / 10.0f;
		
			lastX = posX;
			lastY = posY;
		}
		
		// if (angleY > 269.9f) angleY = 269.9f;
		// if (angleY < 90.1f) angleY = 90.1f;
		
		// if (glfwGetKey(win.window, GLFW_KEY_SPACE) && camera.y == 1.0f) {
		// 	jumpSpeed += jumpAcc * win.dt;
		// }
		// jumpSpeed -= gravity * win.dt;
		// camera.y += jumpSpeed * win.dt;
		// if (camera.y < 1.0f) {
		// 	camera.y = 1.0f;
		// 	jumpSpeed = 0.0f;
		// }
		// for (int x = 0; x < 4; x++) {
		// 	// If keys true add acc, else sub dec, coerce between zero and max
		// 	speed[x] = keys[x] ? (speed[x] + acc > max ? max : speed[x] + acc) : (speed[x] - dec < 0 ? 0 : speed[x] - dec);
		// 	// Compute angle, subtract 90 deg if sideways 
		// 	float angle = angleX * M_PI / 180 - (x % 2 ? M_PI / 2 : 0);
		// 	// Compute direction
		// 	float dir = x < 2 ? -1 : 1;
		// 	// Add speed in direction in dt
		// 	camera.x -= speed[x] * sin(angle) * dir * win.dt;
		// 	camera.z += speed[x] * cos(angle) * dir * win.dt;
		// }
		
		glm::vec3 direction = glm::vec3(0.0f);
		if(glfwGetKey(win.window, GLFW_KEY_W)) {
			direction += glm::vec3( 0.0f,  0.0f, -1.0f);
		}
		if(glfwGetKey(win.window, GLFW_KEY_S)) {
			direction += glm::vec3( 0.0f,  0.0f,  1.0f);
		}
		if(glfwGetKey(win.window, GLFW_KEY_A)) {
			direction += glm::vec3(-1.0f,  0.0f,  0.0f);
		}
		if(glfwGetKey(win.window, GLFW_KEY_D)) {
			direction += glm::vec3( 1.0f,  0.0f,  0.0f);
		}
		if (direction != glm::vec3(0.0f)) {
			player.force = glm::mat3(rotationX) * glm::normalize(direction);
		} else {
			player.force = glm::vec3(0.0f);
		}
		if (glfwGetKey(win.window, GLFW_KEY_SPACE) && player.position.y == 0.0f) {
			player.force.y += 15.0f;
		}
		player.force.y -= 0.75f;
		player.tick(win.dt);
		if (player.position.y < 0.0f) player.position.y = 0.0f;
		projection = glm::perspective(glm::radians(90.0f), (float) width / (float) height, 0.1f, 20.0f);
		rotationX = glm::rotate(glm::mat4(1.0f), glm::radians(angleX), glm::vec3( 0.0f, -1.0f, 0.0f));
		rotationY = glm::rotate(glm::mat4(1.0f), glm::radians(angleY), glm::vec3(-1.0f,  0.0f, 0.0f));
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(100.0f));
		rotation = rotationX * rotationY;
		target = glm::vec3(rotation * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
		view = glm::lookAt(player.position, player.position + target, up);
		worldMatrix = projection * view;

		glUniformMatrix4fv(u_worldMatrix, 1, GL_FALSE, glm::value_ptr(worldMatrix));
		glUniformMatrix4fv(u_rotation, 1, GL_FALSE, glm::value_ptr(rotation));
		glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(u_camera, 1, glm::value_ptr(player.position));
		glUniform1f(u_time, glfwGetTime());

		/* end copy-paste old code */
		object.draw();
		// object2.draw();
		win.draw();
	}
	return 0;
}