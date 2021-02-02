#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

//�������¼�
void onKeyPressed(GLFWwindow* window)
{
	//Esc�����¼�
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//���ڴ�С�ı�ص�
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
	//���õ�ǰ������
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//����viewport
	glViewport(0, 0, 800, 480);
	glfwSetFramebufferSizeCallback(window, onFrameSizeChanged);
	
	//��ѭ��
	while (!glfwWindowShouldClose(window))
	{
		onKeyPressed(window);

		//����������ɫ
		glClearColor(0.1f, 0.5f, 0.2f, 1.f);
		//����
		glClear(GL_COLOR_BUFFER_BIT);

		//��������
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//�ͷ���Դ
	glfwTerminate();

	return 0;
}