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
		Texture* Portal_StarTex = ResourceManager::Load<Texture>(L"Portal_Star", L"..\\Resources\\UI\\Portal_Star.bmp");
		Texture* StageStarTex = ResourceManager::Load<Texture>(L"StageStar", L"..\\Resources\\UI\\StageStar.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(Portal_StarTex, L"Portal_Star", Vector2::Zero, Vector2(50.f, 30.f), Vector2(50.f, 0.f), 0.07f, 12);
		mAnimator->CreateAnimation(StageStarTex, L"StageStar", Vector2::Zero, Vector2(22.f, 20.f), Vector2(22.f, 0.f), 0.1f, 1);

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