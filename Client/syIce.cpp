#include "syIce.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syCollider.h"
namespace sy
{
	Ice::Ice()
		: Enemy(eAbilityType::Ice)
	{
		Texture* Monster_Ice = ResourceManager::Load<Texture>(L"Monster_Ice_Tex", L"..\\Resources\\Enemy\\Monster_Ice.bmp");

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(Monster_Ice, L"BigIce", Vector2(0.f, 0.f), Vector2(29.f, 29.f), Vector2(29.f, 5.f), 1.f, 1);
		animator->CreateAnimation(Monster_Ice, L"SmallIce", Vector2(30.f, 0.f), Vector2(21.f, 29.f), Vector2(21.f, 5.f), 1.f, 1, Vector2(-1.f, -5.f));

		animator->PlayAnimation(L"SmallIce");
		//GetComponent<Collider>()->SetSize(Vector2(15.f, 15.f)); // Small
		//GetComponent<Collider>()->SetSize(Vector2(25.f, 25.f)); // Big
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
	void Ice::OnCollisionEnter(Collider* other)
	{
	}
	void Ice::OnCollisionStay(Collider* other)
	{
	}
	void Ice::OnCollisionExit(Collider* other)
	{
	}
	void Ice::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}
	void Ice::CheckPixelCollision()
	{
	}
}