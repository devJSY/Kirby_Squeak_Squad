#include "syCutterKirby.h"

namespace sy
{
	CutterKirby::CutterKirby(Player* owner)
		: Kirby(owner)
		, mState(eCutterKirbyState::Idle)
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

	CutterKirby::~CutterKirby()
	{
	}

	void CutterKirby::Initialize()
	{
	}

	void CutterKirby::Update()
	{
	}

	void CutterKirby::Enter()
	{
	}

	void CutterKirby::Exit()
	{
	}

	void CutterKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void CutterKirby::OnCollisionEnter(Collider* other)
	{
	}

	void CutterKirby::OnCollisionStay(Collider* other)
	{
	}

	void CutterKirby::OnCollisionExit(Collider* other)
	{
	}

	void CutterKirby::CheckPixelCollision()
	{
	}

	void CutterKirby::Choice()
	{
	}

	void CutterKirby::Level_Enter()
	{
	}

	void CutterKirby::Level_Idle()
	{
	}

	void CutterKirby::Level_Run()
	{
	}

	void CutterKirby::Level_FlyUp()
	{
	}

	void CutterKirby::Level_Drop()
	{
	}

	void CutterKirby::Idle()
	{
	}

	void CutterKirby::Walk()
	{
	}

	void CutterKirby::Run()
	{
	}

	void CutterKirby::Jump()
	{
	}

	void CutterKirby::Turn()
	{
	}

	void CutterKirby::Drop()
	{
	}

	void CutterKirby::Down()
	{
	}

	void CutterKirby::Fly_Start()
	{
	}

	void CutterKirby::Fly_End()
	{
	}

	void CutterKirby::Fly_Down()
	{
	}

	void CutterKirby::Fly_Up()
	{
	}

	void CutterKirby::Skill()
	{
	}
}