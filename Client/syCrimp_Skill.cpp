#include "syCrimp_Skill.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syCollider.h"

namespace sy
{
	CrimpSkill::CrimpSkill(GameObject* owner)
		: Effects(owner)
	{
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(10.f, 10.f));

		Texture* tex = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemy\\Enemies_Right.bmp");

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(tex, L"Flower_Skill", Vector2(109.f, 2959.f), Vector2(8.f, 8.f), Vector2(8.f, 0.f), 1.f, 1);
		animator->PlayAnimation(L"Flower_Skill", true);
	}

	CrimpSkill::~CrimpSkill()
	{
	}

	void CrimpSkill::Initialize()
	{
		Effects::Initialize();
	}

	void CrimpSkill::Update()
	{
		Effects::Update();
	}

	void CrimpSkill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
	void CrimpSkill::OnCollisionEnter(Collider* other)
	{
	}
	void CrimpSkill::OnCollisionStay(Collider* other)
	{
	}
	void CrimpSkill::OnCollisionExit(Collider* other)
	{
	}
}