#include "syDotUI.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"

namespace sy
{
	DotUI::DotUI()
	{
	}

	DotUI::~DotUI()
	{
	}

	void DotUI::Initialize()
	{
		Texture* Tex = ResourceManager::Load<Texture>(L"Dot", L"..\\Resources\\UI\\Dot.bmp");
		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(Tex, L"Dot", Vector2::Zero, Vector2(6.f, 6.f), Vector2(6.f, 0.f), 1.f, 1);

		animator->SetAffectedCamera(false);

		UI::Initialize();
	}

	void DotUI::Update()
	{
		UI::Update();
	}

	void DotUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}