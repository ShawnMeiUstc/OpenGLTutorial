#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <memory>

#include "stb_image/stb_image.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "glm/glm.hpp"

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

#define ASSERT(x) if(!(x)) __debugbreak();
// 用GLCall调用每一个函数
#ifdef _DEBUG
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x
#endif

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);


#include "VertexBufferLayout.h"
#include "tests/Test.h"