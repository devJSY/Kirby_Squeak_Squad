#include "syUI.h"

namespace sy
{
	UI::UI()
		: mAnimator(nullptr)
	{
	}

	UI::~UI()
	{
	}

	void UI::Initialize()
	{
		GameObject::Initialize();
	}

	void UI::Update()
	{
		GameObject::Update();
	}

	void UI::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}