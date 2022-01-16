#include "GLPch.h"

namespace test
{

	TestMenu::TestMenu(Test*& m_CurrentTestPointer) : m_CurrentTest(m_CurrentTestPointer)
	{
	}

	TestMenu::~TestMenu()
	{
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second();
			}
		}
	}
}
