#include "syDaroach.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syCollider.h"
#include "sySound.h"
#include "syTime.h"
#include "sySceneManager.h"
#include "syPlayer.h"
#include "syInput.h"

namespace sy
{
	Daroach::Daroach(eAbilityType type)
		: Enemy(type)
		, mState(eDaroachState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mCollider(nullptr)
		, mDir(eDirection::RIGHT)
		, mStateChangeDelay(0.f)
		, FixedPos{}
	{
		FixedPos[0].x = 40.f;
		FixedPos[0].y = 40.f;

		FixedPos[1].x = 128.f;
		FixedPos[1].y = 40.f;

		FixedPos[2].x = 200.f;
		FixedPos[2].y = 40.f;

		FixedPos[3].x = 40.f;
		FixedPos[3].y = 110.f;

		FixedPos[4].x = 128.f;
		FixedPos[4].y = 96.f;

		FixedPos[5].x = 200.f;
		FixedPos[5].y = 110.f;
	}

	Daroach::~Daroach()
	{
	}

	void Daroach::Initialize()
	{
		// 체력 설정
		SetHP(500);

		// 텍스쳐 로드
		Texture* Daroach_Right_Tex = ResourceManager::Load<Texture>(L"Daroach_Right_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_Right.bmp");
		Texture* Daroach_Left_Tex = ResourceManager::Load<Texture>(L"Daroach_Left_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_Left.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mCollider = GetComponent<Collider>();
		mCollider->SetSize(Vector2(40.f, 40.f));
		//mCollider->SetOffset(Vector2(0.f, 0.f));

		mTransform->SetPosition(FixedPos[1]);

		// 애니메이션 생성
		std::vector<Vector2> Daroach_StarAttack_offset = { Vector2(0.f,5.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,21.f), Vector2(0.f,26.f), Vector2(0.f, 26.f) };

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_Idle", Vector2(8.f, 15.f), Vector2(55.f, 56.f), Vector2(55.f, 0.f), 0.15f, 4);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_Idle", Vector2(757.f, 15.f), Vector2(55.f, 56.f), Vector2(-55.f, 0.f), 0.15f, 4);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_BombAttackReady", Vector2(236.f, 86.f), Vector2(51.f, 55.f), Vector2(51.f, 0.f), 0.15f, 2);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_BombAttackReady", Vector2(533.f, 86.f), Vector2(51.f, 55.f), Vector2(-51.f, 0.f), 0.15f, 2);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_BombAttack", Vector2(486.f, 88.f), Vector2(70.f, 55.f), Vector2(70.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_BombAttack", Vector2(264.f, 88.f), Vector2(70.f, 55.f), Vector2(-70.f, 0.f), 0.1f, 4);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_WandUp", Vector2(4.f, 229.f), Vector2(89.f, 86.f), Vector2(89.f, 0.f), 0.1f, 3);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_WandUp", Vector2(727.f, 229.f), Vector2(89.f, 86.f), Vector2(-89.f, 0.f), 0.1f, 3);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_WandCharge", Vector2(289.f, 231.f), Vector2(55.f, 83.f), Vector2(55.f, 0.f), 0.2f, 2);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_WandCharge", Vector2(476.f, 231.f), Vector2(55.f, 83.f), Vector2(-55.f, 0.f), 0.2f, 2);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_WandAttack", Vector2(444.f, 257.f), Vector2(64.f, 53.f), Vector2(64.f, 0.f), 0.2f, 2);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_WandAttack", Vector2(312.f, 257.f), Vector2(64.f, 53.f), Vector2(-64.f, 0.f), 0.2f, 2);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_Teleport", Vector2(273.f, 3.f), Vector2(60.f, 70.f), Vector2(60.f, 0.f), 0.1f, 3);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_Teleport", Vector2(487.f, 3.f), Vector2(60.f, 70.f), Vector2(-60.f, 0.f), 0.1f, 3);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_TeleportEnd", Vector2(393.f, 3.f), Vector2(60.f, 70.f), Vector2(-60.f, 0.f), 0.1f, 3);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_TeleportEnd", Vector2(367.f, 3.f), Vector2(60.f, 70.f), Vector2(60.f, 0.f), 0.1f, 3);

		mAnimator->CreateAnimation_Offset(Daroach_Right_Tex, L"Daroach_Right_StarAttack", Vector2(1.f, 381.f), Vector2(100.f, 89.f), Vector2(100.f, 0.f), 0.1f, 8, Daroach_StarAttack_offset);
		mAnimator->CreateAnimation_Offset(Daroach_Left_Tex, L"Daroach_Left_StarAttack", Vector2(719.f, 381.f), Vector2(100.f, 89.f), Vector2(-100.f, 0.f), 0.1f, 8, Daroach_StarAttack_offset);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_Death", Vector2(170.f, 152.f), Vector2(71.f, 56.f), Vector2(71.f, 0.f), 2.5f, 1);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_Death", Vector2(579.f, 152.f), Vector2(71.f, 56.f), Vector2(-71.f, 0.f), 2.5f, 1);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_End", Vector2(252.f, 159.f), Vector2(61.f, 44.f), Vector2(61.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_End", Vector2(507.f, 159.f), Vector2(61.f, 44.f), Vector2(-61.f, 0.f), 1.f, 1);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"Daroach_Right_Idle", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"Daroach_Teleport", L"..\\Resources\\Sound\\Effect\\Daroach\\Teleport.wav");


		Enemy::Initialize();
	}

	void Daroach::Update()
	{
		// 테스트용 상태변경
		if (Input::GetKeyDown(eKeyCode::One))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_BombAttackReady", false);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_BombAttackReady", false);

			mState = eDaroachState::BombAttackReady;
		}

		if (Input::GetKeyDown(eKeyCode::Two))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_WandUp", false);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_WandUp", false);

			mState = eDaroachState::WandUp;
		}

		if (Input::GetKeyDown(eKeyCode::Three))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_Teleport", false);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_Teleport", false);

			mState = eDaroachState::Teleport;
		}

		if (Input::GetKeyDown(eKeyCode::Four))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_StarAttack", false);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_StarAttack", false);

			mState = eDaroachState::StarAttack;
		}

		switch (mState)
		{
		case eDaroachState::Idle:
			Idle();
			break;
		case eDaroachState::BombAttackReady:
			BombAttackReady();
			break;
		case eDaroachState::BombAttack:
			BombAttack();
			break;
		case eDaroachState::WandUp:
			WandUp();
			break;
		case eDaroachState::WandCharge:
			WandCharge();
			break;
		case eDaroachState::WandAttack:
			WandAttack();
			break;
		case eDaroachState::Teleport:
			Teleport();
			break;
		case eDaroachState::TeleportEnd:
			TeleportEnd();
			break;
		case eDaroachState::StarAttack:
			StarAttack();
			break;
		case eDaroachState::Damage:
			Damage();
			break;
		case eDaroachState::Dead:
			Dead();
			break;
		default:
			break;
		}

		Enemy::Update();
	}

	void Daroach::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void Daroach::OnCollisionEnter(Collider* other)
	{
	}

	void Daroach::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void Daroach::Idle()
	{
		// 플레이어 방향을 바라보도록 설정
		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 Dir = PlayerPos - mTransform->GetPosition();
		if (Dir.x > 0.f)
		{
			if (mDir == eDirection::LEFT)
			{
				mAnimator->PlayAnimation(L"Daroach_Right_Idle", true);
				mTransform->SetDirection(eDirection::RIGHT);
				mDir = eDirection::RIGHT;
			}
		}
		else
		{
			if (mDir == eDirection::RIGHT)
			{
				mAnimator->PlayAnimation(L"Daroach_Left_Idle", true);
				mTransform->SetDirection(eDirection::LEFT);
				mDir = eDirection::LEFT;
			}
		}

		// 상태처리
		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 1.f)
		{
			mStateChangeDelay = 0.f;

			int randomNumber = std::rand() % 4;
			if (randomNumber == 0)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"Daroach_Right_BombAttackReady", false);
				else
					mAnimator->PlayAnimation(L"Daroach_Left_BombAttackReady", false);

				mState = eDaroachState::BombAttackReady;
			}
			else if (randomNumber == 1)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"Daroach_Right_WandUp", false);
				else
					mAnimator->PlayAnimation(L"Daroach_Left_WandUp", false);

				mState = eDaroachState::WandUp;
			}
			else if (randomNumber == 2)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"Daroach_Right_Teleport", false);
				else
					mAnimator->PlayAnimation(L"Daroach_Left_Teleport", false);

				mState = eDaroachState::Teleport;
			}
			else if (randomNumber == 3)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"Daroach_Right_StarAttack", false);
				else
					mAnimator->PlayAnimation(L"Daroach_Left_StarAttack", false);

				mState = eDaroachState::StarAttack;
			}
		}
	}

	void Daroach::BombAttackReady()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_BombAttack", false);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_BombAttack", false);

			mState = eDaroachState::BombAttack;

			// Bomb 랜덤 생성
			int randomNumber = std::rand() % 100;
			if (randomNumber % 2 == 0)
			{

			}
			else
			{

			}
		}
	}

	void Daroach::WandUp()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_WandCharge", true);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_WandCharge", true);

			mState = eDaroachState::WandCharge;
		}
	}

	void Daroach::WandCharge()
	{
		// 플레이어 방향을 바라보도록 설정
		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 Dir = PlayerPos - mTransform->GetPosition();
		if (Dir.x > 0.f)
		{
			if (mDir == eDirection::LEFT)
			{
				mAnimator->PlayAnimation(L"Daroach_Right_WandCharge", true);
				mTransform->SetDirection(eDirection::RIGHT);
				mDir = eDirection::RIGHT;
			}
		}
		else
		{
			if (mDir == eDirection::RIGHT)
			{
				mAnimator->PlayAnimation(L"Daroach_Left_WandCharge", true);
				mTransform->SetDirection(eDirection::LEFT);
				mDir = eDirection::LEFT;
			}
		}

		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 3.f)
		{
			mStateChangeDelay = 0.f;

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_WandAttack", true);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_WandAttack", true);

			mState = eDaroachState::WandAttack;
		}
	}

	void Daroach::WandAttack()
	{
		// 플레이어 y축 따라가야함









		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 3.f)
		{
			mStateChangeDelay = 0.f;

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_Idle", true);

			mState = eDaroachState::Idle;
		}
	}

	void Daroach::BombAttack()
	{
		mStateChangeDelay += Time::DeltaTime();

		if (mAnimator->IsActiveAnimationComplete() && mStateChangeDelay > 1.f)
		{
			mStateChangeDelay = 0.f;

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_Idle", true);

			mState = eDaroachState::Idle;
		}
	}

	void Daroach::Teleport()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			mStateChangeDelay = 0.f;

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_TeleportEnd", false);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_TeleportEnd", false);

			mState = eDaroachState::TeleportEnd;


			int randomPos = std::rand() % 6;
			mTransform->SetPosition(FixedPos[randomPos]);
		}
	}

	void Daroach::TeleportEnd()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			mStateChangeDelay = 0.f;

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_Idle", true);

			mState = eDaroachState::Idle;
		}
	}

	void Daroach::StarAttack()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			mStateChangeDelay = 0.f;

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_Idle", true);

			mState = eDaroachState::Idle;
		}
	}

	void Daroach::Damage()
	{
	}

	void Daroach::Dead()
	{
	}
}