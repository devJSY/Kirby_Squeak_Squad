#include "syMetaKnight.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syRigidbody.h"
#include "sySound.h"
#include "sySceneManager.h"
#include "syTime.h"
#include "syPlayer.h"
#include "syStar_Effect.h"

namespace sy
{
	MetaKnight::MetaKnight(eAbilityType type)
		: BossEnemy(type)
		, mState(eMetaKnightState::AppearReady)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mCollider(nullptr)
		, mDir(eDirection::LEFT)
		, mStateChangeDelay(-3.f)
		, mbDamaged(false)
	{
	}

	MetaKnight::~MetaKnight()
	{
	}

	void MetaKnight::Initialize()
	{
		// 체력 설정
		SetHP(1000);

		// 텍스쳐 로드
		Texture* MetaKnight_Right_Tex = ResourceManager::Load<Texture>(L"MetaKnight_Right_Tex", L"..\\Resources\\Enemy\\Boss\\MetaKnight\\MetaKnight_Right.bmp");
		Texture* MetaKnight_Left_Tex = ResourceManager::Load<Texture>(L"MetaKnight_Left_Tex", L"..\\Resources\\Enemy\\Boss\\MetaKnight\\MetaKnight_Left.bmp");

		Texture* MetaKnight_Appear_Tex = ResourceManager::Load<Texture>(L"MetaKnight_Appear_Tex", L"..\\Resources\\Enemy\\Boss\\MetaKnight\\MetaKnight_Appear.bmp");
		Texture* MetaKnight_Dead_Tex = ResourceManager::Load<Texture>(L"MetaKnight_Dead_Tex", L"..\\Resources\\Enemy\\Boss\\MetaKnight\\MetaKnight_Dead.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mTransform->SetScale(Vector2(0.35f, 0.35f));
		//mRigidBody = AddComponent<Rigidbody>();
		mCollider = GetComponent<Collider>();
		mCollider->SetSize(Vector2(15.f, 15.f));

		mTransform->SetPosition(Vector2(100.f,100.f));

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(0.f, 0.f);
		mAnimator->CreateAnimation(MetaKnight_Appear_Tex, L"MetaKnight_AppearReady", Vector2::Zero, Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 3, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Appear_Tex, L"MetaKnight_Appear", Vector2::Zero, Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 22, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Dead_Tex, L"MetaKnight_Dead_1", Vector2::Zero, Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 11, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Dead_Tex, L"MetaKnight_Dead_2", Vector2::Zero, Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 6, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Dead_Tex, L"MetaKnight_Dead_3", Vector2::Zero, Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 15, Animationoffset);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"MetaKnight_AppearReady", true);

		// Sound Load
		BossEnemy::Initialize();
	}

	void MetaKnight::Update()
	{
		switch (mState)
		{
		case eMetaKnightState::AppearReady:
			AppearReady();
			break;
		case eMetaKnightState::Appear:
			Appear();
			break;
		case eMetaKnightState::Idle:
			Idle();
			break;
		case eMetaKnightState::Walk:
			Walk();
			break;
		case eMetaKnightState::Dash:
			Dash();
			break;
		case eMetaKnightState::DashAttack:
			DashAttack();
			break;
		case eMetaKnightState::Slash1:
			Slash1();
			break;
		case eMetaKnightState::Slash2:
			Slash2();
			break;
		case eMetaKnightState::Jump:
			Jump();
			break;
		case eMetaKnightState::Turn:
			Turn();
			break;
		case eMetaKnightState::Drop:
			Drop();
			break;
		case eMetaKnightState::SpinAttack:
			SpinAttack();
			break;
		case eMetaKnightState::SparkAttack:
			SparkAttack();
			break;
		case eMetaKnightState::TornadoAttack:
			TornadoAttack();
			break;
		case eMetaKnightState::Dead:
			Dead();
			break;
		default:
			break;
		}

		BossEnemy::Update();
	}

	void MetaKnight::Render(HDC hdc)
	{
		BossEnemy::Render(hdc);
	}

	void MetaKnight::OnCollisionEnter(Collider* other)
	{
	}

	void MetaKnight::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void MetaKnight::CheckPixelCollision()
	{
	}

	void MetaKnight::AddStarEffect(eDirection dir)
	{
	}

	void MetaKnight::AppearReady()
	{
	}

	void MetaKnight::Appear()
	{
	}

	void MetaKnight::Idle()
	{
	}

	void MetaKnight::Walk()
	{
	}

	void MetaKnight::Dash()
	{
	}

	void MetaKnight::DashAttack()
	{
	}

	void MetaKnight::Slash1()
	{
	}

	void MetaKnight::Slash2()
	{
	}

	void MetaKnight::Jump()
	{
	}

	void MetaKnight::Turn()
	{
	}

	void MetaKnight::Drop()
	{
	}

	void MetaKnight::SpinAttack()
	{
	}

	void MetaKnight::SparkAttack()
	{
	}

	void MetaKnight::TornadoAttack()
	{
	}

	void MetaKnight::Dead()
	{
	}
}