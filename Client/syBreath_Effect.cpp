#include "syBreath_Effect.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syTime.h"

namespace sy
{
	Breath_Effect::Breath_Effect(GameObject* owner)
		: Effects(owner)
		, mDir(eDirection::RIGHT)
	{
		Texture* Breath_Effect_Left_tex = ResourceManager::Load<Texture>(L"Breath_Effect_Left", L"..\\Resources\\Effect\\BreathEffect_Left.bmp");
		Texture* Breath_Effect_Right_tex = ResourceManager::Load<Texture>(L"Breath_Effect_Right", L"..\\Resources\\Effect\\BreathEffect_Right.bmp");

		Transform* tr = GetComponent<Transform>();
		Vector2 vec = owner->GetComponent<Transform>()->GetPosition();
		tr->SetPosition(vec);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(25.f, 25.f));
		

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(Breath_Effect_Left_tex, L"Breath_Effect_Left", Vector2(600.f, 0.f), Vector2(100.f, 25.f), Vector2(-100.f, 0.f), 0.1f, 6, Vector2(-50.f, 0.f));
		animator->CreateAnimation(Breath_Effect_Right_tex, L"Breath_Effect_Right", Vector2(0.f, 0.f), Vector2(100.f, 25.f), Vector2(100.f, 0.f), 0.1f, 6, Vector2(50.f, 0.f));

		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();

		// 방향 설정
		if (mDir == eDirection::RIGHT)
			animator->PlayAnimation(L"Breath_Effect_Right", true);
		else
			animator->PlayAnimation(L"Breath_Effect_Left", true);

	}

	Breath_Effect::~Breath_Effect()
	{
	}

	void Breath_Effect::Initialize()
	{
		Effects::Initialize();
	}

	void Breath_Effect::Update()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = GetComponent<Transform>()->GetPosition();		

		if (mDir == eDirection::RIGHT)
			pos.x += 80.f * Time::DeltaTime();
		else
			pos.x -= 80.f * Time::DeltaTime();

		tr->SetPosition(pos);

		Effects::Update();
	}

	void Breath_Effect::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Breath_Effect::OnCollisionEnter(Collider* other)
	{
	}

	void Breath_Effect::OnCollisionStay(Collider* other)
	{
	}

	void Breath_Effect::OnCollisionExit(Collider* other)
	{
	}
}