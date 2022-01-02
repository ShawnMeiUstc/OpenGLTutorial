#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1,
		VERTEX,
		FRNGMENT
	};

	std::string line;
	ShaderType type = ShaderType::NONE;
	std::stringstream ss[2];
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRNGMENT;
			}
		}
		else
		{
			ss[static_cast<unsigned int>(type)] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*) _malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, log);
		std::cout << "Fail to Compile " << (GL_VERTEX_SHADER == type ? "vertex " : "fragment ") << "shader: \n" 
			<< log << std::endl;
	}
	return id;
}
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return(program);
}

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
	
	// Enable or disable a generic vertex attribute array
	glEnableVertexAttribArray(0);
	// index 0号属性
	// 每个顶点有size 2个GL_FLOAT
	// stride：每个顶点的所有属性占的总字节数
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 8, nullptr);
	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);
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

	glDeleteProgram(shader);
	glfwTerminate();
	return 0;
}