#include "syPlacardUI.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"

namespace sy
{
	PlacardUI::PlacardUI()
	{
	}

	PlacardUI::~PlacardUI()
	{
	}

	void PlacardUI::Initialize()
	{
		// UI »ý¼º 
		Texture* Tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.bmp");
		Animator* animator = AddComponent<Animator>();

		animator->CreateAnimation(Tex, L"Placard", Vector2(649.f, 1087.f), Vector2(31.f, 23.f), Vector2(31.f, 0.f), 1.f, 1);
		animator->SetBmpRGB(L"Placard", 0, 128, 0);

		animator->SetAffectedCamera(false);
		animator->PlayAnimation(L"Placard");

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