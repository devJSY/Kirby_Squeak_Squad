#include "syEnemy.h"

namespace sy
{
	Enemy::Enemy(eAbilityType type)
		: mAnimator(nullptr)
		, mDir(eDirection::RIGHT)
		, mAbilityType(type)
	{
		// 애니메이터 생성
		mAnimator = AddComponent<Animator>();
	}

	Enemy::~Enemy()
	{
	}

	void Enemy::Initialize()
	{
		GameObject::Initialize();
	}

	void Enemy::Update()
	{
		GameObject::Update();
	}

	void Enemy::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}