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
#include "syDaroach_Charge_Energe.h"
#include "syObject.h"
#include "syDaroach_Energe.h"
#include "syDaroach_Bomb.h"
#include "syDaroach_TimeBomb.h"

namespace sy
{
	Daroach::Daroach(eAbilityType type)
		: BossEnemy(type)
		, mState(eDaroachState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mCollider(nullptr)
		, mDir(eDirection::RIGHT)
		, mStateChangeDelay(0.f)
		, FixedPos{}
		, mbDamaged(false)
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
		mRigidBody = AddComponent<Rigidbody>();
		mCollider = GetComponent<Collider>();
		mCollider->SetSize(Vector2(40.f, 40.f));
		//mCollider->SetOffset(Vector2(0.f, 0.f));

		mRigidBody->SetGround(true);

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

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_Dead", Vector2(170.f, 152.f), Vector2(71.f, 56.f), Vector2(71.f, 0.f), 2.5f, 1);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_Dead", Vector2(579.f, 152.f), Vector2(71.f, 56.f), Vector2(-71.f, 0.f), 2.5f, 1);

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
		// 데미지 딜레이 설정
		static float DamageDelayTime = 0.f;
		if(mbDamaged)
			DamageDelayTime += Time::DeltaTime();

		if (DamageDelayTime > 1.f)
		{
			mbDamaged = false;
			DamageDelayTime = 0.f;
		}


		// 방향 설정
		mDir = mTransform->GetDirection();

		// 픽셀충돌 체크
		CheckPixelCollision();

