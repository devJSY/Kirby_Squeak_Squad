#include "syFireKirby.h"

namespace sy
{
	FireKirby::FireKirby(Player* owner)
		: Kirby(owner)
		, mState(eFireKirbyState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(enums::eDirection::RIGHT)
		, mbOnLeftStop(false)
		, mbOnRightStop(false)
		, mbTopStop(false)
		, mbOnSlope(false)
	{
	}

	FireKirby::~FireKirby()
	{
	}

	void FireKirby::Initialize()
	{
	}

	void FireKirby::Update()
	{
	}

	void FireKirby::Enter()
	{
	}

	void FireKirby::Exit()
	{
	}

	void FireKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void FireKirby::OnCollisionEnter(Collider* other)
	{
	}

	void FireKirby::OnCollisionStay(Collider* other)
	{
	}

	void FireKirby::OnCollisionExit(Collider* other)
	{
	}

	void FireKirby::CheckPixelCollision()
	{
	}

	void FireKirby::Choice()
	{
	}

	void FireKirby::Level_Enter()
	{
	}

	void FireKirby::Level_Idle()
	{
	}

	void FireKirby::Level_Run()
	{
	}

	void FireKirby::Level_FlyUp()
	{
	}

	void FireKirby::Level_Drop()
	{
	}

	void FireKirby::Idle()
	{
	}

	void FireKirby::Walk()
	{
	}

	void FireKirby::Run()
	{
	}

	void FireKirby::Jump()
	{
	}

	void FireKirby::Turn()
	{
	}

	void FireKirby::Drop()
	{
	}

	void FireKirby::Down()
	{
	}

	void FireKirby::Fly_Start()
	{
	}

	void FireKirby::Fly_End()
	{
	}

	void FireKirby::Fly_Down()
	{
	}

	void FireKirby::Fly_Up()
	{
	}

	void FireKirby::Skill()
	{
	}
}