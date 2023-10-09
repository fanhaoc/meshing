#include <iostream>
#define GLFW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Scene {
public:
	GLFWwindow* window;
	Scene() {
		// ��ʼ��glfw
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// ��ʼ������
		window = glfwCreateWindow(800, 600, "meshing", NULL, NULL);
		if (window == NULL) {
			printf("open window failed");
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);

		// ��ʼ��glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			printf("failed to initialize GLAD");
			glfwTerminate();
		}
		glViewport(0, 0, 800, 600);
	}
	// ѭ������
	void renderLoop() {
		// ��ʼ��һЩ��Ⱦ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		unsigned int VAO;
		

		// ѭ����Ⱦ
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