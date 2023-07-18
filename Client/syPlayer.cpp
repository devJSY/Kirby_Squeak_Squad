#include "syPlayer.h"

namespace sy
{
	Player::Player(eAbilityType type)
		: mAnimator(nullptr)
		, mDir(eDirection::RIGHT)
		, mAbilityType(type)
	{
		// 애니메이터 생성
		mAnimator = AddComponent<Animator>();
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