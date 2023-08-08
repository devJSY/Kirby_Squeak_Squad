#include "syMixItem.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syInventory.h"
#include "sySceneManager.h"
#include "syTime.h"
#include "syApplication.h"
#include "sySound.h"
#include "sySoundManager.h"


namespace sy
{
	MixItem::MixItem()
		: mAnimator(nullptr)
		, mDuration(0.f)
	{
		Texture* Ability_UI_Tex = ResourceManager::Load<Texture>(L"Ability_UI_Tex", L"..\\Resources\\UI\\Ability_UI.bmp");
		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(Ability_UI_Tex, L"MixItemAnimation", Vector2(0.f, 43.f), Vector2(16.f, 27.f), Vector2(16.f, 0.f), 0.05f, 5);

		mAnimator->PlayAnimation(L"MixItemAnimation", true);
		mAnimator->SetAffectedCamera(false);

		Transform* transform = GetComponent<Transform>();
		transform->SetPosition(Vector2(128.f, 250.f));
		transform->SetScale(Vector2(3.f, 3.f));

		ResourceManager::Load<Sound>(L"CombineItem_Sound", L"..\\Resources\\Sound\\Effect\\CombineItem.wav");
		ResourceManager::Find<Sound>(L"CombineItem_Sound")->Play(false);
	}

	MixItem::~MixItem()
	{
	}

	void MixItem::Initialize()
	{
		GameObject::Initialize();
	}

	void MixItem::Update()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 0.5f)
		{
			std::srand(static_cast<unsigned int>(std::time(nullptr))); // 시간을 시드로 사용

			int randomNumber = std::rand() % (int)eAbilityType::Normal; // 0부터 eAbilityType까지의 랜덤 정수 생성
			//int randomNumber = std::rand() % 5; // 0부터 4까지의 랜덤 정수 생성

			SceneManager::GetInventory()->AddItem((eAbilityType)randomNumber);
			Destroy(this);
		}

		GameObject::Update();
	}

	void MixItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}