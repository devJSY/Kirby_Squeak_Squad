#include "syPlayer.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syRigidbody.h"

namespace sy
{
	Player::Player(eAbilityType type, ePlayerMode mode)
		: mAbilityType(type)
		, mMode(ePlayerMode::LevelMode)
		, mHP(100)
		, mLife(3)
	{
		// 애니메이터 생성
		AddComponent<Animator>();
		AddComponent<Rigidbody>();
		AddComponent<Collider>()->SetSize(Vector2(15.f, 15.f));		
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		GameObject::Initialize();
	}

	void Player::Update()
	{
		//if (mHP > 100)
		//	mHP = 100;

		//if (mHP <= 0)
		//{
		//	mHP = 0;
		//	--mLife;
		//}

		//if (mLife < 0)
		//{
		//	// GameOver
		//}

		GameObject::Update();
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}