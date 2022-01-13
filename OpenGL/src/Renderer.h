#pragma once

class VertexArray;
class IndexBuffer;
class Shader;
class Renderer
{
public:
	void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
	void Clear() const;
};