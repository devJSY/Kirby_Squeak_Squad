#include "syPlayer.h"

namespace sy
{
	Player::Player()
		: mAnimator(nullptr)
		, mDir(eDirection::RIGHT)
	{
		// �ִϸ����� ����
		mAnimator = AddComponent<Animator>();
		assert(mAnimator);
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