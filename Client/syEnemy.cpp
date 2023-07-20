#include "syEnemy.h"
#include "syCollider.h"
namespace sy
{
	Enemy::Enemy(eAbilityType type)
		: mAnimator(nullptr)
		, mAbilityType(type)
	{
		// 局聪皋捞磐 积己
		mAnimator = AddComponent<Animator>();
		// 面倒眉 积己
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(15.f, 15.f));
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