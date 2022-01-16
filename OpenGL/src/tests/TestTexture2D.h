#pragma once
namespace test
{
	class TestTexture2D : public Test 
	{
	public:
		TestTexture2D();
		~TestTexture2D();

		void OnUpdate(float dealtTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		glm::vec3 m_Translation;
		glm::mat4 m_Proj;
		glm::mat4 m_View;
		float m_rChannel;
		float m_Increment;
		std::unique_ptr<VertexBuffer> pVbo;
		std::unique_ptr<VertexArray> pVao;
		std::unique_ptr<IndexBuffer> pIbo;
		std::unique_ptr<Shader> pShader;
		std::unique_ptr<Texture> pTexture;
		std::unique_ptr<Renderer> pRenderer;

	};

}