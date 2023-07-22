#include "syPlacardUI.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"

namespace sy
{
	PlacardUI::PlacardUI()
		: mAnimator(nullptr)
	{
	}

	PlacardUI::~PlacardUI()
	{
	}

	void PlacardUI::Initialize()
	{
		Texture* Tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(Tex, L"PlacardUI", Vector2(649.f, 1087.f), Vector2(31.f, 23.f), Vector2(31.f, 0.f), 1.f, 1);
		mAnimator->SetBmpRGB(L"PlacardUI", 0, 128, 0);

		mAnimator->SetAffectedCamera(false);

		UI::Initialize();
	}

	void PlacardUI::Update()
	{
		UI::Update();
	}

	void PlacardUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}