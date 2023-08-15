#include "syDaroach_Charge_Energe.h"
#include "syDaroach.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syTransform.h"

namespace sy
{
	Daroach_Charge_Energe::Daroach_Charge_Energe(Daroach* owner)
		: Effects(owner)
		, mDir(eDirection::RIGHT)
		, mTransform(nullptr)
	{
		mTransform = GetComponent<Transform>();
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();
		mTransform->SetDirection(mDir);
		Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		pos.y -= 38.f;
		if (mDir == eDirection::RIGHT)
			pos.x -= 3.f;
		else
			pos.x += 3.f;	
		mTransform->SetPosition(pos);

		Texture* Daroach_Charge_Energe_Tex = ResourceManager::Load<Texture>(L"Daroach_Charge_Energe_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_Charge_Energe.bmp");

		Animator* animator = AddComponent<Animator>();

		animator->CreateAnimation(Daroach_Charge_Energe_Tex, L"Daroach_Charge_Energe", Vector2::Zero, Vector2(50.f,50.f), Vector2(50.f,0.f), 0.05f, 4);
		animator->PlayAnimation(L"Daroach_Charge_Energe", true);
	}

	Daroach_Charge_Energe::~Daroach_Charge_Energe()
	{
	}

	void Daroach_Charge_Energe::Initialize()
	{
		Effects::Initialize();
	}

	void Daroach_Charge_Energe::Update()
	{
		Daroach* owner = dynamic_cast<Daroach*>(GetOwner());

		if (owner == nullptr)
		{
			Destroy(this);
		}

		mDir = owner->GetComponent<Transform>()->GetDirection();
		mTransform->SetDirection(mDir);
		Vector2 pos = owner->GetComponent<Transform>()->GetPosition();
		pos.y -= 38.f;
		if (mDir == eDirection::RIGHT)
			pos.x -= 3.f;
		else
			pos.x += 3.f;
		mTransform->SetPosition(pos);

		if (owner->GetDaroachState() != eDaroachState::WandCharge)
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void Daroach_Charge_Energe::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
}