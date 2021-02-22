#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

class ShaderProgram
{
public:
	ShaderProgram(const char* vertPath, const char* fragmentPath);
	~ShaderProgram();


	void use();
	unsigned int getID() { return _programID; }
private:
	unsigned int _programID = 0;//shader program id
};

ShaderProgram::ShaderProgram(const char* vertPath, const char* fragmentPath)
{
	
	std::string vertSource, fragmentSource;
	std::ifstream vertFile, fragmentFile;
	vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//���ļ�
		vertFile.open(vertPath);
		fragmentFile.open(fragmentPath);

		//��ȡ�ļ�����������
		std::stringstream vertStream, fragmentStream;
		vertStream << vertFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		//�ر��ļ�
		vertFile.close();
		fragmentFile.close();
		//ת����������
		vertSource = vertStream.str();
		fragmentSource = fragmentStream.str();
	}
	catch (const std::ifstream::failure& e)
	{
		std::cout << "Error: read file failure!" << e.what() << std::endl;
	}

	//����shader
	unsigned int vertShader, fragmentShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertCode = vertSource.c_str();
	const char* fragmentCode = fragmentSource.c_str();

	//����Դ��
	glShaderSource(vertShader, 1, &vertCode, NULL);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	//����shader
	glCompileShader(vertShader);
	glCompileShader(fragmentShader);

	//����program
	_programID = glCreateProgram();
	glAttachShader(_programID, vertShader);
	glAttachShader(_programID, fragmentShader);
	glLinkProgram(_programID);

	//ɾ��shader
	glDeleteShader(vertShader);
	glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::use()
{
	glUseProgram(_programID);
}


#endif // !__SHADER_PROGRAM_H__

