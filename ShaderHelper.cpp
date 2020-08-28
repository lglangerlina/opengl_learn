#include "ShaderHelper.h"

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

ShaderHelper::ShaderHelper(const GLchar * vertexPath, const GLchar * fragmentPath)
{

	//1. 从本地文件中获取着色器code
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	

	vShaderFile.exceptions(std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::badbit);

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "catch an error:" << std::endl;
	}

	const GLchar* vShaderCode = vertexCode.c_str(); 
	const GLchar* fShaderCode = fragmentCode.c_str();

	//2.编译着色器
	GLuint vertex, fragment;
	GLint success;
	GLchar info[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, info);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, info);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, nullptr, info);
		std::cout << "link program failed:" << info <<  std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

ShaderHelper::~ShaderHelper()
{
}

void ShaderHelper::use()
{
	glUseProgram(program);
}
