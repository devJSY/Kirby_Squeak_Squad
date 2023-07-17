#include "syEnemy.h"

namespace sy
{
	Enemy::Enemy(eAbilityType type)
		: mAnimator(nullptr)
		, mAbilityType(type)
		, mDir(eDirection::RIGHT)
	{
		// 애니메이터 생성
		mAnimator = AddComponent<Animator>();
		assert(mAnimator);
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