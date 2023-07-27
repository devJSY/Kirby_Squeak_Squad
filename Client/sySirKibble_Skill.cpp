#include "sySirKibble_Skill.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syCollider.h"

namespace sy
{
	SirKibble_Skill::SirKibble_Skill(GameObject* owner)
		: Effects(owner)
	{
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(10.f, 10.f));

		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemies_Right.bmp");

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(Enemies_Right, L"SirKibble_Skill", Vector2(179.f, 2640.f), Vector2(23.f, 16.f), Vector2(23.f, 0.f), 0.05f, 4);
		animator->PlayAnimation(L"SirKibble_Skill", true);
	}

	SirKibble_Skill::~SirKibble_Skill()
	{
	}

	void SirKibble_Skill::Initialize()
	{
		Effects::Initialize();
	}

	void SirKibble_Skill::Update()
	{
		Effects::Update();
	}

	void SirKibble_Skill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void SirKibble_Skill::OnCollisionEnter(Collider* other)
	{
	}

	void SirKibble_Skill::OnCollisionStay(Collider* other)
	{

	}

	void SirKibble_Skill::OnCollisionExit(Collider* other)
	{
	}
}