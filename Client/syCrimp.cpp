#include "syCrimp.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syInput.h"
#include "syCrimp_Skill.h"
#include "syTransform.h"
#include "syObject.h"

namespace sy
{
	Crimp::Crimp()
		: Enemy(eAbilityType::Normal)
	{
	}

	Crimp::~Crimp()
	{
	}

	void Crimp::Initialize()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemy\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left_Tex", L"..\\Resources\\Enemy\\Enemies_Left.bmp");

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(Enemies_Right, L"Flower_Right_Move", Vector2(0.f, 2916.f), Vector2(25.f, 24.f), Vector2(25.f, 0.f), 0.15f, 6);
		animator->CreateAnimation(Enemies_Right, L"Flower_Right_Death", Vector2(36.f, 3021.f), Vector2(20.f, 32.f), Vector2(20.f, 0.f), 1.f, 1);
		animator->CreateAnimation(Enemies_Right, L"Flower_Right_Attack", Vector2(0.f, 2941.f), Vector2(30.f, 26.f), Vector2(30.f, 0.f), 0.2f, 3);

		animator->PlayAnimation(L"Flower_Right_Move", true);

		Enemy::Initialize();
	}

	void Crimp::Update()
	{
		Enemy::Update();

		// Ư�� �����϶� ��ų ����
		if (Input::GetKeyDown(eKeyCode::T))
		{
			Transform* tr = GetComponent<Transform>();
			// ���� HotHead ��ġ ���� ������ ��ġ�� ����
			Vector2 pos = tr->GetPosition();
			pos += Vector2(10.f, 0.f);

			CrimpSkill* Skill = new CrimpSkill(this);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::Effect, Skill);
			Skill->GetComponent<Transform>()->SetPosition(pos);
		}
	}

	void Crimp::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
	void Crimp::OnCollisionEnter(Collider* other)
	{
	}
	void Crimp::OnCollisionStay(Collider* other)
	{
	}
	void Crimp::OnCollisionExit(Collider* other)
	{
	}
	void Crimp::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}
	void Crimp::CheckPixelCollision()
	{
	}
}