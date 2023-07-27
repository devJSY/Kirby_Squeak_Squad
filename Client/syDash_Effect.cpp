#include "syDash_Effect.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syGameObject.h"
#include "syTransform.h"


namespace sy
{
	Dash_Effect::Dash_Effect(GameObject* owner)
		: Effects(owner)
		, mAnimator(nullptr)
	{
		Texture* Dash_Effect_Left_tex = ResourceManager::Load<Texture>(L"Dash_Effect_Left", L"..\\Resources\\Effect\\Dash_Effect_Left.bmp");
		Texture* Dash_Effect_Right_tex = ResourceManager::Load<Texture>(L"Dash_Effect_Right", L"..\\Resources\\Effect\\Dash_Effect_Right.bmp");

		mAnimator = GetComponent<Animator>();

		mAnimator->CreateAnimation(Dash_Effect_Left_tex, L"Dash_Effect_Left", Vector2(0.f, 0.f), Vector2(57.f, 28.f), Vector2(57.f, 0.f), 0.03f, 19);
		mAnimator->CreateAnimation(Dash_Effect_Right_tex, L"Dash_Effect_Right", Vector2(1083.f, 0.f), Vector2(57.f, 28.f), Vector2(-57.f, 0.f), 0.03f, 19);
		

		if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
		{
			mAnimator->PlayAnimation(L"Dash_Effect_Right", false);
		}
		else
		{
			mAnimator->PlayAnimation(L"Dash_Effect_Left", false);
		}			
	}

	Dash_Effect::~Dash_Effect()
	{
	}

	void Dash_Effect::Initialize()
	{
		GameObject::Initialize();
	}

	void Dash_Effect::Update()
	{
		GameObject* Owner = GetOwner();

		if (Owner->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 vec = Owner->GetComponent<Transform>()->GetPosition();
			vec.x -= 20.f;
			tr->SetPosition(vec);
		}
		else
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 vec = Owner->GetComponent<Transform>()->GetPosition();
			vec.x += 20.f;
			tr->SetPosition(vec);
		}
		
		// Run 상태가 아니면 삭제하도록 추가해야함
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		GameObject::Update();
	}

	void Dash_Effect::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}