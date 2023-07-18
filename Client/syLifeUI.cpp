#include "syLifeUI.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syPlayer.h"
#include "sySpriteRenderer.h"

namespace sy
{
	LifeUI::LifeUI()
		: mOwner(nullptr)
		, mSpriteRenderer(nullptr)
		, mAnimator(nullptr)
	{
	}

	LifeUI::~LifeUI()
	{
	}

	void LifeUI::Initialize()
	{
		Texture* Life_Icon = ResourceManager::Load<Texture>(L"Life_Icon_Tex", L"..\\Resources\\UI\\Life_Icon.bmp");
		Life_Icon->SetType(eTextureType::Bmp);
		mSpriteRenderer = AddComponent<SpriteRenderer>();
		mSpriteRenderer->SetTexture(Life_Icon);
		mSpriteRenderer->SetAffectedCamera(false);

		mAnimator = AddComponent<Animator>();

		Texture* LifeCount_0 = ResourceManager::Load<Texture>(L"LifeCount_0_Tex", L"..\\Resources\\UI\\LifeCount\\LifeCount_0.bmp");
		Texture* LifeCount_1 = ResourceManager::Load<Texture>(L"LifeCount_1_Tex", L"..\\Resources\\UI\\LifeCount\\LifeCount_1.bmp");
		Texture* LifeCount_2 = ResourceManager::Load<Texture>(L"LifeCount_2_Tex", L"..\\Resources\\UI\\LifeCount\\LifeCount_2.bmp");
		Texture* LifeCount_3 = ResourceManager::Load<Texture>(L"LifeCount_3_Tex", L"..\\Resources\\UI\\LifeCount\\LifeCount_3.bmp");
		Texture* LifeCount_4 = ResourceManager::Load<Texture>(L"LifeCount_4_Tex", L"..\\Resources\\UI\\LifeCount\\LifeCount_4.bmp");
		Texture* LifeCount_5 = ResourceManager::Load<Texture>(L"LifeCount_5_Tex", L"..\\Resources\\UI\\LifeCount\\LifeCount_5.bmp");
		Texture* LifeCount_6 = ResourceManager::Load<Texture>(L"LifeCount_6_Tex", L"..\\Resources\\UI\\LifeCount\\LifeCount_6.bmp");
		Texture* LifeCount_7 = ResourceManager::Load<Texture>(L"LifeCount_7_Tex", L"..\\Resources\\UI\\LifeCount\\LifeCount_7.bmp");
		Texture* LifeCount_8 = ResourceManager::Load<Texture>(L"LifeCount_8_Tex", L"..\\Resources\\UI\\LifeCount\\LifeCount_8.bmp");
		Texture* LifeCount_9 = ResourceManager::Load<Texture>(L"LifeCount_9_Tex", L"..\\Resources\\UI\\LifeCount\\LifeCount_9.bmp");


		// AlphaBmp 안그려짐 Bmp로 강제 타입변환		
		LifeCount_0->SetType(eTextureType::Bmp);
		LifeCount_1->SetType(eTextureType::Bmp);
		LifeCount_2->SetType(eTextureType::Bmp);
		LifeCount_3->SetType(eTextureType::Bmp);
		LifeCount_4->SetType(eTextureType::Bmp);
		LifeCount_5->SetType(eTextureType::Bmp);
		LifeCount_6->SetType(eTextureType::Bmp);
		LifeCount_7->SetType(eTextureType::Bmp);
		LifeCount_8->SetType(eTextureType::Bmp);
		LifeCount_9->SetType(eTextureType::Bmp);


		mAnimator->CreateAnimation(LifeCount_0, L"LifeCount_0", Vector2::Zero, Vector2(23.f, 16.f), Vector2(23.f, 0.f), 1.f, 1, Vector2(23.f, 0.f));
		mAnimator->CreateAnimation(LifeCount_1, L"LifeCount_1", Vector2::Zero, Vector2(23.f, 16.f), Vector2(23.f, 0.f), 1.f, 1, Vector2(23.f, 0.f));
		mAnimator->CreateAnimation(LifeCount_2, L"LifeCount_2", Vector2::Zero, Vector2(23.f, 16.f), Vector2(23.f, 0.f), 1.f, 1, Vector2(23.f, 0.f));
		mAnimator->CreateAnimation(LifeCount_3, L"LifeCount_3", Vector2::Zero, Vector2(23.f, 16.f), Vector2(23.f, 0.f), 1.f, 1, Vector2(23.f, 0.f));
		mAnimator->CreateAnimation(LifeCount_4, L"LifeCount_4", Vector2::Zero, Vector2(23.f, 16.f), Vector2(23.f, 0.f), 1.f, 1, Vector2(23.f, 0.f));
		mAnimator->CreateAnimation(LifeCount_5, L"LifeCount_5", Vector2::Zero, Vector2(23.f, 16.f), Vector2(23.f, 0.f), 1.f, 1, Vector2(23.f, 0.f));
		mAnimator->CreateAnimation(LifeCount_6, L"LifeCount_6", Vector2::Zero, Vector2(23.f, 16.f), Vector2(23.f, 0.f), 1.f, 1, Vector2(23.f, 0.f));
		mAnimator->CreateAnimation(LifeCount_7, L"LifeCount_7", Vector2::Zero, Vector2(23.f, 16.f), Vector2(23.f, 0.f), 1.f, 1, Vector2(23.f, 0.f));
		mAnimator->CreateAnimation(LifeCount_8, L"LifeCount_8", Vector2::Zero, Vector2(23.f, 16.f), Vector2(23.f, 0.f), 1.f, 1, Vector2(23.f, 0.f));
		mAnimator->CreateAnimation(LifeCount_9, L"LifeCount_9", Vector2::Zero, Vector2(23.f, 16.f), Vector2(23.f, 0.f), 1.f, 1, Vector2(23.f, 0.f));

		mAnimator->PlayAnimation(L"LifeCount_3", false);
		mAnimator->SetAffectedCamera(false);


		UI::Initialize();
	}

	void LifeUI::Update()
	{
		UI::Update();
	}

	void LifeUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}