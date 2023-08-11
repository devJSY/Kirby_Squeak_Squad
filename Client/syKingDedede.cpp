#include "syKingDedede.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syRigidbody.h"
#include "sySound.h"
#include "sySceneManager.h"

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