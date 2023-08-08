#include "syNinjaKirby_Fire.h"
#include "syPlayer.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "sySound.h"
#include "syTransform.h"

namespace sy
{
	NinjaKirby_Fire::NinjaKirby_Fire(Player* owner)
		: Effects(owner)
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		Animator* animator = AddComponent<Animator>();
		AddComponent<Collider>()->SetSize(Vector2(60.f, 20.f));

		Texture* Ninja_Fire = ResourceManager::Load<Texture>(L"Ninja_Fire_Tex", L"..\\Resources\\Effect\\Ninja_Fire.bmp");

		animator->CreateAnimation(Ninja_Fire, L"Ninja_Fire", Vector2(0.f, 0.f), Vector2(60.f, 100.f), Vector2(60.f, 0.f), 0.035f, 19, Vector2(0.f, -60.f));

		animator->PlayAnimation(L"Ninja_Fire", false);

		ResourceManager::Load<Sound>(L"NinjaFireSound", L"..\\Resources\\Sound\\Effect\\NinjaFire.wav")->Play(false);
	}

	NinjaKirby_Fire::~NinjaKirby_Fire()
	{
	}

	void NinjaKirby_Fire::Initialize()
	{
		Effects::Initialize();
	}

	void NinjaKirby_Fire::Update()
	{
		Effects::Update();
	}

	void NinjaKirby_Fire::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void NinjaKirby_Fire::OnCollisionEnter(Collider* other)
	{
	}

	void NinjaKirby_Fire::OnCollisionStay(Collider* other)
	{
	}
}