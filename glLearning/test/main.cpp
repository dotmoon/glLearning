#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include "ShaderProgram.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float screenWidth = 800;//屏宽
float screenHeight = 480;//屏高

//函数声明
void onKeyPressed(GLFWwindow* window);

//加载纹理
unsigned int loadTexture(const char* fileName, int* width, int* height)
{
	int nrchannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(fileName, width, height, &nrchannels, 0);

	//生成纹理
	unsigned int texture = 0;
	if (data)
	{
		glGenTextures(1, &texture);

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, *width, *height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);//生成多级渐远纹理

		//释放内存
		stbi_image_free(data);
	}
	else
		std::cout << "Failed to load texture:" << fileName << std::endl;
	
	return texture;
}

void test3D(GLFWwindow* window)
{

	//通过model matrix、view matrix、projection matrix的变换，实现3D效果
	int width, height;
	unsigned int textureID = loadTexture("images/course_bg0.jpg", &width, &height);

	if (textureID == 0)//纹理加载失败
		return;

	//设置模型矩阵
	glm::mat4 model(1.f);
	//model = glm::rotate(model, glm::radians(-55.f), glm::vec3(1.f, 0.f, 0.f));

	//设置观察矩阵
	glm::mat4 view(1.f);
	view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));

	//投影矩阵
	glm::mat4 projection(1.f);
	projection = glm::perspective(glm::radians(45.f), screenWidth / screenHeight, 0.1f, 100.f);

	//顶点数组
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.f, 0.f, 0.f,
	//	-0.5f, 0.5f, 0.f, 0.f, 1.f,
	//	0.5f, 0.5f, 0.f, 1.f, 1.f,
	//	0.5f, -0.5f, 0.f, 1.f, 0.f

	//	-0.5f, -0.5f, 0.5f, 1.f, 0.f,
	//	-0.5f, 0.5f, 0.5f, 1.f, 1.f,
	//	0.5f, 0.5f, 0.5f, 0.f, 1.f,
	//	0.5f, -0.5f, 0.5f, 0.f, 0.f
	//};

	glEnable(GL_DEPTH_TEST);//开启深度测试

	float vertices[] = {
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

	//顶点索引数组
	unsigned indeies[] = {
		0, 1, 2,
		2, 3, 0,

		
		//1, 5, 4,
		//4, 0, 1,

		/*2, 6, 5,
		5, 1, 2,

		
		3, 7, 6,
		6, 2, 3,

		0, 4, 7,
		7, 3, 0,*/

		4, 5, 6,
		6, 7, 4

	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeies), indeies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	auto shaderProgram = ShaderProgram("shaders/test3D.vs", "shaders/test3D.fs");
	while (!glfwWindowShouldClose(window))
	{
		onKeyPressed(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清屏

		model = glm::rotate(model, (float)glfwGetTime()/ 10000 * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		unsigned int transformLoc = glGetUniformLocation(shaderProgram.getID(), "model");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

		transformLoc = glGetUniformLocation(shaderProgram.getID(), "view");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(view));

		transformLoc = glGetUniformLocation(shaderProgram.getID(), "projection");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projection));

		glBindTexture(GL_TEXTURE_2D, textureID);//绑定纹理
		shaderProgram.use();
		glBindVertexArray(VAO);
		//绘制三角形
		//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)0);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//std::cout << glGetError() << std::endl;

		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void testShaderProgram(GLFWwindow* window)
{
	//为什么左下角是黑色？
	//顶点着色器将顶点坐标作为顶点颜色，则左下角的颜色值为vec3(-0.5f, -0.5f, 0.f);
	//因为颜色值标准为0 - 1，所以该颜色最终格式化为了(0.f, 0.f, 0.f)即黑色
	//同时在进行计算时，比较靠近左下角的点算出来颜色值为负值，所以和顶点一样都显示为黑色
	float verteies[] = 
	{
		-1.f, -1.f, 0.f, 0.f, 0.f,
		-1.f, 1.f, 0.f, 0.f, 1.f,
		1.f, 1.f, 0.f, 1.f, 1.f,
		-1.f, -1.f, 0.f, 0.f, 0.f,
		1.f, 1.f, 0.f, 1.f, 1.f,
		1.f, -1.f, 0.f, 1.f, 0.f
	};

	////设置顶点对应的纹理坐标
	//float textureCoords[] =
	//{

	//};

	//设置纹理环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//设置纹理过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, texture;
	texture = loadTexture("images/course_bg0.jpg", &width, &height);

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verteies), verteies, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	auto shaderProgram = ShaderProgram("shaders/testVert.vs", "shaders/testFrag.fs");

	while (!glfwWindowShouldClose(window))
	{
		onKeyPressed(window);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 trans(1.f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 1.f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.f, 0.f, 1.f));
		

		unsigned int transformLoc = glGetUniformLocation(shaderProgram.getID(), "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		shaderProgram.use();
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}


//绘制三角形
void drawTriangle(GLFWwindow* window)
{

	//顶点着色器源码
	const char* vertexSource = "\n\
		#version 330 core\n\
		layout(location = 0) in vec3 aPos;\n\
		layout(location = 1) in vec3 aColor;\n\
		out vec3 ourColor;\n\
		\n\
		void main()\n\
		{\n\
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n\
			ourColor = aColor;\n\
		}\n\
		\0\
		";

	const char* fragmentSource = "\n\
		#version 330 core\n\
		out vec4 FragColor;\n\
		in vec3 ourColor;\n\
		void main()\n\
		{\n\
			FragColor = vec4(ourColor, 1.f);\n\
		}\n\
		\0";

	//顶点数组
	float vertexs[] = {
		0.f, 0.f, 0.f, 1.f, 0.f, 0.f,
		-1.f, -1.f, 0.f, 0.f, 1.f, 0.f,
		1.f, -1.f, 0.f, 0.f, 0.f, 1.f,

		-1.f, 1.f, 0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
		1.f, 1.f, 0.f, 0.f, 0.f, 1.f,

		1.f, 1.f, 0.f, 0.f, 0.f, 1.f,
		0.f, 0.f, 0.f, 0.f, 1.f, 0.f,
		1.f, -1.f, 0.f, 1.f, 0.f, 0.f,
	};

	unsigned int VAO;
	//生成VAO
	glGenVertexArrays(1, &VAO);
	
	unsigned int VBO;
	//生成VBO
	glGenBuffers(1, &VBO);

	//绑定VAO
	glBindVertexArray(VAO);

	//绑定VBO到顶点缓冲
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//复制数据到顶点缓冲
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);

	unsigned int vertexShader;
	//创建顶点着色器shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//附加源码到着色器上
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//编译顶点着色器
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	//检查是否编译成功
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Compile Vertex Error:" << infoLog << std::endl;
		return;
	}

	//创建片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//附加源码
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//编译shadre
	glCompileShader(fragmentShader);
	//查看编译是否成功
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Compile Fragment Error:" << infoLog << std::endl;
		return;
	}

	//创建着色器程序
	unsigned int program;
	program = glCreateProgram();
	//附加顶点着色器和片段着色器
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	//链接着色器
	glLinkProgram(program);

	//检查链接是否成功
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Link Error:" << infoLog << std::endl;
		return;
	}

	//释放顶点着色器和片段着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//告诉program顶点数据布局
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//启用顶点属性
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	
	while (!glfwWindowShouldClose(window))
	{
		onKeyPressed(window);

		//设置清屏颜色
		glClearColor(0.1f, 0.5f, 0.2f, 1.f);
		//清屏
		glClear(GL_COLOR_BUFFER_BIT);
		//激活program
		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertexs) / sizeof(float) / 6);

		//解绑vao
		glBindVertexArray(0);

		//std::cout << glGetError() << std::endl;
		//交互缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(program);
	
}

