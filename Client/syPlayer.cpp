#include "syPlayer.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syRigidbody.h"
#include "syDefaultKirby.h"

namespace sy
{
	Player::Player(eAbilityType type, ePlayerMode mode)
		: mAbilityType(type)
		, mMode(ePlayerMode::LevelMode)
		, mbLevelEnter(false)
		, mHP(100)
		, mLife(3)
		, mHitEnemy(nullptr)
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
		GameObject::Update();
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}