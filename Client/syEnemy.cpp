#include "syEnemy.h"
#include "syAnimator.h"

namespace sy
{
	Enemy::Enemy(eAbilityType type)
		: mAbilityType(type)
	{
		AddComponent<Animator>();
	}

	Enemy::~Enemy()
	{
	}

	void Enemy::Initialize()
	{
	}

	void Enemy::Update()
	{
	}

	void Enemy::Render(HDC hdc)
	{
	}
}