#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
		//事件
		glfwPollEvents();
	}

	//释放资源
	glfwTerminate();

	return 0;
}