#include "syIce.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"

namespace sy
{
	Ice::Ice()
		: Enemy(eAbilityType::Ice)
	{
		Texture* Monster_Ice = ResourceManager::Load<Texture>(L"Monster_Ice_Tex", L"..\\Resources\\Enemy\\Monster_Ice.bmp");

		Animator* animator = GetAnimator();

		animator->CreateAnimation(Monster_Ice, L"BigIce", Vector2(0.f, 0.f), Vector2(29.f, 29.f), Vector2(29.f, 0.f), 1.f, 1);
		animator->CreateAnimation(Monster_Ice, L"SmallIce", Vector2(30.f, 0.f), Vector2(21.f, 29.f), Vector2(21.f, 0.f), 1.f, 1);

		animator->PlayAnimation(L"SmallIce");
	}

	Ice::~Ice()
	{
	}

	void Ice::Initialize()
	{
		Enemy::Initialize();
	}

	void Ice::Update()
	{
		Enemy::Update();
	}

	void Ice::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
}