#include "syPlayer.h"
#include "syAnimator.h"
#include "syCollider.h"

namespace sy
{
	Player::Player(eAbilityType type, ePlayerMode mode)
		: mAbilityType(type)
		, mMode(ePlayerMode::LevelMode)
	{
		// 애니메이터 생성
		AddComponent<Animator>();
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(20.f, 20.f));
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