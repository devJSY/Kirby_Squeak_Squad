#include "syDarkNebula_Eye.h"
#include "syTexture.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syDarkNebula.h"
#include "syAnimator.h"

namespace sy
{
	DarkNebula_Eye::DarkNebula_Eye(DarkNebula* owner)
		: mOwner(owner)
		, mTransform(nullptr)
		, mAnimator(nullptr)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mOwner->GetComponent<Transform>()->GetPosition());

		Texture* DarkNebula_Eye_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Eye_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Eye.bmp");
		Texture* DarkNebula_Eye_ModeChange_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Eye_ModeChange_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Eye_ModeChange.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(DarkNebula_Eye_Tex, L"DarkNebula_Eye", Vector2::Zero, Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.1f, 1);
		mAnimator->CreateAnimation(DarkNebula_Eye_Tex, L"DarkNebula_Eye_Flash", Vector2::Zero, Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.1f, 3);
		mAnimator->CreateAnimation(DarkNebula_Eye_ModeChange_Tex, L"DarkNebula_Eye_ModeChange", Vector2::Zero, Vector2(69.f, 86.f), Vector2(69.f, 0.f), 0.1f, 5);
		
		mAnimator->PlayAnimation(L"DarkNebula_Eye", true);
	}

	DarkNebula_Eye::~DarkNebula_Eye()
	{
	}

	void DarkNebula_Eye::Initialize()
	{
		GameObject::Initialize();
	}

	void DarkNebula_Eye::Update()
	{
		mTransform->SetPosition(mOwner->GetComponent<Transform>()->GetPosition());

		GameObject::Update();
	}

	void DarkNebula_Eye::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}