#include "syBossEnemy.h"


namespace sy
{
	BossEnemy::BossEnemy(eAbilityType type)
		: Enemy(type)
	{
	}

	BossEnemy::~BossEnemy()
	{
	}

	void BossEnemy::Initialize()
	{
		Enemy::Initialize();
	}

	void BossEnemy::Update()
	{
		Enemy::Update();
	}

	void BossEnemy::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
}