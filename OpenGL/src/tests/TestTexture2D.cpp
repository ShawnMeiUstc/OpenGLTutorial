#include "GLPch.h"
#include "TestTexture2D.h"
#include "glm/gtc/matrix_transform.hpp"

extern int width;
extern int height;

namespace test
{

	TestTexture2D::TestTexture2D() : m_Translation{0.0f, 0.0f, 0.0f}, m_rChannel(0.0f), m_Increment(0.05f)
	{
		float widthOver2 = width / 2, heightOver2 = height / 2;
		float sideLenOver2 = 150;
		float left = widthOver2 - sideLenOver2, right = widthOver2 + sideLenOver2,
			top = heightOver2 + sideLenOver2, bottum = heightOver2 - sideLenOver2;

		float position[] = {
		left, bottum, 0.0f, 0.0f,
		right, bottum, 1.0f, 0.0f,
		right, top, 1.0f, 1.0f,
		left,  top, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA));

		pVao = std::make_unique<VertexArray>();
		pVbo = std::make_unique<VertexBuffer>(position, sizeof(position));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		pVao->AddBuffer(*pVbo, layout);

		pIbo = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0]));

		m_Proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

		pShader = std::make_unique<Shader>("res/shaders/Basic.shader");
		pShader->Bind();
		pShader->setUniform1i("u_Texture", 0);

		pTexture = std::make_unique<Texture>("res/textures/rectangle.png");
		pTexture->Bind();
		pRenderer = std::make_unique<Renderer>();
	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float dealtTime)
	{
	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		glm::mat4 mvp = m_Proj * m_View * model;
		pShader->SetUniform4f("u_Color", m_rChannel, 0.5f, 0.2f, 1.0f);
		pShader->SetUniformMat4f("u_MVP", mvp);
		pRenderer->Draw(*pVao, *pIbo, *pShader);

		if (m_rChannel > 1.0f)
		{
			m_Increment = -0.05f;
		}
		else if (m_rChannel < 0.0f)
		{
			m_Increment = 0.05f;
		}
		m_rChannel += m_Increment;
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::Begin("2D Texture");
		ImGui::SliderFloat2("worldMat", &m_Translation.x, -500.0f, 500.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}

