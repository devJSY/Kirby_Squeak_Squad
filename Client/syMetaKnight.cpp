#include "syMetaKnight.h"

namespace sy
{
	MetaKnight::MetaKnight(eAbilityType type)
		: BossEnemy(type)
	{
	}

	MetaKnight::~MetaKnight()
	{
	}

	void MetaKnight::Initialize()
	{
		BossEnemy::Initialize();
	}

	void MetaKnight::Update()
	{
		BossEnemy::Update();
	}

	void MetaKnight::Render(HDC hdc)
	{
		BossEnemy::Render(hdc);
	}

	void MetaKnight::OnCollisionEnter(Collider* other)
	{
	}

	void MetaKnight::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void MetaKnight::CheckPixelCollision()
	{
	}

	void MetaKnight::AddStarEffect(eDirection dir)
	{
	}

	void MetaKnight::Idle()
	{
	}

	void MetaKnight::Walk()
	{
	}

	void MetaKnight::Dash()
	{
	}

	void MetaKnight::DashAttack()
	{
	}

	void MetaKnight::Attack1()
	{
	}

	void MetaKnight::Attack2()
	{
	}

	void MetaKnight::Jump()
	{
	}

	void MetaKnight::Turn()
	{
	}

	void MetaKnight::Drop()
	{
	}

	void MetaKnight::SpinAttack()
	{
	}

	void MetaKnight::SparkAttack()
	{
	}

	void MetaKnight::TornadoAttack()
	{
	}

	void MetaKnight::Dead()
	{
	}
}