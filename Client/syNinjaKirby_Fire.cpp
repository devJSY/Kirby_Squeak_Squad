#include "syNinjaKirby_Fire.h"
#include "syPlayer.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "sySound.h"
#include "syTransform.h"
#include "syTime.h"

namespace sy
{
	NinjaKirby_Fire::NinjaKirby_Fire(Player* owner, Vector2 pos)
		: Effects(owner)
		, mCollider(nullptr)
		, mTime(0.f)
	{
		GetComponent<Transform>()->SetPosition(pos);

		Animator* animator = AddComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(60.f, 20.f));

		Texture* Ninja_Fire = ResourceManager::Load<Texture>(L"Ninja_Fire_Tex", L"..\\Resources\\Effect\\Ninja_Fire.bmp");

		animator->CreateAnimation(Ninja_Fire, L"Ninja_Fire", Vector2(0.f, 0.f), Vector2(60.f, 100.f), Vector2(60.f, 0.f), 0.035f, 19, Vector2(0.f, -40.f));

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
		if (mTime >= 0.51f)
		{
			mCollider->SetSize(Vector2(0.f, 0.f));
		}
		else
		{
			mTime += (float)Time::DeltaTime();

			Vector2 size = { 60.f, 20.f };

			size.y += mTime * 150.f;
			float offset = mTime * 150.f / 2.f;

			if (size.y >= 80.f)
			{
				size.y = 80.f;
				offset = 30.f;
			}
			
			mCollider->SetSize(size);
			mCollider->SetOffset(Vector2(0.f, -offset));
		}

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