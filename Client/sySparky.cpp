#include "sySparky.h"

namespace sy
{
	Sparky::Sparky()
		: Enemy(eAbilityType::Spark)
	{
	}

	Sparky::~Sparky()
	{
	}

	void Sparky::Initialize()
	{
		Enemy::Initialize();
	}

	void Sparky::Update()
	{
		Enemy::Update();
	}

	void Sparky::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void Sparky::OnCollisionEnter(Collider* other)
	{
	}

	void Sparky::OnCollisionStay(Collider* other)
	{
	}

	void Sparky::OnCollisionExit(Collider* other)
	{

	}
	void Sparky::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void Sparky::TakeInhaled(math::Vector2 InhaleDir)
	{
	}

	void Sparky::Move()
	{
	}

	void Sparky::Jump()
	{
	}

	void Sparky::SkillReady()
	{
	}

	void Sparky::Skill()
	{
	}

	void Sparky::Damage()
	{
	}

	void Sparky::Dead()
	{
	}

	void Sparky::Inhaled()
	{
	}
}