#include "syDarkNebula_Border.h"
#include "syTexture.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syDarkNebula.h"
#include "syAnimator.h"

namespace sy
{
	DarkNebula_Border::DarkNebula_Border(DarkNebula* owner)
		: mOwner(owner)
		, mTransform(nullptr)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mOwner->GetComponent<Transform>()->GetPosition());

		Texture* DarkNebula_Border_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Border_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Border.bmp");

		Animator* animator = AddComponent<Animator>();
		animator->CreateAnimation(DarkNebula_Border_Tex, L"DarkNebula_Border", Vector2::Zero, Vector2(80.f, 80.f), Vector2(80.f, 0.f), 0.1f, 8, Vector2(0.f, -7.f));
		animator->PlayAnimation(L"DarkNebula_Border", true);
	}

	DarkNebula_Border::~DarkNebula_Border()
	{
	}

	void DarkNebula_Border::Initialize()
	{
		GameObject::Initialize();
	}

	void DarkNebula_Border::Update()
	{
		mTransform->SetPosition(mOwner->GetComponent<Transform>()->GetPosition());

		GameObject::Update();
	}

	void DarkNebula_Border::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}