#include "VertexArray.h"
#include "Renderer.h"

/*�������������ǣ�
		0��			����Ǹ������ڶ����е� index���������ǵڼ������ԣ��� 0 ��ʼ���������У�ÿ������ֻ����ά������һ�����ԣ�
					���ֱ�ӷ��� VBO �� 0 ��λ�ã�ע����Ҳ�� vertex shader �п�ͷ��ʾ�� location = 0 �ĺ��壩��������㻹����������ֵ��
					�������� 2 �� floats ����ɫֵ����ô���ٴε��øú���������ɫ����ʱ������������� 1����Ȼ shader ҲҪ�޸ģ���

		2��			�����Եĵ�Ԫ�ظ�����ÿ�������� 2 �� floats����˾��� 2��

		GL_FLOAT :  ��������ÿ��Ԫ�ص����͡�

		GL_FALSE :  Ԫ���Ƿ���Ҫ���ݱ���׼�����з������ᱻӳ�䵽[-1, 1] ֮�䣬�޷��ŵĻ�����[0, 1] ֮�䣩��
					������Ϊ��OpenGL ֻ�����[-1, 1] ֮�������ֵ������������Χ��ֵ�� clip ����ͨ�������Ǳ�����Ϊ false��
					Ȼ��ͨ����Ҫ�û����н����մ��������ֵ��׼����[-1, 1] ֮�䡣����ע�⣬�Ⲣ��һ��Ҫͨ��ֱ���޸����������ſ��Ա�׼���ģ�
					���ǻ�����ͨ��һЩ�������̣�����ͨ��ͶӰӳ�䣨projective transformation���Ϳ��ԣ����磬�� RGB - D ���ƻ���ʱ������ˣ���
					��������ֻ��Ҫ��֤�����Ե�Ԫ��ֵ������[-1, 1] ��Χ���ɡ�

		2 * sizeof(float)��	����ǲ�����stride������һ�����Ե��ܳ��ȡ���λ�� bytes��

		(void*)0��	���ֵ�� offset��������Ҫǿ��ת���� void* ���͡�offset ָ���Ǹ������ڶ������ݶ��е� offset�������У�
					һ�������һ�����ԣ���� offset = 0����һ�������ж������ʱ����ô�����õڶ�������ʱ���ò������ǵڶ������Կ�ʼ��λ�ã�ͬʱҲ�ǵ�һ�����Եĳ��ȣ���
					��λҲ�� bytes��*/

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
