#include "syEnemy.h"
#include "syCollider.h"
#include "syAnimator.h"
#include "syRigidBody.h"
#include "syEnemyHPbarUI.h"
#include "syObject.h"

namespace sy
{
	Enemy::Enemy(eAbilityType type)
		: mAbilityType(type)
		, mMaxHp(100)
		, mCurHp(mMaxHp)
		, mHPbarUI(nullptr)
	{
		AddComponent<Animator>();
		AddComponent<Collider>()->SetSize(Vector2(15.f, 15.f));

		mHPbarUI = new EnemyHPbarUI(this);
		object::ActiveSceneAddGameObject(eLayerType::UI, mHPbarUI);
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