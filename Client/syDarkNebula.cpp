#include "syDarkNebula.h"

namespace sy
{
	DarkNebula::DarkNebula(eAbilityType type)
		: BossEnemy(type)
		, mState(eDarkNebulaState::Idle)
		, mMode(eDarkNebulaMode::Fire)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mStateChangeDelay(0.f)
		, FixedPos{}
		, mbDamaged(false)
	{
		FixedPos[0].x = 40.f;
		FixedPos[0].y = 40.f;

		FixedPos[1].x = 128.f;
		FixedPos[1].y = 40.f;

		FixedPos[2].x = 200.f;
		FixedPos[2].y = 40.f;

		FixedPos[3].x = 40.f;
		FixedPos[3].y = 110.f;

		FixedPos[4].x = 128.f;
		FixedPos[4].y = 96.f;

		FixedPos[5].x = 200.f;
		FixedPos[5].y = 110.f;
	}

	DarkNebula::~DarkNebula()
	{
	}

	void DarkNebula::Initialize()
	{
		BossEnemy::Initialize();
	}

	void DarkNebula::Update()
	{
		switch (mState)
		{
		case eDarkNebulaState::Idle:
			Idle();
			break;
		case eDarkNebulaState::Move:
			Move();
			break;
		case eDarkNebulaState::RotationalMove:
			RotationalMove();
			break;
		case eDarkNebulaState::ZigzagMove:
			ZigzagMove();
			break;
		case eDarkNebulaState::SkillReady:
			SkillReady();
			break;
		case eDarkNebulaState::FireSkill:
			FireSkill();
			break;
		case eDarkNebulaState::IceSkill:
			IceSkill();
			break;
		case eDarkNebulaState::SparkSkill:
			SparkSkill();
			break;
		case eDarkNebulaState::ModeChange:
			ModeChange();
			break;
		case eDarkNebulaState::Dead:
			Dead();
			break;
		default:
			break;
		}

		BossEnemy::Update();
	}

	void DarkNebula::Render(HDC hdc)
	{
		BossEnemy::Render(hdc);
	}

	void DarkNebula::OnCollisionEnter(Collider* other)
	{
	}

	void DarkNebula::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void DarkNebula::Idle()
	{
	}

	void DarkNebula::Move()
	{
	}

	void DarkNebula::RotationalMove()
	{
	}

	void DarkNebula::ZigzagMove()
	{
	}

	void DarkNebula::SkillReady()
	{
	}

	void DarkNebula::FireSkill()
	{
	}

	void DarkNebula::IceSkill()
	{
	}

	void DarkNebula::SparkSkill()
	{
	}

	void DarkNebula::ModeChange()
	{
	}

	void DarkNebula::Dead()
	{
	}
}