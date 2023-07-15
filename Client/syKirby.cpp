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
		// 애니메이터 생성
		mAni = AddComponent<Animator>();
		assert(mAni);

		// 텍스쳐 로드
		Texture* DefaultKirby_Right_Tex = ResourceManager::Load<Texture>(L"DefaultKirby_Right", L"..\\Resources\\Kirby\\DefaultKirby\\DefaultKirby_Right.bmp");
		Texture* DefaultKirby_Left_Tex = ResourceManager::Load<Texture>(L"DefaultKirby_Left", L"..\\Resources\\Kirby\\DefaultKirby\\DefaultKirby_Left.bmp");
		
		// 애니메이션 생성
		mAni->CreateAnimation(L"Choice", DefaultKirby_Right_Tex, Vector2(309.f, 324.f), Vector2(22.f, 28.f), Vector2(22.f, 0.f), 0.04f, 9);
		mAni->CreateAnimation(L"Enter", DefaultKirby_Right_Tex, Vector2(738.f, 7.f), Vector2(19.f, 22.f), Vector2(19.f, 0.f), 0.6f, 1);


	











		mAni->PlayAnimation(L"Choice", true);

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
