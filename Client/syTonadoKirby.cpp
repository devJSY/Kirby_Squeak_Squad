#include "syTonadoKirby.h"

namespace sy
{
	TonadoKirby::TonadoKirby(Player* owner)
		: Kirby(owner)
		, mState(eTonadoKirbyState::Idle)
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

	TonadoKirby::~TonadoKirby()
	{

	}
	void TonadoKirby::Initialize()
	{
	}

	void TonadoKirby::Update()
	{
	}

	void TonadoKirby::Enter()
	{
	}

	void TonadoKirby::Exit()
	{
	}

	void TonadoKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void TonadoKirby::OnCollisionEnter(Collider* other)
	{
	}

	void TonadoKirby::OnCollisionStay(Collider* other)
	{
	}

	void TonadoKirby::OnCollisionExit(Collider* other)
	{
	}

	void TonadoKirby::CheckPixelCollision()
	{
	}

	void TonadoKirby::Choice()
	{
	}

	void TonadoKirby::Level_Enter()
	{
	}

	void TonadoKirby::Level_Idle()
	{
	}

	void TonadoKirby::Level_Run()
	{
	}

	void TonadoKirby::Level_FlyUp()
	{
	}

	void TonadoKirby::Level_Drop()
	{
	}

	void TonadoKirby::Idle()
	{
	}

	void TonadoKirby::Walk()
	{
	}

	void TonadoKirby::Run()
	{
	}

	void TonadoKirby::Jump()
	{
	}

	void TonadoKirby::Turn()
	{
	}

	void TonadoKirby::Drop()
	{
	}

	void TonadoKirby::Down()
	{
	}

	void TonadoKirby::Fly_Start()
	{
	}

	void TonadoKirby::Fly_End()
	{
	}

	void TonadoKirby::Fly_Down()
	{
	}

	void TonadoKirby::Fly_Up()
	{
	}

	void TonadoKirby::Skill()
	{
	}
}