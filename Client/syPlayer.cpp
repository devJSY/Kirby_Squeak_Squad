#include "syPlayer.h"
#include "syAnimator.h"
#include "syCollider.h"

namespace sy
{
	Player::Player(eAbilityType type)
		: mAbilityType(type)
	{
		// 애니메이터 생성
		AddComponent<Animator>();
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(15.f, 15.f));
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