#include "sySirKibble.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "sySirKibble_Skill.h"
#include "syobject.h"
#include "syTransform.h"
#include "syInput.h"

namespace sy
{
	SirKibble::SirKibble()
		: Enemy(eAbilityType::Cutter)
	{
	}

	SirKibble::~SirKibble()
	{
	}

	void SirKibble::Initialize()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left_Tex", L"..\\Resources\\Enemies_Left.bmp");

		Animator* animator = GetAnimator();

		animator->CreateAnimation(Enemies_Right, L"SirKibble_Right_Idle", Vector2(3.f, 2582.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.12f, 5);
		animator->CreateAnimation(Enemies_Left, L"SirKibble_Left_Idle", Vector2(456.f, 2582.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.2f, 3);

		animator->CreateAnimation(Enemies_Right, L"SirKibble_Right_Attack", Vector2(2.f, 2632.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.2f, 6);
		animator->CreateAnimation(Enemies_Left, L"SirKibble_Left_Attack", Vector2(456.f, 2632.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.2f, 6);

		animator->CreateAnimation(Enemies_Right, L"SirKibble_Right_Jump", Vector2(3.f, 2582.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 1.f, 1);
		animator->CreateAnimation(Enemies_Left, L"SirKibble_Left_Jump", Vector2(456.f, 2582.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 1.f, 1);

		animator->CreateAnimation(Enemies_Right, L"SirKibble_Right_Death", Vector2(29.f, 2663.f), Vector2(24.f, 20.f), Vector2(24.f, 0.f), 1.f, 1);
		animator->CreateAnimation(Enemies_Left, L"SirKibble_Left_Death", Vector2(429.f, 2663.f), Vector2(24.f, 20.f), Vector2(-24.f, 0.f), 1.f, 1);

		animator->PlayAnimation(L"SirKibble_Right_Idle", true);

		Enemy::Initialize();
	}

	void SirKibble::Update()
	{
		Enemy::Update();

		// 특정 조건일때 스킬 생성
		if (Input::GetKeyDown(eKeyCode::T))
		{
			Transform* tr = GetComponent<Transform>();
			// 현재 HotHead 위치 기준 더해준 위치로 생성
			Vector2 pos = tr->GetPosition();
			pos += Vector2(10.f, 0.f);
			SirKibble_Skill* skill = object::Instantiate<SirKibble_Skill>(eLayerType::Effect);
			skill->GetComponent<Transform>()->SetPosition(pos);
			skill->SetOwner(this);
		}
	}

	void SirKibble::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
	void SirKibble::OnCollisionEnter(Collider* other)
	{
	}
	void SirKibble::OnCollisionStay(Collider* other)
	{
	}
	void SirKibble::OnCollisionExit(Collider* other)
	{
	}
}