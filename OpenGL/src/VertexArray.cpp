#include "VertexArray.h"
#include "Renderer.h"

/*各个参数含义是：
		0：			这个是该属性在顶点中的 index（即，它是第几个属性，从 0 开始）。本例中，每个顶点只有三维坐标这一个属性，
					因此直接放在 VBO 中 0 的位置（注：这也是 vertex shader 中开头所示的 location = 0 的含义）。如果顶点还其它的属性值，
					例如增加 2 个 floats 的颜色值，那么当再次调用该函数设置颜色属性时，这个参数就是 1（当然 shader 也要修改）。

		2：			该属性的的元素个数。每个顶点是 2 个 floats，因此就是 2。

		GL_FLOAT :  该属性中每个元素的类型。

		GL_FALSE :  元素是否需要数据被标准化（有符号数会被映射到[-1, 1] 之间，无符号的话就是[0, 1] 之间）。
					这是因为，OpenGL 只会绘制[-1, 1] 之间的坐标值，而将超出范围的值给 clip 掉。通常这里是被设置为 false，
					然后通常需要用户自行将最终传入的属性值标准化到[-1, 1] 之间。不过注意，这并非一定要通过直接修改输入的坐标才可以标准化的，
					而是还可以通过一些其它流程，例如通过投影映射（projective transformation）就可以（例如，在 RGB - D 点云绘制时就是如此）。
					即，我们只需要保证该属性的元素值最终在[-1, 1] 范围即可。

		2 * sizeof(float)：	这个是步长（stride），即一个属性的总长度。单位是 bytes。

		(void*)0：	这个值是 offset，不过需要强制转换成 void* 类型。offset 指的是该属性在顶点数据段中的 offset。本例中，
					一个顶点就一个属性，因此 offset = 0。当一个顶点有多个属性时，那么在设置第二个属性时，该参数就是第二个属性开始的位置（同时也是第一个属性的长度）。
					单位也是 bytes。*/

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout)
{
	Bind();
	vbo.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0; i != elements.size(); ++i)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(0));
		GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
