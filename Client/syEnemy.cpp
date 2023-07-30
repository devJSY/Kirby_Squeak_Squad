#include "syEnemy.h"
#include "syCollider.h"
#include "syAnimator.h"
#include "syRigidBody.h"

namespace sy
{
	Enemy::Enemy(eAbilityType type)
		: mAbilityType(type)
	{
		AddComponent<Animator>();
		AddComponent<Rigidbody>();
		AddComponent<Collider>()->SetSize(Vector2(15.f, 15.f));
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