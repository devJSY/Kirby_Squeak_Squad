#include "syStarUI.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"

namespace sy
{
	StarUI::StarUI()
		: mAnimator(nullptr)
	{
	}

	StarUI::~StarUI()
	{
	}

	void StarUI::Initialize()
	{
		// UI »ý¼º 
		Texture* Tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(Tex, L"StarUI", Vector2(649.f, 875.f), Vector2(31.f, 23.f), Vector2(34.f, 0.f), 0.1f, 3);
		mAnimator->SetBmpRGB(L"StarUI", 0, 128, 0);

		mAnimator->SetAffectedCamera(false);
		//mAnimator->PlayAnimation(L"StarUI");

		UI::Initialize();
	}

	void StarUI::Update()
	{
		UI::Update();
	}

	void StarUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}