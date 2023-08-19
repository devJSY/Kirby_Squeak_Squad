#include "syDarkNebula_DeadStar.h"
#include "syDarkNebula.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "syTime.h"

namespace sy
{
	DarkNebula_DeadStar::DarkNebula_DeadStar(DarkNebula* owner, eDirection Dir)
		: Effects(owner)
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mDuration(0.f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		mTransform->SetDirection(Dir);

		mRigidbody = AddComponent<Rigidbody>();
		Vector2 vel = Vector2(0.f, -100.f);

		int randomNumber = (std::rand() % 50) + 50;
		if (Dir == eDirection::RIGHT)
			vel.x += randomNumber;
		else
			vel.x -= randomNumber;
		mRigidbody->SetVelocity(vel);
		mRigidbody->SetGround(false);

		Texture* DarkNebula_DeathStar_Tex = ResourceManager::Load<Texture>(L"DarkNebula_DeathStar_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_DeathStar.bmp");

		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(DarkNebula_DeathStar_Tex, L"DarkNebula_DeathStar", Vector2::Zero, Vector2(11.f, 11.f), Vector2(11.f, 0.f), 0.05f, 4);
		animator->PlayAnimation(L"DarkNebula_DeathStar", true);
	}

	DarkNebula_DeadStar::~DarkNebula_DeadStar()
	{
	}

	void DarkNebula_DeadStar::Initialize()
	{
		Effects::Initialize();
	}

	void DarkNebula_DeadStar::Update()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 5.f)
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void DarkNebula_DeadStar::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
}