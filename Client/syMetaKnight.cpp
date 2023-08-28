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
#include "syCamera.h"
#include "syMetaKnight_AttackArea.h"
#include "syMetaKnight_SlashSkill.h"
#include "syMetaKnight_TornadoSkill.h"

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
		, mStateChangeDelay(0.f)
		, mbDamaged(false)
		, mWalkDir(mDir)
		, mSlashCount(3)
	{
	}

	MetaKnight::~MetaKnight()
	{
	}

	void MetaKnight::Initialize()
	{
		// 체력 설정
		SetHP(900);

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

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Slash1", Vector2(0.f, 1920.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.035f, 8, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Slash1", Vector2(0.f, 1920.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.035f, 8, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Slash2", Vector2(0.f, 2400.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.035f, 8, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Slash2", Vector2(0.f, 2400.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.035f, 8, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Jump", Vector2(0.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 2, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Jump", Vector2(0.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 2, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Turn", Vector2(960.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.035f, 7, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Turn", Vector2(960.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.035f, 7, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_Drop", Vector2(4320.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_Drop", Vector2(4320.f, 2880.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 1.f, 1, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_SpinAttack", Vector2(0.f, 3360.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.03f, 5, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_SpinAttack", Vector2(0.f, 3360.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.03f, 5, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_SpinAttackEnd", Vector2(2400.f, 3360.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.03f, 2, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_SpinAttackEnd", Vector2(2400.f, 3360.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.03f, 2, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_JumpDownAttack", Vector2(0.f, 3840.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.03f, 3, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_JumpDownAttack", Vector2(0.f, 3840.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.03f, 3, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_TornadoSkillCharge", Vector2(0.f, 4320.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 4, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_TornadoSkillCharge", Vector2(0.f, 4320.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 4, Animationoffset);

		mAnimator->CreateAnimation(MetaKnight_Right_Tex, L"MetaKnight_Right_TornadoSkill", Vector2(1920.f, 4320.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 1, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Left_Tex, L"MetaKnight_Left_TornadoSkill", Vector2(1920.f, 4320.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 1, Animationoffset);
					
		mAnimator->CreateAnimation(MetaKnight_Dead_Tex, L"MetaKnight_Dead_1", Vector2::Zero, Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 11, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Dead_Tex, L"MetaKnight_Dead_2", Vector2(0.f, 480.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 6, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Dead_Tex, L"MetaKnight_Dead_3", Vector2(0.f, 960.f), Vector2(480.f, 480.f), Vector2(480.f, 0.f), 0.1f, 15, Animationoffset);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"MetaKnight_AppearReady", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"MetaKnight_DashSlashSound", L"..\\Resources\\Sound\\Effect\\MetaKnight\\MetaKnight_DashSlash.wav");
		ResourceManager::Load<Sound>(L"MetaKnight_SlashSound", L"..\\Resources\\Sound\\Effect\\MetaKnight\\MetaKnight_Slash.wav");

		ResourceManager::Find<Sound>(L"MetaKnight_DashSlashSound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"MetaKnight_SlashSound")->SetVolume(100.f);

		BossEnemy::Initialize();
	}

	void MetaKnight::Update()
	{
		// 데미지 딜레이 설정
		static float DamageDelayTime = 0.f;
		if (mbDamaged)
			DamageDelayTime += Time::DeltaTime();

		if (DamageDelayTime > 1.f)
		{
			mbDamaged = false;
			mAnimator->SetBlink(false);
			DamageDelayTime = 0.f;
		}

		// 방향 설정
		mDir = mTransform->GetDirection();

		// 픽셀충돌 체크
		CheckPixelCollision();

		// 테스트용 상태변경
		SetBossState();
		
		switch (mState)
		{
		case eMetaKnightState::AppearReady:
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
		case eMetaKnightState::Slash:
			Slash();
			break;
		case eMetaKnightState::SlashSkill:
			SlashSkill();
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
		case eMetaKnightState::TornadoSkillCharge:
			TornadoSkillCharge();
			break;
		case eMetaKnightState::TornadoSkill:
			TornadoSkill();
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

		// 이동제한
		Vector2 pos = mTransform->GetPosition();
		if (pos.x < 0)
		{
			pos.x = 0;
		}
		if (pos.y < 0)
		{
			pos.y = 0;
		}
		if (pos.x > Camera::GetCameraLimit().x)
		{
			pos.x = Camera::GetCameraLimit().x;
		}
		if (pos.y > Camera::GetCameraLimit().y)
		{
			pos.y = Camera::GetCameraLimit().y;
		}
		mTransform->SetPosition(pos);

		BossEnemy::Update();
	}

	void MetaKnight::Render(HDC hdc)
	{
		BossEnemy::Render(hdc);
	}

	void MetaKnight::OnCollisionEnter(Collider* other)
	{
		if (mState == eMetaKnightState::AppearReady
			|| mState == eMetaKnightState::Appear
			|| mState == eMetaKnightState::Dead1
			|| mState == eMetaKnightState::Dead2
			|| mState == eMetaKnightState::Dead3)
			return;

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr)
			return;

		// 몬스터 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

		player->TakeHit(10, Dir);
	}

	void MetaKnight::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		if (mbDamaged 
			|| mState == eMetaKnightState::AppearReady
			|| mState == eMetaKnightState::Appear
			|| mState == eMetaKnightState::Dead1
			|| mState == eMetaKnightState::Dead2
			|| mState == eMetaKnightState::Dead3)
			return;

		Damaged(DamageAmount);

		mbDamaged = true;
		mAnimator->SetBlink(true);

		if (GetCurHP() <= 0.f)
		{
			mbDamaged = false;
			mAnimator->SetBlink(false);

			mState = eMetaKnightState::Dead1;
			mAnimator->PlayAnimation(L"MetaKnight_Dead_1", false);

			mState = eMetaKnightState::Dead1;
		}
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
			pos.y -= 10.f;
			Star_Effect* effect = new Star_Effect(this, pos);
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect);
		}
		else
		{
			pos.x -= 50.f;
			pos.y -= 10.f;
			Star_Effect* effect = new Star_Effect(this, pos);
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect);
		}
	}

	void MetaKnight::SetBossState()
	{
		if (Input::GetKeyDown(eKeyCode::One))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Idle", true);

			mState = eMetaKnightState::Idle;
			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Two))
		{
			if (mDir == eDirection::RIGHT)
			{
				mAnimator->PlayAnimation(L"MetaKnight_Right_Walk", true);
				mWalkDir = eDirection::LEFT;
			}
			else
			{
				mAnimator->PlayAnimation(L"MetaKnight_Left_Walk", true);
				mWalkDir = eDirection::RIGHT;
			}

			mState = eMetaKnightState::Walk;
		}

		if (Input::GetKeyDown(eKeyCode::Three))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Dash", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Dash", true);

			mState = eMetaKnightState::Dash;
			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Four))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Jump", false);

			mState = eMetaKnightState::Jump;
			mRigidBody->SetGround(false);

			// 제자리점프 범위
			int randomY = (std::rand() % 150) + 150;
			Vector2 vel = Vector2(0.f, (float)-randomY);
			mRigidBody->SetVelocity(vel);

			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Five))
		{
			Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
			Vector2 Diff = PlayerPos - mTransform->GetPosition();

			// 플레이어와의 거리에 따라서 분기
			if (fabs(Diff.x) < 50)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_Slash1", false);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_Slash1", false);

				mState = eMetaKnightState::Slash;
				--mSlashCount;

				// 스킬 생성
				MetaKnight_AttackArea* AttackArea = new MetaKnight_AttackArea(this, Vector2(40.f, 30.f));
				object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

				ResourceManager::Find<Sound>(L"MetaKnight_SlashSound")->Play(false);
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_Slash1", false);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_Slash1", false);

				mState = eMetaKnightState::SlashSkill;
				--mSlashCount;

				// 스킬 생성
				MetaKnight_AttackArea* AttackArea = new MetaKnight_AttackArea(this, Vector2(40.f, 30.f));
				object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

				Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
				Vector2 Dir = PlayerPos - mTransform->GetPosition();

				MetaKnight_SlashSkill* SlashSkill = new MetaKnight_SlashSkill(this, Dir);
				object::ActiveSceneAddGameObject(eLayerType::Effect, SlashSkill);

				ResourceManager::Find<Sound>(L"MetaKnight_SlashSound")->Play(false);
			}

			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Six))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_TornadoSkillCharge", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_TornadoSkillCharge", true);

			mState = eMetaKnightState::TornadoSkillCharge;

			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Seven))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Jump", false);

			mState = eMetaKnightState::Jump;
			mRigidBody->SetGround(false);

			// 제자리점프, 이동점프 범위
			int randomX = (std::rand() % 100) + 100;
			int randomY = (std::rand() % 100) + 100;

			Vector2 vel = Vector2(0.f, (float)-randomY);

			// X축 랜덤 방향
			int randomSign = std::rand() % 100;
			if (randomSign % 2 == 0)
				randomX *= -1;

			// 제자리점프, 이동점프 랜덤 구현
			int randomDir = std::rand() % 100;
			if (randomDir % 2 == 0)
				vel.x = (float)randomX;

			mRigidBody->SetVelocity(vel);

			mStateChangeDelay = 0.f;
		}
	}

	void MetaKnight::Appear()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if(mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Idle", true);

			mState = eMetaKnightState::Idle;
		}
	}

	void MetaKnight::Idle()
	{
		// 땅에 닿은 상태가 아니라면 Drop으로 변경
		if (!mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Drop", true);

			mState = eMetaKnightState::Drop;
		}

		// 플레이어 방향을 바라보도록 설정
		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 Dir = PlayerPos - mTransform->GetPosition();
		if (Dir.x > 0.f)
		{
			if (mDir == eDirection::LEFT)
			{
				mAnimator->PlayAnimation(L"MetaKnight_Right_Idle", true);
				mTransform->SetDirection(eDirection::RIGHT);
				mDir = eDirection::RIGHT;
			}
		}
		else
		{
			if (mDir == eDirection::RIGHT)
			{
				mAnimator->PlayAnimation(L"MetaKnight_Left_Idle", true);
				mTransform->SetDirection(eDirection::LEFT);
				mDir = eDirection::LEFT;
			}
		}

		// 상태처리
		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 0.1f)
		{
			mStateChangeDelay = 0.f;

			int randomNumber = std::rand() % 5;
			if (randomNumber == 0)
			{
				if (mDir == eDirection::RIGHT)
				{
					mAnimator->PlayAnimation(L"MetaKnight_Right_Walk", true);				
					mWalkDir = eDirection::LEFT;
				}
				else
				{
					mAnimator->PlayAnimation(L"MetaKnight_Left_Walk", true);				
					mWalkDir = eDirection::RIGHT;
				}

				mState = eMetaKnightState::Walk;
			}
			else if (randomNumber == 1)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_Dash", true);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_Dash", true);

				mState = eMetaKnightState::Dash;
			}
			else if (randomNumber == 2)
			{
				Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
				Vector2 Diff = PlayerPos - mTransform->GetPosition();

				// 플레이어와의 거리에 따라서 분기
				if (fabs(Diff.x) < 50)
				{
					if (mDir == eDirection::RIGHT)
						mAnimator->PlayAnimation(L"MetaKnight_Right_Slash1", false);
					else
						mAnimator->PlayAnimation(L"MetaKnight_Left_Slash1", false);

					mState = eMetaKnightState::Slash;
					--mSlashCount;

					// 스킬 생성
					MetaKnight_AttackArea* AttackArea = new MetaKnight_AttackArea(this, Vector2(40.f, 30.f));
					object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

					ResourceManager::Find<Sound>(L"MetaKnight_SlashSound")->Play(false);
				}
				else
				{
					// 스킬 랜덤 분기
					int randomSkill = std::rand() % 100;
					if (randomSkill % 2 == 0)
					{
						if (mDir == eDirection::RIGHT)
							mAnimator->PlayAnimation(L"MetaKnight_Right_Slash1", false);
						else
							mAnimator->PlayAnimation(L"MetaKnight_Left_Slash1", false);

						mState = eMetaKnightState::SlashSkill;
						--mSlashCount;

						// 스킬 생성
						MetaKnight_AttackArea* AttackArea = new MetaKnight_AttackArea(this, Vector2(40.f, 30.f));
						object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

						Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
						Vector2 Dir = PlayerPos - mTransform->GetPosition();

						MetaKnight_SlashSkill* SlashSkill = new MetaKnight_SlashSkill(this, Dir);
						object::ActiveSceneAddGameObject(eLayerType::Effect, SlashSkill);

						ResourceManager::Find<Sound>(L"MetaKnight_SlashSound")->Play(false);
					}
					else
					{
						if (mDir == eDirection::RIGHT)
							mAnimator->PlayAnimation(L"MetaKnight_Right_TornadoSkillCharge", true);
						else
							mAnimator->PlayAnimation(L"MetaKnight_Left_TornadoSkillCharge", true);

						mState = eMetaKnightState::TornadoSkillCharge;
					}
				}				
			}
			else if (randomNumber == 3)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_Jump", false);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_Jump", false);

				mState = eMetaKnightState::Jump;
				mRigidBody->SetGround(false);

				// 제자리점프 범위
				int randomY = (std::rand() % 150) + 150;
				Vector2 vel = Vector2(0.f, (float)-randomY);
				mRigidBody->SetVelocity(vel);
			}
		}
	}

	void MetaKnight::Walk()
	{
		Vector2 pos = mTransform->GetPosition();
		float Accel = 0.f;

		if (mWalkDir == eDirection::RIGHT)
			Accel = 100.f;
		else
			Accel = -100.f;

		mStateChangeDelay += Time::DeltaTime();
		if (mStateChangeDelay > 2.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Idle", true);

			mState = eMetaKnightState::Idle;
			mStateChangeDelay = 0.f;
		}
		else if (mStateChangeDelay > 1.f)
			Accel *= -1.f;

		pos.x += Accel * Time::DeltaTime();
		mTransform->SetPosition(pos);

		// 땅에 닿은 상태가 아니라면 Drop으로 변경
		if (!mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Drop", true);

			mState = eMetaKnightState::Drop;
			mStateChangeDelay = 0.f;
		}

		// 플레이어 방향을 바라보도록 설정
		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 Dir = PlayerPos - mTransform->GetPosition();
		if (Dir.x > 0.f)
		{
			if (mDir == eDirection::LEFT)
			{
				mAnimator->PlayAnimation(L"MetaKnight_Right_Walk", true);
				mTransform->SetDirection(eDirection::RIGHT);
				mDir = eDirection::RIGHT;
			}
		}
		else
		{
			if (mDir == eDirection::RIGHT)
			{
				mAnimator->PlayAnimation(L"MetaKnight_Left_Walk", true);
				mTransform->SetDirection(eDirection::LEFT);
				mDir = eDirection::LEFT;
			}
		}
	}

	void MetaKnight::Dash()
	{
		Vector2 pos = mTransform->GetPosition();
		if (mDir == eDirection::RIGHT)		
			pos.x += 150.f * Time::DeltaTime();		
		else		
			pos.x += -150.f * Time::DeltaTime();
		mTransform->SetPosition(pos);

		mStateChangeDelay += Time::DeltaTime();
		if (mStateChangeDelay > 0.5f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_DashAttack", false);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_DashAttack", false);

			mState = eMetaKnightState::DashAttack;
			mStateChangeDelay = 0.f;

			// 스킬 생성
			MetaKnight_AttackArea* AttackArea = new MetaKnight_AttackArea(this, Vector2(40.f, 30.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			ResourceManager::Find<Sound>(L"MetaKnight_DashSlashSound")->Play(false);
		}
	}

	void MetaKnight::DashAttack()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Idle", true);

			mState = eMetaKnightState::Idle;
		}
	}

	void MetaKnight::Slash()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mSlashCount == 0)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_Idle", true);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_Idle", true);

				mSlashCount = 3;
				mState = eMetaKnightState::Idle;
			}
			else
			{
				if (mSlashCount == 2)
				{
					if (mDir == eDirection::RIGHT)
						mAnimator->PlayAnimation(L"MetaKnight_Right_Slash2", false);
					else
						mAnimator->PlayAnimation(L"MetaKnight_Left_Slash2", false);

					--mSlashCount;
					ResourceManager::Find<Sound>(L"MetaKnight_SlashSound")->Play(false);
				}
				else if(mSlashCount == 1)
				{
					if (mDir == eDirection::RIGHT)
						mAnimator->PlayAnimation(L"MetaKnight_Right_Slash1", false);
					else
						mAnimator->PlayAnimation(L"MetaKnight_Left_Slash1", false);

					--mSlashCount;
					ResourceManager::Find<Sound>(L"MetaKnight_SlashSound")->Play(false);
				}
			}
		}
	}

	void MetaKnight::SlashSkill()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mSlashCount == 0)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_Idle", true);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_Idle", true);

				mSlashCount = 3;
				mState = eMetaKnightState::Idle;
			}
			else
			{
				Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
				Vector2 Dir = PlayerPos - mTransform->GetPosition();

				if (mSlashCount == 2)
				{
					if (mDir == eDirection::RIGHT)
						mAnimator->PlayAnimation(L"MetaKnight_Right_Slash2", false);
					else
						mAnimator->PlayAnimation(L"MetaKnight_Left_Slash2", false);

					--mSlashCount;

					MetaKnight_SlashSkill* SlashSkill = new MetaKnight_SlashSkill(this, Dir);
					object::ActiveSceneAddGameObject(eLayerType::Effect, SlashSkill);

					ResourceManager::Find<Sound>(L"MetaKnight_SlashSound")->Play(false);
				}
				else if (mSlashCount == 1)
				{
					if (mDir == eDirection::RIGHT)
						mAnimator->PlayAnimation(L"MetaKnight_Right_Slash1", false);
					else
						mAnimator->PlayAnimation(L"MetaKnight_Left_Slash1", false);

					--mSlashCount;

					MetaKnight_SlashSkill* SlashSkill = new MetaKnight_SlashSkill(this, Dir);
					object::ActiveSceneAddGameObject(eLayerType::Effect, SlashSkill);

					ResourceManager::Find<Sound>(L"MetaKnight_SlashSound")->Play(false);
				}
			}
		}
	}

	void MetaKnight::Jump()
	{
		Vector2 vel = mRigidBody->GetVelocity();

		if (vel.y >= 0.f)
		{
			int randomNumber = std::rand() % 100;
			if (randomNumber % 2 == 0)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_Turn", false);

				mState = eMetaKnightState::Turn;
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_SpinAttack", true);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_SpinAttack", true);

				mState = eMetaKnightState::SpinAttack;
				mRigidBody->SetFloat(true);

				// 스킬 생성
				MetaKnight_AttackArea* AttackArea = new MetaKnight_AttackArea(this, Vector2(50.f, 50.f));
				object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);
			}

			vel.x = 0.f;
			mRigidBody->SetVelocity(vel);
			mStateChangeDelay = 0.f;
		}
	}

	void MetaKnight::Turn()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			int randomNumber = std::rand() % 100;
			if (randomNumber % 2 == 0)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_Drop", true);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_Drop", true);

				mState = eMetaKnightState::Drop;

				// 제자리점프, 이동점프 범위
				float Velx = 250.f;

				Vector2 vel = mRigidBody->GetVelocity();

				if (mDir == eDirection::RIGHT)
					Velx *= -1;

				// 제자리 Drop, 이동 Drop 랜덤 구현
				int randomDir = std::rand() % 100;
				if (randomDir % 2 == 0)
					vel.x = Velx;				

				mRigidBody->SetVelocity(vel);
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_JumpDownAttack", false);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_JumpDownAttack", false);

				mState = eMetaKnightState::JumpDownAttack;
			}

			mStateChangeDelay = 0.f;
		}
	}

	void MetaKnight::Drop()
	{
		if (mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Idle", true);

			mState = eMetaKnightState::Idle;
			mRigidBody->SetVelocity(Vector2::Zero);
		}
	}

	void MetaKnight::SpinAttack()
	{
		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 1.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_SpinAttackEnd", false);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_SpinAttackEnd", false);

			mState = eMetaKnightState::SpinAttackEnd;
			mRigidBody->SetFloat(false);
			mStateChangeDelay = 0.f;
		}
	}

	void MetaKnight::SpinAttackEnd()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			int randomNumber = std::rand() % 100;
			if (randomNumber % 2 == 0)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_Drop", true);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_Drop", true);

				mState = eMetaKnightState::Drop;

				// 제자리점프, 이동점프 범위
				float Velx = 250.f;

				Vector2 vel = mRigidBody->GetVelocity();

				if (mDir == eDirection::RIGHT)
					Velx *= -1;

				// 제자리 Drop, 이동 Drop 랜덤 구현
				int randomDir = std::rand() % 100;
				if (randomDir % 2 == 0)
					vel.x = Velx;

				mRigidBody->SetVelocity(vel);
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"MetaKnight_Right_JumpDownAttack", false);
				else
					mAnimator->PlayAnimation(L"MetaKnight_Left_JumpDownAttack", false);

				mState = eMetaKnightState::JumpDownAttack;
			}

			mStateChangeDelay = 0.f;
		}
	}

	void MetaKnight::JumpDownAttack()
	{
		if (mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Idle", true);

			mState = eMetaKnightState::Idle;
			AddStarEffect(eDirection::RIGHT);
			AddStarEffect(eDirection::LEFT);
		}
	}

	void MetaKnight::TornadoSkillCharge()
	{
		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 1.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_TornadoSkill", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_TornadoSkill", true);
			
			mState = eMetaKnightState::TornadoSkill;
			mStateChangeDelay = 0.f;

			MetaKnight_TornadoSkill* TornadoSkill = new MetaKnight_TornadoSkill(this);
			object::ActiveSceneAddGameObject(eLayerType::Effect, TornadoSkill);					
		}
	}

	void MetaKnight::TornadoSkill()
	{
		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 1.5f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"MetaKnight_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"MetaKnight_Left_Idle", true);

			mState = eMetaKnightState::Idle;
		}
	}

	void MetaKnight::Dead1()
	{
		if (mAnimator->IsActiveAnimationComplete() && mRigidBody->IsGround())
		{
			mAnimator->PlayAnimation(L"MetaKnight_Dead_2", false);
			mState = eMetaKnightState::Dead2;

			mRigidBody->SetVelocity(Vector2(70.f, -100.f));
			mRigidBody->SetGround(false);
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