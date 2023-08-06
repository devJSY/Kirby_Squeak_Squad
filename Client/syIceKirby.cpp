#include "syIceKirby.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "sySound.h"

namespace sy
{
	IceKirby::IceKirby()
		: Player(eAbilityType::Normal, ePlayerMode::LevelMode)
		, mState(eIceKirbyState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::RIGHT)
		, mbOnLeftStop(false)
		, mbOnRightStop(false)
		, mbTopStop(false)
		, mbOnSlope(false)
	{
	}

	IceKirby::~IceKirby()
	{
	}

	void IceKirby::Initialize()
	{
	}

	void IceKirby::Update()
	{
	}

	void IceKirby::Render(HDC hdc)
	{
	}

	void IceKirby::OnCollisionEnter(Collider* other)
	{
	}

	void IceKirby::OnCollisionStay(Collider* other)
	{
	}

	void IceKirby::OnCollisionExit(Collider* other)
	{
	}

	void IceKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void IceKirby::CheckPixelCollision()
	{
	}

	void IceKirby::Choice()
	{

	}

	void IceKirby::Level_Enter()
	{
	}

	void IceKirby::Level_Idle()
	{
	}

	void IceKirby::Level_Run()
	{
	}

	void IceKirby::Level_FlyUp()
	{
	}

	void IceKirby::Level_Drop()
	{
	}

	void IceKirby::Idle()
	{
	}

	void IceKirby::Walk()
	{
	}

	void IceKirby::Run()
	{
	}

	void IceKirby::Skill()
	{
	}

	void IceKirby::Down()
	{
	}

	void IceKirby::Jump()
	{
	}

	void IceKirby::Turn()
	{
	}

	void IceKirby::Drop()
	{
	}

	void IceKirby::Fly_Start()
	{
	}

	void IceKirby::Fly_End()
	{
	}

	void IceKirby::Fly_Down()
	{
	}

	void IceKirby::Fly_Up()
	{
	}
}