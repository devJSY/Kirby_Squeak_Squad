#include "syCrimp.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syInput.h"
#include "syCrimp_Skill.h"
#include "syTransform.h"
#include "syObject.h"
#include "syPlayer.h"
#include "syCollider.h"
#include "syDefaultKirby.h"
#include "syTime.h"

namespace sy
{
	Crimp::Crimp()
		: Enemy(eAbilityType::Normal)
		, mState(eCrimpState::Move)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mAttackDelay(0.f)
	{
	}

	Crimp::~Crimp()
	{
	}

	void Crimp::Initialize()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemy\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left_Tex", L"..\\Resources\\Enemy\\Enemies_Left.bmp");

		Texture* Monster_Death_Tex = ResourceManager::Load<Texture>(L"Monster_Death_Tex", L"..\\Resources\\Effect\\Monster_Death.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();

		mAnimator->CreateAnimation(Enemies_Right, L"Crimp_Right_Move", Vector2(0.f, 2916.f), Vector2(25.f, 24.f), Vector2(25.f, 0.f), 0.15f, 6);
		mAnimator->CreateAnimation(Enemies_Right, L"Crimp_Right_Damage", Vector2(36.f, 3021.f), Vector2(20.f, 32.f), Vector2(20.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(Enemies_Right, L"Crimp_Right_Attack", Vector2(0.f, 2941.f), Vector2(30.f, 26.f), Vector2(30.f, 0.f), 0.1f, 3);

		mAnimator->CreateAnimation(Monster_Death_Tex, L"Crimp_Death", Vector2(0.f, 0.f), Vector2(102.f, 102.f), Vector2(102.f, 0.f), 0.05f, 14);

		mAnimator->PlayAnimation(L"Crimp_Right_Move", true);

		Enemy::Initialize();
	}

	void Crimp::Update()
	{
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
		case eCrimpState::Dead:
			Dead();
			break;
		case eCrimpState::Inhaled:
			Inhaled();
			break;
		default:
			break;
		}

		Enemy::Update();
	}

	void Crimp::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void Crimp::OnCollisionEnter(Collider* other)
	{
		if (mState == eCrimpState::Dead || mState == eCrimpState::Inhaled)
			return;

		// Inhale 상태에선 무시
		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(other->GetOwner());
		if (kirby != nullptr)
		{
			if (kirby->GetKirbyState() == eDefaultKirbyState::Inhale_1 || kirby->GetKirbyState() == eDefaultKirbyState::Inhale_2)
				return;
		}

		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 몬스터 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Crimp::OnCollisionStay(Collider* other)
	{
	}

	void Crimp::OnCollisionExit(Collider* other)
	{
	}

	void Crimp::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		Damaged(DamageAmount);

		// 이미 데미지 상태면 애니메이션, 피격 넉백 처리하지않음
		if (mState == eCrimpState::Damage || mState == eCrimpState::Dead)
			return;

		mState = eCrimpState::Damage;

		mAnimator->PlayAnimation(L"Crimp_Right_Damage", false);
		mTransform->SetDirection(eDirection::RIGHT);
	}

	void Crimp::TakeInhaled(math::Vector2 InhaleDir)
	{
		if (mState == eCrimpState::Dead)
			return;

		mState = eCrimpState::Inhaled;

		mAnimator->PlayAnimation(L"Crimp_Right_Damage", false);
		mTransform->SetDirection(eDirection::RIGHT);
	}

	void Crimp::Move()
	{
		if (GetCurHP() <= 0.f)
		{
			mAnimator->PlayAnimation(L"Crimp_Death", false);
			mState = eCrimpState::Dead;
		}

		mAttackDelay += Time::DeltaTime();

		// 특정 조건일때 스킬 생성
		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 distance = PlayerPos - mTransform->GetPosition();
		float Len = distance.Length();

		if (Len < 50.f && mAttackDelay > 1.f)
		{
			CrimpSkill* Skill = new CrimpSkill(this);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::Effect, Skill);
			mAnimator->PlayAnimation(L"Crimp_Right_Attack", false);
			mState = eCrimpState::Attack;
			mAttackDelay = 0.f;
		}
	}

	void Crimp::Attack()
	{
		static float time = 0.f;

		time += Time::DeltaTime();

		if (GetCurHP() <= 0.f)
		{
			mAnimator->PlayAnimation(L"Crimp_Death", false);
			mState = eCrimpState::Dead;
			time = 0.f;
		}

		if (mAnimator->IsActiveAnimationComplete() && time > 2.f)
		{
			mAnimator->PlayAnimation(L"Crimp_Right_Move", true);
			mState = eCrimpState::Move;
			time = 0.f;
		}
	}

	void Crimp::Damage()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (GetCurHP() <= 0.f)
			{
				mAnimator->PlayAnimation(L"Crimp_Death", false);
				mState = eCrimpState::Dead;
			}
			else
			{
				mAnimator->PlayAnimation(L"Crimp_Right_Move", true);
				mState = eCrimpState::Move;
			}
		}
	}
	void Crimp::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void Crimp::Inhaled()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"Crimp_Right_Move", true);
			mState = eCrimpState::Move;			
		}
	}
}