#include "syKirby.h"
#include "syTransform.h"
#include "syInput.h"
#include "syTime.h"
#include "syCamera.h"

namespace sy
{
	Kirby::Kirby()
	{
	}

	Kirby::~Kirby()
	{
	}

	void Kirby::Initialize()
	{
	}

	void Kirby::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::W))
		{
			pos.y -= 200.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::A))
		{
			pos.x -= 200.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::S))
		{
			pos.y += 200.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::D))
		{
			pos.x += 200.0f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}

	void Kirby::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}
