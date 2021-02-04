#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//函数声明
void onKeyPressed(GLFWwindow* window);

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
void main()\n\
{\n\
	FragColor = vec4(0.1f, 0.1f, 0.0f, 1.f);\n\
}\n\
\0";


//顶点数组
float vertexs[] = {
	0.f, 0.f, 0.f,
	-1.f, -1.f, 0.f,
	1.f, -1.f, 0.f,

	-1.f, 1.f, 0.f,
	0.f, 0.f, 0.f,
	1.f, 1.f, 0.f,

	1.f, 1.f, 0.f,
	0.f, 0.f, 0.f,
	1.f, -1.f, 0.f,
};

//绘制三角形
void drawTriangle(GLFWwindow* window)
{
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
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//启用顶点属性
	glEnableVertexAttribArray(0);

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
		glDrawArrays(GL_TRIANGLES, 0, sizeof(vertexs) / sizeof(float) / 3);

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

	//drawTriangle(window);
	drawRectangle(window);

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