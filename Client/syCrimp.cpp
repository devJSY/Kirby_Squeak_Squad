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
		, mState(eCrimpState::Move)
		, mAnimator(nullptr)
		, mTransform(nullptr)
	{
	}

	Crimp::~Crimp()
	{
	}

	void Crimp::Initialize()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemy\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left_Tex", L"..\\Resources\\Enemy\\Enemies_Left.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mAnimator->CreateAnimation(Enemies_Right, L"Crimp_Right_Move", Vector2(0.f, 2916.f), Vector2(25.f, 24.f), Vector2(25.f, 0.f), 0.15f, 6);
		mAnimator->CreateAnimation(Enemies_Right, L"Crimp_Right_Damage", Vector2(36.f, 3021.f), Vector2(20.f, 32.f), Vector2(20.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(Enemies_Right, L"Crimp_Right_Attack", Vector2(0.f, 2941.f), Vector2(30.f, 26.f), Vector2(30.f, 0.f), 0.2f, 3);

		mAnimator->PlayAnimation(L"Crimp_Right_Move", true);

		Enemy::Initialize();
	}

	void Crimp::Update()
	{
		Enemy::Update();

		switch (mState)
		{
		case eCrimpState::Move:
			Move();
			break;
		case eCrimpState::Attack:
			Attack();
			break;
		case eCrimpState::Damage:
			Damage();
			break;
		default:
			break;
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
		// 이미 데미지 상태면 처리하지않음
		if (mState == eCrimpState::Damage)
			return;

		Damaged(DamageAmount);
		mState = eCrimpState::Damage;

		mAnimator->PlayAnimation(L"Crimp_Right_Damage", false);
		mTransform->SetDirection(eDirection::RIGHT);
	}

	void Crimp::Move()
	{
	}

	void Crimp::Attack()
	{
		// 특정 조건일때 스킬 생성
		if (Input::GetKeyDown(eKeyCode::T))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos += Vector2(10.f, 0.f);

			CrimpSkill* Skill = new CrimpSkill(this);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::Effect, Skill);
			Skill->GetComponent<Transform>()->SetPosition(pos);
		}
	}

	void Crimp::Damage()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (GetHP() <= 0.f)
				Destroy(this);

			mAnimator->PlayAnimation(L"Crimp_Right_Move", true);	

			mState = eCrimpState::Move;
		}
	}
}