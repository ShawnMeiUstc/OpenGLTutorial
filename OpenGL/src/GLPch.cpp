#include "GLPch.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ") happens in FUNCTION: "
			<< function << "\nFILE: " << file << "\nLINE: "
			<< line << std::endl;
		return false;
	}
	return true;
}