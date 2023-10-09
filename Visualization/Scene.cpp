#include <iostream>
#define GLFW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Scene {
public:
	GLFWwindow* window;
	Scene() {
		// 初始化glfw
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// 初始化窗口
		window = glfwCreateWindow(800, 600, "meshing", NULL, NULL);
		if (window == NULL) {
			printf("open window failed");
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);

		// 初始化glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			printf("failed to initialize GLAD");
			glfwTerminate();
		}
		glViewport(0, 0, 800, 600);
	}
	// 循环绘制
	void renderLoop() {
		// 初始化一些渲染数据
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		unsigned int VAO;
		

		// 循环渲染
		while (!glfwWindowShouldClose(window))
		{
			processInput();

			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
		return;
	}
	void processInput() {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}
private:
	float vertices[9] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
};