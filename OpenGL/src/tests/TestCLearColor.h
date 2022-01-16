#pragma once

namespace test
{
	class TestClearColor : public Test 
	{
	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float dealtTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_ClearColor[4];
	};

}