#include "syKirby.h"
#include "syTransform.h"
#include "syInput.h"
#include "syTime.h"
#include "syCamera.h"
#include "syResourceManager.h"
#include "syTexture.h"

namespace sy
{
	Kirby::Kirby()
		: mAni(nullptr)
	{
	}

	Kirby::~Kirby()
	{
	}

	void Kirby::Initialize()
	{
		mAni = AddComponent<Animator>();
		assert(mAni);

		Texture* tex = ResourceManager::Load<Texture>(L"DefaultKirby_Right", L"..\\Resources\\Kirby\\DefaultKirby\\DefaultKirby_Right.bmp");
		mAni->CreateAnimation(L"RightMove", tex, Vector2(253.f, 8.f), Vector2(21.0f, 22.f), 10, Vector2::Zero, 0.1f);
		mAni->SetAniScale(L"RightMove", Vector2(4.f, 4.f));




		mAni->PlayAnimation(L"RightMove", true);

		GameObject::Initialize();
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