		// 테스트용 상태변경
		if (Input::GetKeyDown(eKeyCode::One))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_BombAttackReady", false);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_BombAttackReady", false);

			mState = eDaroachState::BombAttackReady;
			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Two))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_WandUp", false);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_WandUp", false);

			mState = eDaroachState::WandUp;
			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Three))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_Teleport", false);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_Teleport", false);

			mState = eDaroachState::Teleport;
			mStateChangeDelay = 0.f;

			ResourceManager::Find<Sound>(L"Daroach_Teleport")->Play(false);
		}

		if (Input::GetKeyDown(eKeyCode::Four))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_StarAttack", false);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_StarAttack", false);

			mState = eDaroachState::StarAttack;
			mStateChangeDelay = 0.f;
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
		Damaged(DamageAmount);

		// 이미 데미지 상태면 애니메이션, 피격 넉백 처리하지않음
		if (mbDamaged || mState == eDaroachState::Dead)
			return;

		if (GetCurHP() <= 0.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_Dead", false);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_Dead", false);

			mState = eDaroachState::Dead;
		}

		mbDamaged = true;
	}

	void Daroach::CheckPixelCollision()
	{
		std::wstring CurSceneName = SceneManager::GetActiveScene()->GetName();

		Texture* PixelTex = nullptr;

		// Stage타입에따라 픽셀텍스쳐 변경하기
		if (CurSceneName == L"AbilityTestScene")
			PixelTex = ResourceManager::Find<Texture>(L"AbilityTest_Pixel");
		else if (CurSceneName == L"Level1_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"King_Dedede_Stage_Pixel");
		else if (CurSceneName == L"Level6_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"Daroach_Pixel");
		else
			PixelTex = ResourceManager::Find<Texture>(L"Stage1_Pixel");

		if (PixelTex == nullptr)
			return;

		// Offset 픽셀 좌상단위치 설정
		Vector2 offset = Vector2::Zero;

		if (CurSceneName == L"AbilityTestScene"
			|| CurSceneName == L"King_Dedede_Stage_Pixel"
			|| CurSceneName == L"Daroach_Pixel"
			|| CurSceneName == L"Level1_Stage1Scene")
		{
			offset = Vector2::Zero;
		}
		else if (CurSceneName == L"Level1_Stage2Scene")
		{
			offset = Vector2(0, 347.f);
		}
		else if (CurSceneName == L"Level1_Stage3Scene")
		{
			offset = Vector2(0, 679.f);
		}
		else if (CurSceneName == L"Level1_Stage4Scene")
		{
			offset = Vector2(1603.f, 137.f);
		}

		Collider* col = GetComponent<Collider>();
		Vector2 ColPos = col->GetPosition();
		Vector2 ColSize = col->GetSize();

		Vector2 LT = Vector2(ColPos.x - (ColSize.x / 2.f), ColPos.y - (ColSize.y / 2.f));
		Vector2 RT = Vector2(ColPos.x + (ColSize.x / 2.f), ColPos.y - (ColSize.y / 2.f));
		Vector2 LB = Vector2(ColPos.x - (ColSize.x / 2.f), ColPos.y + (ColSize.y / 2.f));
		Vector2 RB = Vector2(ColPos.x + (ColSize.x / 2.f), ColPos.y + (ColSize.y / 2.f));

		LT += offset;
		RT += offset;
		LB += offset;
		RB += offset;

		COLORREF LTColor = PixelTex->GetTexturePixel((int)LT.x, (int)LT.y);
		COLORREF RTColor = PixelTex->GetTexturePixel((int)RT.x, (int)RT.y);
		COLORREF LBColor = PixelTex->GetTexturePixel((int)LB.x, (int)LB.y);
		COLORREF RBColor = PixelTex->GetTexturePixel((int)RB.x, (int)RB.y);


		// 바닥 처리
		if (LBColor == RGB(0, 0, 255) || RBColor == RGB(0, 0, 255)
			|| LBColor == RGB(255, 0, 0) || RBColor == RGB(255, 0, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.y -= 1.f;
			mTransform->SetPosition(pos);
			mRigidBody->SetGround(true);			
		}
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

		if (mStateChangeDelay > 0.1f)
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

				ResourceManager::Find<Sound>(L"Daroach_Teleport")->Play(false);
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
				Daroach_Bomb* bomb = new Daroach_Bomb(this);
				object::ActiveSceneAddGameObject(eLayerType::Effect, bomb);
			}
			else
			{
				Daroach_TimeBomb* bomb = new Daroach_TimeBomb(this);
				object::ActiveSceneAddGameObject(eLayerType::Effect, bomb);
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

			Daroach_Charge_Energe* energe = new Daroach_Charge_Energe(this);
			object::ActiveSceneAddGameObject(eLayerType::Effect, energe);
		}
	}

	void Daroach::WandCharge()
	{
		// 플레이어 y축 따라 가도록 설정
		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 Dir = PlayerPos - mTransform->GetPosition();

		Dir.Normalize();
		Dir.y *= 50.f * Time::DeltaTime();
		Vector2 pos = mTransform->GetPosition();
		pos.y += Dir.y;
		mTransform->SetPosition(pos);


		// 플레이어 방향을 바라보도록 설정
		PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Dir = PlayerPos - mTransform->GetPosition();
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

			Daroach_Energe* energe = new Daroach_Energe(this);
			object::ActiveSceneAddGameObject(eLayerType::Effect, energe);
		}
	}

	void Daroach::WandAttack()
	{
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
		static int TeleportCount = 0;

		if (mAnimator->IsActiveAnimationComplete())
		{
			if (TeleportCount < 2)
			{
				// 플레이어 방향을 바라보도록 설정
				Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
				Vector2 Dir = PlayerPos - mTransform->GetPosition();
				if (Dir.x > 0.f)
				{
					if (mDir == eDirection::LEFT)
					{
						mTransform->SetDirection(eDirection::RIGHT);
						mDir = eDirection::RIGHT;
					}
				}
				else
				{
					if (mDir == eDirection::RIGHT)
					{
						mTransform->SetDirection(eDirection::LEFT);
						mDir = eDirection::LEFT;
					}
				}

				TeleportCount++;

				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"Daroach_Right_Teleport", false);
				else
					mAnimator->PlayAnimation(L"Daroach_Left_Teleport", false);

				mState = eDaroachState::Teleport;

				ResourceManager::Find<Sound>(L"Daroach_Teleport")->Play(false);
			}
			else
			{
				TeleportCount = 0;

				mStateChangeDelay = 0.f;

				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"Daroach_Right_Idle", true);
				else
					mAnimator->PlayAnimation(L"Daroach_Left_Idle", true);

				mState = eDaroachState::Idle;
			}
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

	void Daroach::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Daroach_Right_End", true);
			else
				mAnimator->PlayAnimation(L"Daroach_Left_End", true);

			mRigidBody->SetGround(false);
		}		
	}
}