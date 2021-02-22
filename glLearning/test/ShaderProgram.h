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
		//打开文件
		vertFile.open(vertPath);
		fragmentFile.open(fragmentPath);

		//读取文件到数据流中
		std::stringstream vertStream, fragmentStream;
		vertStream << vertFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		//关闭文件
		vertFile.close();
		fragmentFile.close();
		//转换数据流到
		vertSource = vertStream.str();
		fragmentSource = fragmentStream.str();
	}
	catch (const std::ifstream::failure& e)
	{
		std::cout << "Error: read file failure!" << e.what() << std::endl;
	}

	//创建shader
	unsigned int vertShader, fragmentShader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertCode = vertSource.c_str();
	const char* fragmentCode = fragmentSource.c_str();

	//附加源码
	glShaderSource(vertShader, 1, &vertCode, NULL);
	glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
	//编译shader
	glCompileShader(vertShader);
	glCompileShader(fragmentShader);

	//创建program
	_programID = glCreateProgram();
	glAttachShader(_programID, vertShader);
	glAttachShader(_programID, fragmentShader);
	glLinkProgram(_programID);

	//删除shader
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

