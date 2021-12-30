#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <iostream>

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "glew init error" << std::endl;
 	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	float position[] = {
		-0.5f, -0.5,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	// Generate a name for a new buffer.
	// e.g. buffer = 2
	// 只是产生一个id给buffer用，并没有产生真的buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	// Make the new buffer active, creating it if necessary.
	// Kind of like:
	// if (opengl->buffers[buffer] == null)
	//     opengl->buffers[buffer] = new Buffer()
	// opengl->current_array_buffer = opengl->buffers[buffer]
	// 真正产生buffer并且跟id绑定（并不知道大小）
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// Upload a bunch of data into the active array buffer
	// Kind of like:
	// opengl->current_array_buffer->data = new byte[sizeof(points)]
	// memcpy(opengl->current_array_buffer->data, points, sizeof(points))
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}