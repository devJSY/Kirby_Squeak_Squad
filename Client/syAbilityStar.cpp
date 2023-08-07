#include "syAbilityStar.h"
#include "syTransform.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syCollider.h"
#include "syTime.h"
#include "syAnimator.h"
#include "syPlayer.h"

namespace sy
{
	AbilityStar::AbilityStar(class Player* owner, math::Vector2 Dir)
		: mOwner(owner)
		, mState(eAbilityStarState::Move)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mCollider(nullptr)
		, mDuration(0.f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mOwner->GetComponent<Transform>()->GetPosition());

		if(Dir.x > 0.f)
			mTransform->SetDirection(eDirection::RIGHT);
		else
			mTransform->SetDirection(eDirection::LEFT);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(20.f, 20.f));

		Texture* Portal_StarTex = ResourceManager::Load<Texture>(L"Portal_Star", L"..\\Resources\\UI\\Portal_Star.bmp");
		Texture* Monster_Death_Tex = ResourceManager::Load<Texture>(L"Monster_Death_Tex", L"..\\Resources\\Effect\\Monster_Death.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(Portal_StarTex, L"Portal_Star", Vector2::Zero, Vector2(50.f, 30.f), Vector2(50.f, 0.f), 0.07f, 12);
		mAnimator->CreateAnimation(Monster_Death_Tex, L"AbilityStar_Death", Vector2(0.f, 0.f), Vector2(102.f, 102.f), Vector2(102.f, 0.f), 0.05f, 14);
				
		mAnimator->PlayAnimation(L"Portal_Star", true);
	}

	AbilityStar::~AbilityStar()
	{
	}

	void AbilityStar::Initialize()
	{
		GameObject::Initialize();
	}

	void AbilityStar::Update()
	{
		mDuration += Time::DeltaTime();

		switch (mState)
		{
		case eAbilityStarState::Move:
			Move();
			break;
		case eAbilityStarState::Dead:
			Dead();
			break;
		default:
			break;
		}

		GameObject::Update();
	}

	void AbilityStar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void AbilityStar::CheckPixelCollision()
	{
	}

	void AbilityStar::Move()
	{
		if (mDuration > 5.f)
		{
			mState = eAbilityStarState::Dead;
			mAnimator->PlayAnimation(L"AbilityStar_Death", false);
		}

		Vector2 pos = mTransform->GetPosition();
		if (mTransform->GetDirection() == eDirection::RIGHT)
			pos.x += 50.f * Time::DeltaTime();
		else
			pos.x -= 50.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void AbilityStar::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}
}