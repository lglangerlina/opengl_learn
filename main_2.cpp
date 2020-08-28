#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;


float vertices[] = {
	 -0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};
//顶点数组对象:VAO,描述顶点属性
//顶点缓冲对象:VBO,管理顶点数据内存， 在GPU上存储大量顶点，通过VBO一次性将大量顶点数据发送到显卡上，减少CPU的使用
//索引缓冲对象:EBO/IBO

//顶点着色器：将输入的顶点坐标转换为另一种顶点坐标
//几何着色器：通过输入一系列的顶点坐标，构造出新的图元形状等
//片段着色器：计算最终颜色
//GPU中没有默认的顶点着色器和片段着色器，所以必须自定义至少一个顶点着色器和片段着色器

//顶点着色器
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void DrawTraple()
{

	unsigned int VBO;
	glGenBuffers(1, &VBO);//生成一个VBO对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定缓冲对象到GL_ARRAY_BUFFER目标上
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//复制数据到缓冲的内存中

	//告诉opengl如何解析顶点数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//创建两个着色器 顶点着色器和片段着色器
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建一个顶点着色器
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);//加载着色器源码
	glCompileShader(vertexShader);//编译着色器

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		cout << "compile sharder failed" << endl;
	}


	//片段着色器
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		cout << "create fragment shader failed" << endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();//创建着色器程序
	glAttachShader(shaderProgram, vertexShader); //着色器附加到程序上
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);//链接着色器程序
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		cout << "link shader program failed" << endl;
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
	}

	glUseProgram(shaderProgram);//使用该程序
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);//之前的着色器就没用了，删除

	glDrawArrays(GL_TRIANGLES, 0, 3);

}



//绘制三角形
int main_2()
{

	glfwInit();
	GLFWwindow *window = glfwCreateWindow(600, 800, "window_2", nullptr, nullptr);
	if (window == nullptr) {
		cout << "create window failed" << endl;
		goto END;
	}
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	while (!glfwWindowShouldClose(window))
	{
		//inout
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}

		glClearColor(0.1, 0.2, 0.5, 0.5);
		glClear(GL_COLOR_BUFFER_BIT);

		DrawTraple();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


END:
	glfwTerminate();
	return 0;
}