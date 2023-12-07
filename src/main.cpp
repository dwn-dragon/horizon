#include <iostream>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char const *argv[]) {
	
	if (!glfwInit()) {
		std::cerr << "GLFW Init error" << std::endl;
		return 1;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "Window title", nullptr, nullptr);
	if (!window) {
		std::cerr << "Window creation error" << std::endl;

		glfwTerminate();
		return 1;
	}

	//	OpenGL Init

	glfwMakeContextCurrent(window);
	if (gl3wInit()) {
		std::cerr << "GL3W Init error" << std::endl;

		glfwTerminate();
		return 1;
	}

	auto res = glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << res << std::endl;

	//	GLFW Setup

	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	//	Main Loop

	while(!glfwWindowShouldClose(window)) {

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

	//	Clean up

	glfwTerminate();
	return 0;
}
