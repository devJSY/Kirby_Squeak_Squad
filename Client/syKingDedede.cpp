#include "syKingDedede.h"
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


#include "syInput.h"

namespace sy
{
	KingDedede::KingDedede(eAbilityType type)
		: Enemy(type)
		, mState(eKingDededeState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::LEFT)
	{
	}

	KingDedede::~KingDedede()
	{
	}

	void KingDedede::Initialize()
	{
		// 체력 설정
		SetHP(500);

		// 텍스쳐 로드
		Texture* KingDedede_Right = ResourceManager::Load<Texture>(L"KingDedede_Right_Tex", L"..\\Resources\\Enemy\\Boss\\KingDedede\\KingDedede_Right.bmp");
		Texture* KingDedede_Left = ResourceManager::Load<Texture>(L"KingDedede_Left_Tex", L"..\\Resources\\Enemy\\Boss\\KingDedede\\KingDedede_Left.bmp");
		KingDedede_Right->SetType(eTextureType::Bmp);
		KingDedede_Left->SetType(eTextureType::Bmp);

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidBody = AddComponent<Rigidbody>();
		Collider* col = GetComponent<Collider>();
		col->SetSize(Vector2(35.f, 40.f));
		col->SetOffset(Vector2(0.f, 5.f));

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(0.f, 30.f);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Idle", Vector2::Zero, Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.4f, 4, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Idle", Vector2::Zero, Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.4f, 4, Animationoffset);
		
		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Walk", Vector2(768.f, 0.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 4, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Walk", Vector2(768.f, 0.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 4, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_JumpReady", Vector2(768.f, 256.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 1, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_JumpReady", Vector2(768.f, 256.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 1, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Jump", Vector2(1024.f, 256.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.1f, 1, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Jump", Vector2(1024.f, 256.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.1f, 1, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Drop", Vector2(0.f, 512.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 1, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Drop", Vector2(0.f, 512.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 1, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_AttackReady", Vector2(256.f, 512.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.1f, 4, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_AttackReady", Vector2(256.f, 512.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.1f, 4, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_AttackRun", Vector2(0.f, 768.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.1f, 4, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_AttackRun", Vector2(0.f, 768.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.1f, 4, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Attack", Vector2(1024.f, 768.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 6, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Attack", Vector2(1024.f, 768.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 6, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_FlyReady", Vector2(0.f, 1280.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 2, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_FlyReady", Vector2(0.f, 1280.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 2, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_FlyUp", Vector2(512.f, 1280.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 1, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_FlyUp", Vector2(512.f, 1280.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 1, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Fly", Vector2(768.f, 1280.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 2, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Fly", Vector2(768.f, 1280.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 2, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_FlyDrop", Vector2(0.f, 1536.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 1, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_FlyDrop", Vector2(0.f, 1536.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 1, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_MonsterSummonReady", Vector2(256.f, 1536.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 3, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_MonsterSummonReady", Vector2(256.f, 1536.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.3f, 3, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_MonsterSummonJump", Vector2(1024.f, 1536.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 1, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_MonsterSummonJump", Vector2(1024.f, 1536.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 1, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_MonsterSummonDrop", Vector2(0.f, 1792.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 1, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_MonsterSummonDrop", Vector2(0.f, 1792.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 1, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_MonsterSummon", Vector2(256.f, 1792.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 8, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_MonsterSummon", Vector2(256.f, 1792.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 8, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Damage", Vector2(768.f, 2048.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 2, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Damage", Vector2(768.f, 2048.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 2, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_DeadJump", Vector2(0.f, 2304.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 1, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_DeadJump", Vector2(0.f, 2304.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 1, Animationoffset);

		mAnimator->CreateAnimation(KingDedede_Right, L"KingDedede_Right_Dead", Vector2(256.f, 2304.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 2, Animationoffset);
		mAnimator->CreateAnimation(KingDedede_Left, L"KingDedede_Left_Dead", Vector2(256.f, 2304.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.2f, 2, Animationoffset);
		
		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"KingDedede_Left_Idle", true);

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

		// 테스트용 상태변경
		if (Input::GetKeyDown(eKeyCode::M))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"KingDedede_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"KingDedede_Left_Idle", true);

			mState = eKingDededeState::Idle;
		}

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
		case eKingDededeState::DeadJump:
			DeadJump();
			break;
		case eKingDededeState::Dead:
			Dead();
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
		Damaged(DamageAmount);

		// 이미 데미지 상태면 애니메이션, 피격 넉백 처리하지않음
		if (mState == eKingDededeState::Damage || mState == eKingDededeState::Dead)
			return;

		mState = eKingDededeState::Damage;

		if (HitDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"KingDedede_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"KingDedede_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void KingDedede::CheckPixelCollision()
	{
		std::wstring CurSceneName = SceneManager::GetActiveScene()->GetName();

		Texture* PixelTex = nullptr;

		// Stage타입에따라 픽셀텍스쳐 변경하기
		if (CurSceneName == L"AbilityTestScene")
			PixelTex = ResourceManager::Find<Texture>(L"AbilityTest_Pixel");
		else if (CurSceneName == L"Level1_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"King_Dedede_Stage_Pixel");
		else
			PixelTex = ResourceManager::Find<Texture>(L"Stage1_Pixel");

		if (PixelTex == nullptr)
			return;

		// Offset 픽셀 좌상단위치 설정
		Vector2 offset = Vector2::Zero;

		if (CurSceneName == L"AbilityTestScene"
			|| CurSceneName == L"King_Dedede_Stage_Pixel"
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

		COLORREF LBColorOffsetY = PixelTex->GetTexturePixel((int)LB.x, int(LB.y + 1));
		COLORREF RBColorOffsetY = PixelTex->GetTexturePixel((int)RB.x, int(RB.y + 1));

		// 바닥 ~ 바닥 + 1픽셀 범위가 아닐경우 Ground false 처리
		if (!(LBColor == RGB(0, 0, 255) || LBColorOffsetY == RGB(0, 0, 255)
			|| RBColor == RGB(0, 0, 255) || RBColorOffsetY == RGB(0, 0, 255)
			|| LBColor == RGB(255, 0, 0) || LBColorOffsetY == RGB(255, 0, 0)
			|| RBColor == RGB(255, 0, 0) || RBColorOffsetY == RGB(255, 0, 0)))
		{
			mRigidBody->SetGround(false);
		}


		// Right Stop Check
		COLORREF RBColorOffsetX = PixelTex->GetTexturePixel(int(RB.x + 1), (int)RB.y);

		if (RBColor == RGB(0, 255, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 1.f;
			mTransform->SetPosition(pos);
		}
		else if (RBColorOffsetX == RGB(0, 255, 0))
		{
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 3.f;
			mTransform->SetPosition(pos);
		}

		// Left Stop Check
		COLORREF LBColorOffsetX = PixelTex->GetTexturePixel(int(LB.x - 1), (int)LB.y);

		if (LBColor == RGB(0, 255, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x += 1.f;
			mTransform->SetPosition(pos);
		}
		else if (LBColorOffsetX == RGB(0, 255, 0))
		{
			Vector2 pos = mTransform->GetPosition();
			pos.x += 3.f;
			mTransform->SetPosition(pos);
		}
	}

	void KingDedede::Idle()
	{
		// 땅에 닿은 상태가 아니라면 Drop으로 변경
		if (!mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"KingDedede_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"KingDedede_Left_Drop", true);

			mState = eKingDededeState::Drop;
		}

		// 플레이어 방향을 바라보도록 설정
		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 Dir = PlayerPos - mTransform->GetPosition();
		if (Dir.x > 0.f)
		{
			mAnimator->PlayAnimation(L"KingDedede_Right_Idle", true);
			mTransform->SetDirection(eDirection::RIGHT);
			mDir = eDirection::RIGHT;
		}
		else
		{
			mAnimator->PlayAnimation(L"KingDedede_Left_Idle", true);
			mTransform->SetDirection(eDirection::LEFT);
			mDir = eDirection::LEFT;
		}

		// 상태처리
		if (fabs(Dir.x) > 50.f)
		{
			int randomNumber = std::rand() % 3;
			if (randomNumber == 0)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"KingDedede_Right_Walk", true);
				else
					mAnimator->PlayAnimation(L"KingDedede_Left_Walk", true);

				mState = eKingDededeState::Walk;
			}
			else if (randomNumber == 1)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"KingDedede_Right_JumpReady", false);
				else
					mAnimator->PlayAnimation(L"KingDedede_Left_JumpReady", false);

				mState = eKingDededeState::JumpReady;
			}
			else if (randomNumber == 2)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"KingDedede_Right_FlyReady", false);
				else
					mAnimator->PlayAnimation(L"KingDedede_Left_FlyReady", false);

				mState = eKingDededeState::FlyReady;
			}
		}
		else
		{
			int randomNumber = std::rand() % 100;
			if (randomNumber % 2 == 0)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"KingDedede_Right_AttackReady", false);
				else
					mAnimator->PlayAnimation(L"KingDedede_Left_AttackReady", false);

				mState = eKingDededeState::AttackReady;
			}
			else 
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"KingDedede_Right_MonsterSummonReady", false);
				else
					mAnimator->PlayAnimation(L"KingDedede_Left_MonsterSummonReady", false);

				mState = eKingDededeState::MonsterSummonReady;
			}
		}
	}

	void KingDedede::Walk()
	{
		// 좌우 이동
		Vector2 pos = mTransform->GetPosition();

		if (mDir == eDirection::RIGHT)
			pos.x += 20.f * Time::DeltaTime();
		else
			pos.x -= 20.f * Time::DeltaTime();

		mTransform->SetPosition(pos);


		// 플레이어 방향을 바라보도록 설정
		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 Dir = PlayerPos - mTransform->GetPosition();

		// 상태처리
		if (fabs(Dir.x) < 50.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"KingDedede_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"KingDedede_Left_Idle", true);

			mState = eKingDededeState::Idle;
		}
	}

	void KingDedede::JumpReady()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"KingDedede_Right_Jump", true);
			else
				mAnimator->PlayAnimation(L"KingDedede_Left_Jump", true);

			mState = eKingDededeState::Jump;
		}
	}

	void KingDedede::Jump()
	{
	}

	void KingDedede::Drop()
	{
		if (mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"KingDedede_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"KingDedede_Left_Idle", true);

			mState = eKingDededeState::Idle;
		}
	}

	void KingDedede::AttackReady()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"KingDedede_Right_AttackRun", true);
			else
				mAnimator->PlayAnimation(L"KingDedede_Left_AttackRun", true);

			mState = eKingDededeState::AttackRun;
		}
	}

	void KingDedede::AttackRun()
	{
	}

	void KingDedede::Attack()
	{
	}

	void KingDedede::FlyReady()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"KingDedede_Right_FlyUp", true);
			else
				mAnimator->PlayAnimation(L"KingDedede_Left_FlyUp", true);

			mState = eKingDededeState::FlyUp;
		}
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
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"KingDedede_Right_MonsterSummonJump", true);
			else
				mAnimator->PlayAnimation(L"KingDedede_Left_MonsterSummonJump", true);

			mState = eKingDededeState::MonsterSummonJump;
		}
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
		static float StateChangeDelay = 0.f;

		StateChangeDelay += Time::DeltaTime();

		if (mAnimator->IsActiveAnimationComplete() && StateChangeDelay > 1.f)
		{
			StateChangeDelay = 0.f;
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			mRigidBody->SetLimitVelocity(Vector2(300.f, 300.f));

			if (GetCurHP() <= 0.f)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"KingDedede_Right_Dead", false);
				else
					mAnimator->PlayAnimation(L"KingDedede_Left_Dead", false);

				mState = eKingDededeState::Dead;
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"KingDedede_Right_Idle", true);
				else
					mAnimator->PlayAnimation(L"KingDedede_Left_Idle", true);

				mState = eKingDededeState::Idle;
			}
		}
	}

	void KingDedede::DeadJump()
	{
	}

	void KingDedede::Dead()
	{
	}
}