//绘制矩形，使用EBO
void drawRectangle(GLFWwindow* window)
{

	//顶点着色器源码
	const char* vertexSource = "\n\
		#version 330 core\n\
		layout(location = 0) in vec3 aPos;\n\
		\n\
		void main()\n\
		{\n\
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n\
		}\n\
		\0\
		";

	const char* fragmentSource = "\n\
		#version 330 core\n\
		out vec4 FragColor;\n\
		void main()\n\
		{\n\
			FragColor = vec4(0.5f, 0.1f, 0.3f, 1.f);\n\
		}\n\
		\0";

	const char* fragmentSource2 = "\n\
		#version 330 core\n\
		out vec4 FragColor;\n\
		uniform vec4 ourColor;\n\
		void main()\n\
		{\n\
			FragColor = ourColor;\n\
		}\n\
		\0";

	float vertexs[] = 
	{
		-0.5f, -0.5f, 0.f,
		-0.5f, 0.5f, 0.f,
		0.5f, 0.5f, 0.f,
		0.5f, -0.5f, 0.f
	};

	unsigned int indexs[] = 
	{
		0, 1, 2,
		//0, 2, 3
	};

	unsigned int indexs2[] =
	{
		0, 2, 3
	};
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs), indexs, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//解绑vbo vao
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned int VAO2, VBO2, EBO2;
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs2), indexs2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned int vertexShader, fragmentShader, program;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int vertexShader2, fragmentShader2, program2;
	vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader2, 1, &vertexSource, NULL);
	glShaderSource(fragmentShader2, 1, &fragmentSource2, NULL);

	glCompileShader(vertexShader2);
	glCompileShader(fragmentShader2);

	program2 = glCreateProgram();
	glAttachShader(program2, vertexShader2);
	glAttachShader(program2, fragmentShader2);
	glLinkProgram(program2);

	glDeleteShader(vertexShader2);
	glDeleteShader(fragmentShader2);

	while (!glfwWindowShouldClose(window))
	{
		onKeyPressed(window);
		
		glClearColor(0.1f, 0.3f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(program);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//解绑vao
		glBindVertexArray(0);

		glUseProgram(program2);
		glBindVertexArray(VAO2);
		//获取ourColor的位置
		int location = glGetUniformLocation(program2, "ourColor");
		//更新ourColor的值
		float redValue = sin(glfwGetTime()) / 2.f + 0.5f;
		glUniform4f(location, redValue, 0.2f, 0.1f, 1.f);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//解绑vao
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(program);
}

//检查键盘事件
void onKeyPressed(GLFWwindow* window)
{
	//Esc键盘事件
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//窗口大小改变回调
void onFrameSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	auto window = glfwCreateWindow(800, 480, "testGLFW", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//设置当前上下文
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//设置viewport
	glViewport(0, 0, 800, 480);
	glfwSetFramebufferSizeCallback(window, onFrameSizeChanged);

	glClearColor(0.1f, 0.5f, 0.2f, 1.f);//设置清屏颜色

	//drawTriangle(window);
	//drawRectangle(window);
	//testShaderProgram(window);
	test3D(window);

	getchar();
	
	//主循环
	while (!glfwWindowShouldClose(window))
	{
		onKeyPressed(window);

		//设置清屏颜色
		glClearColor(0.1f, 0.5f, 0.2f, 1.f);
		//清屏
		glClear(GL_COLOR_BUFFER_BIT);

		//交互缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//释放资源
	glfwTerminate();

	return 0;
}