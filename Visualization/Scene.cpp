#include <iostream>
#include <vector>
#include "Model.cpp"
#include "Shader.h"
#include "Camera.h"
#include "controller.h"
#define GLFW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene {
public:
	GLFWwindow* window;
	// 组件

	// 绘制数据
	std::vector<Model*> models;
	std::vector<unsigned int> VAOS;
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

		// 初始化组件
		camera = new Camera(glm::vec3(0, 0, 3.0f), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));
		// 鼠标事件
		glfwSetCursorPosCallback(window, mouse_callback);
	}
	// 循环绘制
	void renderLoop() {
		// 初始化一些渲染数据
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);
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

		//unsigned int EBO;
		//glGenBuffers(1, &EBO);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		
		// mvp矩阵
		glm::mat4 modelMat = glm::mat4(1.0f);
		modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 viewMat = glm::mat4(1.0f);
		viewMat = camera->getViewMatrix();

		glm::mat4 projMat = glm::mat4(1.0f);
		projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

		// 循环渲染
		while (!glfwWindowShouldClose(window))
		{
			processInput();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			viewMat = camera->getViewMatrix();

			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			//for (int i = 0, len = models.size(); i < len; i++) {
			//	glBufferData(GL_ARRAY_BUFFER, sizeof(models[i]->vertices), &models[i]->vertices, GL_STATIC_DRAW);
			//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(models[i]->indices), &models[i]->indices, GL_STATIC_DRAW);
			//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			//}
			shader->use();
			glBindVertexArray(VAO);			
			glDrawArrays(GL_TRIANGLES, 0, 36);
			// glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(model->vertices), &model->vertices, GL_STATIC_DRAW);

		unsigned int EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model->indices), &model->indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		VAOS.push_back(VAO);

		glBindVertexArray(0);
	}



	float vertices[180] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
};