#include "syTornadoKirby.h"

namespace sy
{
	TornadoKirby::TornadoKirby(Player* owner)
		: Kirby(owner)
		, mState(eTornadoKirbyState::Idle)
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

	TornadoKirby::~TornadoKirby()
	{

	}
	void TornadoKirby::Initialize()
	{
	}

	void TornadoKirby::Update()
	{
	}

	void TornadoKirby::Enter()
	{
	}

	void TornadoKirby::Exit()
	{
	}

	void TornadoKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void TornadoKirby::OnCollisionEnter(Collider* other)
	{
	}

	void TornadoKirby::OnCollisionStay(Collider* other)
	{
	}

	void TornadoKirby::OnCollisionExit(Collider* other)
	{
	}

	void TornadoKirby::CheckPixelCollision()
	{
	}

	void TornadoKirby::Choice()
	{
	}

	void TornadoKirby::Level_Enter()
	{
	}

	void TornadoKirby::Level_Idle()
	{
	}

	void TornadoKirby::Level_Run()
	{
	}

	void TornadoKirby::Level_FlyUp()
	{
	}

	void TornadoKirby::Level_Drop()
	{
	}

	void TornadoKirby::Idle()
	{
	}

	void TornadoKirby::Walk()
	{
	}

	void TornadoKirby::Run()
	{
	}

	void TornadoKirby::Jump()
	{
	}

	void TornadoKirby::Turn()
	{
	}

	void TornadoKirby::Drop()
	{
	}

	void TornadoKirby::Down()
	{
	}

	void TornadoKirby::Fly_Start()
	{
	}

	void TornadoKirby::Fly_End()
	{
	}

	void TornadoKirby::Fly_Down()
	{
	}

	void TornadoKirby::Fly_Up()
	{
	}

	void TornadoKirby::Skill()
	{
	}
}