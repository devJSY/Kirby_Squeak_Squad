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
#include "syObject.h"
#include "syInput.h"

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
		
		MetaKnight_Right_Tex->SetScale(Vector2(0.35f, 0.35f));
		MetaKnight_Left_Tex->SetScale(Vector2(0.35f, 0.35f));
		MetaKnight_Appear_Tex->SetScale(Vector2(0.35f, 0.35f));
		MetaKnight_Dead_Tex->SetScale(Vector2(0.35f, 0.35f));

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidBody = AddComponent<Rigidbody>();
		mCollider = GetComponent<Collider>();
		mCollider->SetSize(Vector2(15.f, 15.f));

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(0.f, 0.f);
		mAnimator->CreateAnimation(MetaKnight_Appear_Tex, L"MetaKnight_AppearReady", Vector2::Zero, Vector2(480.f, 480.f), Vector2(480.f, 0.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Appear_Tex, L"MetaKnight_Appear", Vector2::Zero, Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.08f, 22, Animationoffset);
		
		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Idle", Vector2::Zero, Vector2(480.f, 480.f), Vector2(480.f, 0.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Idle", Vector2::Zero, Vector2(480.f, 480.f), Vector2(480.f, 0.f), 1.f, 1, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Walk", Vector2(0.f, 480.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 7, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Walk", Vector2(0.f, 480.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 7, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Dash", Vector2(0.f, 960.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.05f, 5, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Dash", Vector2(0.f, 960.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.05f, 5, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_DashAttack", Vector2(0.f, 1440.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.05f, 6, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_DashAttack", Vector2(0.f, 1440.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.05f, 6, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Slash1", Vector2(0.f, 1920.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.05f, 8, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Slash1", Vector2(0.f, 1920.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.05f, 8, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Slash2", Vector2(0.f, 2400.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.05f, 8, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Slash2", Vector2(0.f, 2400.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.05f, 8, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Jump", Vector2(0.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 2, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Jump", Vector2(0.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 2, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Turn", Vector2(960.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.07f, 7, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Turn", Vector2(960.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.07f, 7, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Drop", Vector2(4320.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Drop", Vector2(4320.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 1.f, 1, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_SpinAttack", Vector2(0.f, 3360.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.03f, 5, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_SpinAttack", Vector2(0.f, 3360.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.03f, 5, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_SpinAttackEnd", Vector2(2400.f, 3360.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 2, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_SpinAttackEnd", Vector2(2400.f, 3360.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 2, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_JumpDownAttack", Vector2(0.f, 3840.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 3, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_JumpDownAttack", Vector2(0.f, 3840.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 3, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_TornadoAttackCharge", Vector2(0.f, 4320.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 4, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_TornadoAttackCharge", Vector2(0.f, 4320.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 4, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_TornadoAttack", Vector2(1440.f, 4320.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 1, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_TornadoAttack", Vector2(1440.f, 4320.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 1, Animationoffset);
					
		mAnimator->CreateAnimation(MetaKnight_Dead_Tex, L"MetaKnight_Dead_1", Vector2::Zero, Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.08f, 11, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Dead_Tex, L"MetaKnight_Dead_2", Vector2(0.f, 480.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.08f, 6, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Dead_Tex, L"MetaKnight_Dead_3", Vector2(0.f, 960.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.08f, 15, Animationoffset);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"MetaKnight_AppearReady", true);

		// Sound Load
		BossEnemy::Initialize();
	}

	void MetaKnight::Update()
	{
		// 방향 설정
		mDir = mTransform->GetDirection();

		// 픽셀충돌 체크
		CheckPixelCollision();

		// 테스트용 상태변경
		if (Input::GetKeyDown(eKeyCode::One))
		{
			mState = eMetaKnightState::Dead1;
			mAnimator->PlayAnimation(L"MetaKnight_Dead_1", false);
			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Two))
		{


			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Three))
		{

			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Four))
		{

			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Five))
		{

			mStateChangeDelay = 0.f;
		}

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
		case eMetaKnightState::SpinAttackEnd:
			SpinAttackEnd();
			break;
		case eMetaKnightState::JumpDownAttack:
			JumpDownAttack();
			break;
		case eMetaKnightState::TornadoAttackCharge:
			TornadoAttackCharge();
			break;
		case eMetaKnightState::TornadoAttack:
			TornadoAttack();
			break;
		case eMetaKnightState::Dead1:
			Dead1();
			break;
		case eMetaKnightState::Dead2:
			Dead2();
			break;
		case eMetaKnightState::Dead3:
			Dead3();
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
		std::wstring CurSceneName = SceneManager::GetActiveScene()->GetName();

		Texture* PixelTex = nullptr;

		// Stage타입에따라 픽셀텍스쳐 변경하기
		if (CurSceneName == L"AbilityTestScene")
			PixelTex = ResourceManager::Find<Texture>(L"AbilityTest_Pixel");
		else if (CurSceneName == L"Level1_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"King_Dedede_Stage_Pixel");
		else if (CurSceneName == L"Level6_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"Daroach_Pixel");
		else if (CurSceneName == L"Level7_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"Meta_Knight_Pixel");
		else if (CurSceneName == L"Level8_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"DarkNebula_Pixel");
		else
			PixelTex = ResourceManager::Find<Texture>(L"Stage1_Pixel");

		if (PixelTex == nullptr)
			return;

		// Offset 픽셀 좌상단위치 설정
		Vector2 offset = Vector2::Zero;

		if (CurSceneName == L"AbilityTestScene"
			|| CurSceneName == L"King_Dedede_Stage_Pixel"
			|| CurSceneName == L"Daroach_Pixel"
			|| CurSceneName == L"Meta_Knight_Pixel"
			|| CurSceneName == L"DarkNebula_Pixel"
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
			// 특정상태에선 바닥무시
			if (mState != eMetaKnightState::Jump)
				mRigidBody->SetGround(false);
		}

		// Right Stop Check
		if (RBColor == RGB(0, 255, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 1.f;
			mTransform->SetPosition(pos);
		}

		// Left Stop Check
		if (LBColor == RGB(0, 255, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x += 1.f;
			mTransform->SetPosition(pos);
		}
	}

	void MetaKnight::AddStarEffect(eDirection dir)
	{
		Vector2 pos = mTransform->GetPosition();

		if (dir == eDirection::RIGHT)
		{
			pos.x += 50.f;
			pos.y += 10.f;
			Star_Effect* effect = new Star_Effect(this, pos);
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect);
		}
		else
		{
			pos.x -= 50.f;
			pos.y += 10.f;
			Star_Effect* effect = new Star_Effect(this, pos);
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect);
		}
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

	void MetaKnight::SpinAttackEnd()
	{
	}

	void MetaKnight::JumpDownAttack()
	{
	}

	void MetaKnight::TornadoAttackCharge()
	{
	}

	void MetaKnight::TornadoAttack()
	{
	}

	void MetaKnight::Dead1()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"MetaKnight_Dead_2", false);
			mState = eMetaKnightState::Dead2;
		}
	}

	void MetaKnight::Dead2()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"MetaKnight_Dead_3", false);
			mState = eMetaKnightState::Dead3;
		}
	}

	void MetaKnight::Dead3()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}
}