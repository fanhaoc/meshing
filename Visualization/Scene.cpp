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
		
		// ѭ����Ⱦ
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
	// �������봦����
	void processInput() {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}
	// �����Ҫ���Ƶ�ģ��
	void add(Model* model) {
		models.push_back(model);
	}

	float vertices[12] = {
		0.5f, 0.5f, 0.0f,   // ���Ͻ�
		0.5f, -0.5f, 0.0f,  // ���½�
		-0.5f, -0.5f, 0.0f, // ���½�
		-0.5f, 0.5f, 0.0f   // ���Ͻ�
	};
	unsigned int indices[6] = {
		// ע��������0��ʼ! 
		// ����������(0,1,2,3)���Ƕ�������vertices���±꣬
		// �����������±��������ϳɾ���

		0, 1, 3, // ��һ��������
		1, 2, 3  // �ڶ���������
	};
};