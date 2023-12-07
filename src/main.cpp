#include <iostream>
#include <thread>

#include "gfx/core.h"
#include "gfx/shaders.h"

constexpr float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

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

	//	Shaders

	gfx::Shader shader;

	shader = gfx::Shader{ "shaders/vertex.shader.glsl", "shaders/fragment.shader.glsl" };

	//	Model

	GLuint VAO, VBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	//	Main Loop

	shader.use();
	glBindVertexArray(VAO);

	while(!glfwWindowShouldClose(window)) {
		std::this_thread::sleep_for( std::chrono::duration<double, std::milli>(0.02f) );

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();    
	}

	//	Clean up

	glfwTerminate();
	return 0;
}
