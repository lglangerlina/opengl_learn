#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;

void onWindowSizeChanged(GLFWwindow *window, int width, int height) {
	cout << "window size changed, window=" << window << ", w=" << width << ", h=" << height << endl;
}

void onWindowFrameBufferSizeChanged(GLFWwindow *window, int w, int h) {
	cout << "window framebuffer changed, window=" << window << ", w=" << w << ", h=" << h << endl;
	glViewport(0, 0, w, h);
}

//绘制窗口
int main_1()
{
	int sss = 0;
	sss += 10;
	cout << "sss=" << sss << endl;
	
	if (glfwInit() == GLFW_FALSE) {
		cout << "init glfw error" << std::endl;
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow *window = glfwCreateWindow(640, 480, "window_1", nullptr, nullptr);
	if (window) {
		glfwMakeContextCurrent(window);
		glfwSetWindowSizeCallback(window, GLFWwindowsizefun(onWindowSizeChanged));
		glfwSetFramebufferSizeCallback(window, GLFWframebuffersizefun(onWindowFrameBufferSizeChanged));
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		while (!glfwWindowShouldClose(window)) {
			glClearColor(0.1, 0.2, 0.3, 0.5);
			glClear(GL_COLOR_BUFFER_BIT);
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}

			glfwSwapBuffers(window);
			glfwPollEvents();


		}
	}
	else {
		cout << "create window failed" << endl;
	}
	
END:
	glfwTerminate();
	return 0;
}