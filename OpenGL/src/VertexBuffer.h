#pragma once

// Generate a name for a new buffer.
// e.g. buffer = 2
// ֻ�ǲ���һ��id��buffer�ã���û�в������buffer object
// 
// Make the new buffer active, creating it if necessary.
// Kind of like:
// if (opengl->buffers[buffer] == null)
//     opengl->buffers[buffer] = new Buffer()
// opengl->current_array_buffer = opengl->buffers[buffer]
// ��������buffer���Ҹ�id�󶨣�����֪����С��
// 
// Upload a bunch of data into the active array buffer
// Kind of like:
// opengl->current_array_buffer->data = new byte[sizeof(points)]
// memcpy(opengl->current_array_buffer->data, points, sizeof(points))
class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};