#include "syKingDedede.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syRigidbody.h"
#include "sySound.h"

namespace sy
{
	KingDedede::KingDedede(eAbilityType type)
		: Enemy(type)
		, mState(eKingDededeState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::RIGHT)
	{
	}

	KingDedede::~KingDedede()
	{
	}

	void KingDedede::Initialize()
	{
		// 텍스쳐 로드
		Texture* KingDedede_Right = ResourceManager::Load<Texture>(L"KingDedede_Right_Tex", L"..\\Resources\\Enemy\\Boss\\KingDedede\\KingDedede_Right.bmp");
		Texture* KingDedede_Left = ResourceManager::Load<Texture>(L"KingDedede_Left_Tex", L"..\\Resources\\Enemy\\Boss\\KingDedede\\KingDedede_Left.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidBody = AddComponent<Rigidbody>();
		mRigidBody->SetGround(true);
		GetComponent<Collider>()->SetSize(Vector2(60.f, 60.f));

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(0.f, 0.f);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Idle", Vector2::Zero, Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.05f, 4, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Idle", Vector2::Zero, Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.05f, 4, Animationoffset);


		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"KingDedede_Right_Idle", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"BossAttack", L"..\\Resources\\Sound\\Effect\\Boss\\BossAttack.wav");
		ResourceManager::Load<Sound>(L"BossDeath", L"..\\Resources\\Sound\\Effect\\Boss\\BossDeath.wav");
		ResourceManager::Load<Sound>(L"BossDrop", L"..\\Resources\\Sound\\Effect\\Boss\\BossDrop.wav");
		ResourceManager::Load<Sound>(L"BossRun", L"..\\Resources\\Sound\\Effect\\Boss\\BossRun.wav");
		ResourceManager::Load<Sound>(L"BossShout", L"..\\Resources\\Sound\\Effect\\Boss\\BossShout.wav");
		ResourceManager::Load<Sound>(L"BossWalk", L"..\\Resources\\Sound\\Effect\\Boss\\BossWalk.wav");

		//ResourceManager::Find<Sound>(L"BossAttack")->SetVolume(100.f);

		Enemy::Initialize();
	}

	void KingDedede::Update()
	{
		// 방향 설정
		mDir = mTransform->GetDirection();

		// 픽셀충돌 체크
		CheckPixelCollision();
		

		switch (mState)
		{
		case eKingDededeState::Idle:
			Idle();
			break;
		case eKingDededeState::Walk:
			Walk();
			break;
		case eKingDededeState::JumpReady:
			JumpReady();
			break;
		case eKingDededeState::Jump:
			Jump();
			break;
		case eKingDededeState::Drop:
			Drop();
			break;
		case eKingDededeState::AttackReady:
			AttackReady();
			break;
		case eKingDededeState::AttackRun:
			AttackRun();
			break;
		case eKingDededeState::Attack:
			Attack();
			break;
		case eKingDededeState::FlyReady:
			FlyReady();
			break;
		case eKingDededeState::FlyUp:
			FlyUp();
			break;
		case eKingDededeState::Fly:
			Fly();
			break;
		case eKingDededeState::FlyDrop:
			FlyDrop();
			break;
		case eKingDededeState::MonsterSummonReady:
			MonsterSummonReady();
			break;
		case eKingDededeState::MonsterSummonJump:
			MonsterSummonJump();
			break;
		case eKingDededeState::MonsterSummonDrop:
			MonsterSummonDrop();
			break;
		case eKingDededeState::MonsterSummon:
			MonsterSummon();
			break;
		case eKingDededeState::Damage:
			Damage();
			break;
		case eKingDededeState::DeathJump:
			DeathJump();
			break;
		case eKingDededeState::Death:
			Death();
			break;
		default:
			break;
		}

		Enemy::Update();
	}

	void KingDedede::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void KingDedede::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void KingDedede::CheckPixelCollision()
	{
	}

	void KingDedede::Idle()
	{
	}

	void KingDedede::Walk()
	{
	}

	void KingDedede::JumpReady()
	{
	}

	void KingDedede::Jump()
	{
	}

	void KingDedede::Drop()
	{
	}

	void KingDedede::AttackReady()
	{
	}

	void KingDedede::AttackRun()
	{
	}

	void KingDedede::Attack()
	{
	}

	void KingDedede::FlyReady()
	{
	}

	void KingDedede::FlyUp()
	{
	}

	void KingDedede::Fly()
	{
	}

	void KingDedede::FlyDrop()
	{
	}

	void KingDedede::MonsterSummonReady()
	{
	}

	void KingDedede::MonsterSummonJump()
	{
	}

	void KingDedede::MonsterSummonDrop()
	{
	}

	void KingDedede::MonsterSummon()
	{
	}

	void KingDedede::Damage()
	{
	}

	void KingDedede::DeathJump()
	{
	}

	void KingDedede::Death()
	{
	}
}