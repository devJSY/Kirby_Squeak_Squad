#include "syStageUI.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"

namespace sy
{
	StageUI::StageUI()
		: mAnimator(nullptr)
	{
	}

	StageUI::~StageUI()
	{
	}

	void StageUI::Initialize()
	{
		Texture* Tex = ResourceManager::Load<Texture>(L"LevelSelectImage_Tex", L"..\\Resources\\Map\\LevelSelect.bmp");
		mAnimator = AddComponent<Animator>();

		mAnimator->CreateAnimation(Tex, L"NormalStageClear", Vector2(683.f, 901.f), Vector2(31.f, 15.f), Vector2(34.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"NormalStage", Vector2(649.f, 919.f), Vector2(31.f, 15.f), Vector2(34.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"BossStageClear", Vector2(683.f, 937.f), Vector2(31.f, 23.f), Vector2(34.f, 0), 1.f, 1);
		mAnimator->CreateAnimation(Tex, L"BossStage", Vector2(649.f, 963.f), Vector2(31.f, 23.f), Vector2(34.f, 0), 1.f, 1);

		mAnimator->CreateAnimation(Tex, L"NormalStageClearFlash", Vector2(649.f, 901.f), Vector2(31.f, 15.f), Vector2(34.f, 0), 0.2f, 5);
		mAnimator->CreateAnimation(Tex, L"NormalStageFlash", Vector2(649.f, 919.f), Vector2(31.f, 15.f), Vector2(34.f, 0), 0.2f, 2);
		mAnimator->CreateAnimation(Tex, L"BossStageClearFlash", Vector2(649.f, 937.f), Vector2(31.f, 23.f), Vector2(34.f, 0), 0.2f, 5);
		mAnimator->CreateAnimation(Tex, L"BossStageFlash", Vector2(649.f, 963.f), Vector2(31.f, 23.f), Vector2(34.f, 0), 0.2f, 2);
	
		mAnimator->SetBmpRGB(L"NormalStageClear", 0, 128, 0);
		mAnimator->SetBmpRGB(L"NormalStage", 0, 128, 0);
		mAnimator->SetBmpRGB(L"BossStageClear", 0, 128, 0);
		mAnimator->SetBmpRGB(L"BossStage", 0, 128, 0);
		mAnimator->SetBmpRGB(L"NormalStageClearFlash", 0, 128, 0);
		mAnimator->SetBmpRGB(L"NormalStageFlash", 0, 128, 0);
		mAnimator->SetBmpRGB(L"BossStageClearFlash", 0, 128, 0);
		mAnimator->SetBmpRGB(L"BossStageFlash", 0, 128, 0);

		mAnimator->SetAffectedCamera(false);

		UI::Initialize();
	}

	void StageUI::Update()
	{
		UI::Update();
	}

	void StageUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}