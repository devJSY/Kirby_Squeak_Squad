#include "syHPbarUI.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syPlayer.h"

namespace sy
{
	HPbarUI::HPbarUI()
	{
	}

	HPbarUI::~HPbarUI()
	{
	}

	void HPbarUI::Initialize()
	{
		mAnimator = AddComponent<Animator>();

		Texture* HP_Red = ResourceManager::Load<Texture>(L"HP_Red", L"..\\Resources\\UI\\HpBar\\HP_Red.bmp");
		Texture* HpBar_0 = ResourceManager::Load<Texture>(L"HpBar_0", L"..\\Resources\\UI\\HpBar\\HpBar_0.bmp");
		Texture* HpBar_10 = ResourceManager::Load<Texture>(L"HpBar_10", L"..\\Resources\\UI\\HpBar\\HpBar_10.bmp");
		Texture* HpBar_20 = ResourceManager::Load<Texture>(L"HpBar_20", L"..\\Resources\\UI\\HpBar\\HpBar_20.bmp");
		Texture* HpBar_30 = ResourceManager::Load<Texture>(L"HpBar_30", L"..\\Resources\\UI\\HpBar\\HpBar_30.bmp");
		Texture* HpBar_40 = ResourceManager::Load<Texture>(L"HpBar_40", L"..\\Resources\\UI\\HpBar\\HpBar_40.bmp");
		Texture* HpBar_50 = ResourceManager::Load<Texture>(L"HpBar_50", L"..\\Resources\\UI\\HpBar\\HpBar_50.bmp");
		Texture* HpBar_60 = ResourceManager::Load<Texture>(L"HpBar_60", L"..\\Resources\\UI\\HpBar\\HpBar_60.bmp");
		Texture* HpBar_70 = ResourceManager::Load<Texture>(L"HpBar_70", L"..\\Resources\\UI\\HpBar\\HpBar_70.bmp");
		Texture* HpBar_80 = ResourceManager::Load<Texture>(L"HpBar_80", L"..\\Resources\\UI\\HpBar\\HpBar_80.bmp");
		Texture* HpBar_90 = ResourceManager::Load<Texture>(L"HpBar_90", L"..\\Resources\\UI\\HpBar\\HpBar_90.bmp");
		Texture* HpBar_100 = ResourceManager::Load<Texture>(L"HpBar_100", L"..\\Resources\\UI\\HpBar\\HpBar_100.bmp");
		Texture* HpBar_110 = ResourceManager::Load<Texture>(L"HpBar_110", L"..\\Resources\\UI\\HpBar\\HpBar_110.bmp");
		Texture* HpBar_120 = ResourceManager::Load<Texture>(L"HpBar_120", L"..\\Resources\\UI\\HpBar\\HpBar_120.bmp");

		// AlphaBmp 안그려짐 Bmp로 강제 타입변환
		HP_Red->SetType(eTextureType::Bmp);
		HpBar_0->SetType(eTextureType::Bmp);
		HpBar_10->SetType(eTextureType::Bmp);
		HpBar_20->SetType(eTextureType::Bmp);
		HpBar_30->SetType(eTextureType::Bmp);
		HpBar_40->SetType(eTextureType::Bmp);
		HpBar_50->SetType(eTextureType::Bmp);
		HpBar_60->SetType(eTextureType::Bmp);
		HpBar_70->SetType(eTextureType::Bmp);
		HpBar_80->SetType(eTextureType::Bmp);
		HpBar_90->SetType(eTextureType::Bmp);
		HpBar_100->SetType(eTextureType::Bmp);
		HpBar_110->SetType(eTextureType::Bmp);
		HpBar_120->SetType(eTextureType::Bmp);


		mAnimator->CreateAnimation(HP_Red, L"HP_Red", Vector2::Zero, Vector2(104.f, 8.f), Vector2(104.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_0, L"HpBar_0", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_10, L"HpBar_10", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_20, L"HpBar_20", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_30, L"HpBar_30", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_40, L"HpBar_40", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_50, L"HpBar_50", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_60, L"HpBar_60", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_70, L"HpBar_70", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_80, L"HpBar_80", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_90, L"HpBar_90", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_100, L"HpBar_100", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_110, L"HpBar_110", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(HpBar_120, L"HpBar_120", Vector2::Zero, Vector2(84, 12.f), Vector2(84, 0.f), 1.f, 1);

		mAnimator->PlayAnimation(L"HpBar_10", false);
		mAnimator->SetAffectedCamera(false);

		UI::Initialize();
	}

	void HPbarUI::Update()
	{
		UI::Update();
	}

	void HPbarUI::Render(HDC hdc)
	{
		UI::Render(hdc);
	}
}