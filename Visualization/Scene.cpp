#include <iostream>
#include <vector>
#include "Model.cpp"
#include "Shader.h"
#define GLFW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Scene {
public:
	GLFWwindow* window;
	std::vector<Model*> models;
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
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		Shader* shader = new Shader("C:\\Users\\19288\\Desktop\\coding\\cxx\\meshing\\Visualization\\ShaderSource\\normalVert.txt", "C:\\Users\\19288\\Desktop\\coding\\cxx\\meshing\\Visualization\\ShaderSource\\normalFrag.txt");

		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		
		// 循环渲染
		while (!glfwWindowShouldClose(window))
		{
			processInput();

			glClear(GL_COLOR_BUFFER_BIT);

			
			//for (int i = 0, len = models.size(); i < len; i++) {
			//	glBufferData(GL_ARRAY_BUFFER, sizeof(models[i]->vertices), &models[i]->vertices, GL_STATIC_DRAW);
			//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(models[i]->indices), &models[i]->indices, GL_STATIC_DRAW);
			//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			//}
			shader->use();
			glBindVertexArray(VAO);			
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
		return;
	}
	// 键盘输入处理函数
	void processInput() {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}
	// 添加需要绘制的模型
	void add(Model* model) {
		models.push_back(model);
	}

	float vertices[12] = {
		0.5f, 0.5f, 0.0f,   // 右上角
		0.5f, -0.5f, 0.0f,  // 右下角
		-0.5f, -0.5f, 0.0f, // 左下角
		-0.5f, 0.5f, 0.0f   // 左上角
	};
	unsigned int indices[6] = {
		// 注意索引从0开始! 
		// 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
		// 这样可以由下标代表顶点组合成矩形

		0, 1, 3, // 第一个三角形
		1, 2, 3  // 第二个三角形
	};
};