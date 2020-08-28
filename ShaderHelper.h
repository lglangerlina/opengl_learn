#pragma once
#include "glad/glad.h"

class ShaderHelper
{
public:
	ShaderHelper(const GLchar* vertexPath, const GLchar* fragmentPath);
	~ShaderHelper();

	void use();

private:
	GLuint program;
};

