#include "syPlayer.h"
#include "syTransform.h"
#include "syInput.h"
#include "syTime.h"
#include "syApplication.h"

namespace sy
{
	Player::Player()
	{
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
	}

	void Player::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		POINT Resolution = Application::GetResolution();

		if (Input::GetKeyPressed(eKeyCode::UP) && pos.y >= 0)
		{
			pos.y -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && pos.x >= 0)
		{
			pos.x -= 300.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::DOWN) && pos.y <= (Resolution.y / 2))
		{
			pos.y += 300.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && pos.x <= Resolution.x / 2)
		{
			pos.x += 300.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}
