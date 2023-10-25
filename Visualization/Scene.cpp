#include <iostream>
#include <vector>
#include "Shader.h"
#include "Camera.h"
#include "controller.h"
#include "Material.h"
#include "Lights/Light.h"
#include "Lights/LightSpot.h"
#include "Mesh.h"
#include "Model.h"
#define GLFW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

class Scene {
public:
	GLFWwindow* window;
	// 组件
	Material* material;
	
	// 数据根目录
	std::string rootPath = "C:\\Users\\19288\\Desktop\\coding\\cxx\\meshing";
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
		camera = new Camera(glm::vec3(0, 4.0f, 5.0f), 0.0f, 180.0f, glm::vec3(0, 1.0f, 0));
		// 鼠标事件
		glfwSetMouseButtonCallback(window, mouseButton_callback);

		glfwSetScrollCallback(window, scroll_callback);
	}
	// 循环绘制
	void renderLoop() {
		// 初始化一些渲染数据
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		 

		Shader* shader = new Shader((rootPath + "\\Visualization\\ShaderSource\\normalVert.vert").c_str(), (rootPath+"\\Visualization\\ShaderSource\\normalFrag.frag").c_str());

		//material = new Material(shader,
		//	LoadImageToGpu((rootPath + "\\sources\\container2.png").c_str(), GL_RGBA, GL_RGBA, Shader::DIFFUSE),
		//	LoadImageToGpu((rootPath + "\\sources\\container2_specular.png").c_str(), GL_RGBA, GL_RGBA, Shader::SPECULAR),
		//	LoadImageToGpu((rootPath + "\\sources\\matrix.jpg").c_str(), GL_RGB, GL_RGB, Shader::EMISSION),
		//	glm::vec3(1.0f, 1.0f, 1.0f),
		//	32.0f
		//);

		Light* lightD = new Light(glm::vec3(0.0f, 30.0f, -20.0f), glm::vec3(glm::radians(180.0f), glm::radians(-45.0f), 0.0f), glm::vec3(2.0f, 2.0f, 2.0f));
		Light* lightP = new Light(glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(glm::radians(45.0f), glm::radians(-45.0f), 0.0f), glm::vec3(0.0f, 2.0f, 2.0f));

		// Mesh* cube = new  Mesh(vertices);

		
		// mvp矩阵
		glm::mat4 modelMat = glm::mat4(1.0f);
		// modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 viewMat = glm::mat4(1.0f);

		glm::mat4 projMat = glm::mat4(1.0f);
		
		// 循环渲染
		while (!glfwWindowShouldClose(window))
		{
			processInput(window);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// 更新视角
			viewMat = camera->getViewMatrix();
			projMat = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(shader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

			// glUniform3f(glGetUniformLocation(shader->ID, "objColor"), 0.5f, 0.3f, 0.7f);
			glUniform3f(glGetUniformLocation(shader->ID, "ambientColor"), 0.5f, 0.5f, 0.5f);
			glUniform3f(glGetUniformLocation(shader->ID, "cameraPos"), camera->Position.x, camera->Position.y, camera->Position.z);

			shader->setUniform3f("lightD.pos", lightD->position);
			shader->setUniform3f("lightD.color", lightD->color);
			shader->setUniform3f("lightD.dirToLight", lightD->direction);

			shader->setUniform3f("lightP.pos", lightP->position);
			shader->setUniform3f("lightP.color", lightP->color);
			shader->setUniform3f("lightP.dirToLight", lightP->direction);
			shader->setUniform1f("lightP.constant", lightP->constant);
			shader->setUniform1f("lightP.linear", lightP->linear);
			shader->setUniform1f("lightP.quadratic", lightP->quadratic);

			//material->shader->setUniform3f("material.ambient", material->ambient);
			//material->shader->setUniform1i("material.diffuse", Shader::DIFFUSE);
			//material->shader->setUniform1i("material.specular", Shader::SPECULAR);
			//material->shader->setUniform1i("material.emission", Shader::EMISSION);
			//material->shader->setUniform1f("material.shininess", material->shininess);
			
			shader->use();

			// glBindVertexArray(VAO);
			
			// glDrawArrays(GL_POINTS, 0, position.size());
			for (int i = 0; i < models.size(); i++) {
				models[i]->Draw(shader);
			}
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
		return;
	}

	void add(Model* model) {
		models.push_back(model);
	}

	unsigned int LoadImageToGpu(const char* img, GLint internalFormat, GLenum format, int textureSlot) {
		// 纹理
		stbi_set_flip_vertically_on_load(true);

		unsigned int TexBuffer;

		glGenTextures(1, &TexBuffer);
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, TexBuffer);

		int width, height, nrChannel;
		unsigned char* data = stbi_load(img, &width, &height, &nrChannel, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "load image failed" << std::endl;
		}
		stbi_image_free(data);

		return TexBuffer;
	}


	float vertices[288] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	glm::vec3 cubePositions[10] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
	};
};