#include "sySwordKirby.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syCollider.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "sySound.h"
#include "syPlayer.h"
#include "syCamera.h"
#include "syEnemy.h"
#include "syDefaultKirby.h"
#include "sySceneManager.h"
#include "syInventory.h"
#include "syInput.h"
#include "syLanding_Effect.h"
#include "syObject.h"
#include "syTime.h"
#include "syDash_Effect.h"
#include "syLevelSelectScene.h"
#include "syBreath_Effect.h"
#include "syCollider.h"
#include "syAbilityStar.h"
#include "syBossEnemy.h"
#include "sySwordKirby_AttackArea.h"

namespace sy
{
	SwordKirby::SwordKirby(class Player* owner)
		: Kirby(owner)
		, mState(eSwordKirbyState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::RIGHT)
		, mbOnLeftStop(false)
		, mbOnRightStop(false)
		, mbTopStop(false)
		, mbOnSlope(false)
		, mKeyReleaseTime(0.f)
		, mKeyPressdTime(0.f)
	{
	}

	SwordKirby::~SwordKirby()
	{
	}

	void SwordKirby::Initialize()
	{
		// 텍스쳐 로드
		Texture* SwordKirby_Right = ResourceManager::Load<Texture>(L"SwordKirby_Right_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Right.bmp");
		Texture* SwordKirby_Left = ResourceManager::Load<Texture>(L"SwordKirby_Left_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Left.bmp");

		Texture* SwordKirby_Right_Slash_Tex = ResourceManager::Load<Texture>(L"SwordKirby_Right_Slash_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Right_Slash.bmp");
		Texture* SwordKirby_Left_Slash_Tex = ResourceManager::Load<Texture>(L"SwordKirby_Left_Slash_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Left_Slash.bmp");

		Texture* SwordKirby_Right_Slashing_Tex = ResourceManager::Load<Texture>(L"SwordKirby_Right_Slashing_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Right_Slashing.png");
		Texture* SwordKirby_Left_Slashing_Tex = ResourceManager::Load<Texture>(L"SwordKirby_Left_Slashing_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Left_Slashing.png");

		SwordKirby_Right->SetScale(Vector2(0.35f, 0.35f));
		SwordKirby_Left->SetScale(Vector2(0.35f, 0.35f));

		// Player 에서 만들었던 컴포넌트 멤버변수로 저장
		mAnimator = GetOwner()->GetComponent<Animator>();
		mTransform = GetOwner()->GetComponent<Transform>();

		mRigidBody = GetOwner()->GetComponent<Rigidbody>();
		mRigidBody->SetGround(true);

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(0.f, 0.f);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Choice", Vector2(0.f, 1980.f), Vector2(210.f, 180.f), Vector2(27.f, 0.f), 0.04f, 9, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_Enter", Vector2(0.f, 1980.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_Enter", Vector2(0.f, 1980.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 1.f, 1, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_Idle", Vector2::Zero, Vector2(213.f, 180.f), Vector2(213.f, 0.f), 0.5f, 2, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_Idle", Vector2::Zero, Vector2(213.f, 180.f), Vector2(213.f, 0.f), 0.5f, 2, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_Walk", Vector2(0.f, 540.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 0.07f, 12, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_Walk", Vector2(0.f, 540.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 0.07f, 12, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_Run", Vector2(0.f, 720.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 0.043f, 8, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_Run", Vector2(0.f, 720.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 0.043f, 8, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_Jump", Vector2(0.f, 900.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_Jump", Vector2(0.f, 900.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 1.f, 1, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_Turn", Vector2(212.f, 900.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 0.035f, 7, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_Turn", Vector2(212.f, 900.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 0.035f, 7, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_Drop", Vector2(1696.f, 900.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 0.05f, 2, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_Drop", Vector2(1696.f, 900.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 0.05f, 2, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_Land", Vector2(2120.f, 900.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 0.05f, 2, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_Land", Vector2(2120.f, 900.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 0.05f, 2, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_Down", Vector2(0.f, 180.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_Down", Vector2(0.f, 180.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_FlyStart", Vector2(0.f, 1080.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 0.0667f, 3, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_FlyStart", Vector2(0.f, 1080.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 0.0667f, 3, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_FlyEnd", Vector2(636.f, 1260.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 0.0667f, 2, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_FlyEnd", Vector2(636, 1260.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 0.0667f, 2, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_FlyDown", Vector2(0.f, 1260.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 0.15f, 3, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_FlyDown", Vector2(0.f, 1260.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 0.15f, 3, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_FlyUp", Vector2(636.f, 1080.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 0.07f, 6, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_FlyUp", Vector2(636.f, 1080.f), Vector2(210.f, 180.f), Vector2(210.f, 0.f), 0.07f, 6, Animationoffset);

		mAnimator->CreateAnimation(SwordKirby_Right, L"SwordKirby_Right_DownAttack", Vector2(0.f, 360.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f),0.25f, 2, Animationoffset);
		mAnimator->CreateAnimation(SwordKirby_Left, L"SwordKirby_Left_DownAttack", Vector2(0.f, 360.f), Vector2(212.f, 180.f), Vector2(212.f, 0.f), 0.25f, 2, Animationoffset);


		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"FlySound", L"..\\Resources\\Sound\\Effect\\Fly.wav");
		ResourceManager::Load<Sound>(L"JumpSound", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		ResourceManager::Load<Sound>(L"LandSound", L"..\\Resources\\Sound\\Effect\\Land.wav");
		ResourceManager::Load<Sound>(L"RunSound", L"..\\Resources\\Sound\\Effect\\Run.wav");
		ResourceManager::Load<Sound>(L"ClickSound", L"..\\Resources\\Sound\\Effect\\Click.wav");
		ResourceManager::Load<Sound>(L"SwordKirbyAttackSound", L"..\\Resources\\Sound\\Effect\\SwordKirbyAttack.wav");

		ResourceManager::Find<Sound>(L"JumpSound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"FlySound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"LandSound")->SetVolume(10.f);
		ResourceManager::Find<Sound>(L"RunSound")->SetVolume(100.f);
	}

	void SwordKirby::Update()
	{
		// 방향 설정
		mDir = mTransform->GetDirection();

		// PlayerMode 에 따라서 상태처리 
		if (GetOwner()->GetPlayerMode() == ePlayerMode::LevelMode)
		{
			switch (mState)
			{
			case eSwordKirbyState::Transformations:
				Level_Transformations();
				break;
			case eSwordKirbyState::Choice:
				Choice();
				break;
			case eSwordKirbyState::Enter:
				Level_Enter();
				break;
			case eSwordKirbyState::Idle:
				Level_Idle();
				break;
			case eSwordKirbyState::Run:
				Level_Run();
				break;
			case eSwordKirbyState::Fly_Up:
				Level_FlyUp();
				break;
			case eSwordKirbyState::Drop:
				Level_Drop();
				break;
			default:
				break;
			}
		}
		else if (GetOwner()->GetPlayerMode() == ePlayerMode::PlayMode)
		{
			if (Input::GetKeyDown(eKeyCode::W)
				&& mState != eSwordKirbyState::DownAttack
				&& mState != eSwordKirbyState::JumpAttack
				&& mState != eSwordKirbyState::Slash
				&& mState != eSwordKirbyState::Slashing)
			{
				eDefaultKirbyState state = eDefaultKirbyState::Idle;

				if (mState == eSwordKirbyState::Idle)
					state = eDefaultKirbyState::Idle;
				else if (mState == eSwordKirbyState::Walk)
					state = eDefaultKirbyState::Walk;
				else if (mState == eSwordKirbyState::Run)
					state = eDefaultKirbyState::Run;
				else if (mState == eSwordKirbyState::Down)
					state = eDefaultKirbyState::Down;
				else
					state = eDefaultKirbyState::Drop;

				GetOwner()->ReleaseTransformations(state);

				AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Sword);
				object::ActiveSceneAddGameObject(eLayerType::AbilityItem, abilityStar);

				// 상태변경 방지 리턴
				return;
			}

			// 픽셀충돌 체크
			CheckPixelCollision();

			// 상태처리
			switch (mState)
			{
			case eSwordKirbyState::Transformations:
				Transformations();
				break;
			case eSwordKirbyState::Idle:
				Idle();
				break;
			case eSwordKirbyState::Walk:
				Walk();
				break;
			case eSwordKirbyState::Run:
				Run();
				break;
			case eSwordKirbyState::Jump:
				Jump();
				break;
			case eSwordKirbyState::Turn:
				Turn();
				break;
			case eSwordKirbyState::Drop:
				Drop();
				break;
			case eSwordKirbyState::Land:
				Land();
				break;
			case eSwordKirbyState::Down:
				Down();
				break;
			case eSwordKirbyState::Fly_Start:
				Fly_Start();
				break;
			case eSwordKirbyState::Fly_End:
				Fly_End();
				break;
			case eSwordKirbyState::Fly_Down:
				Fly_Down();
				break;
			case eSwordKirbyState::Fly_Up:
				Fly_Up();
				break;
			case eSwordKirbyState::DownAttack:
				DownAttack();
				break;
			case eSwordKirbyState::JumpAttack:
				JumpAttack();
				break;
			case eSwordKirbyState::Slash:
				Slash();
				break;
			case eSwordKirbyState::Slashing:
				Slashing();
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
		}
	}

	void SwordKirby::Enter()
	{
		if (mDir == eDirection::RIGHT)
			mAnimator->PlayAnimation(L"SwordKirby_Right_Enter", false);
		else
			mAnimator->PlayAnimation(L"SwordKirby_Left_Enter", false);

		mState = eSwordKirbyState::Transformations;
	}

	void SwordKirby::Exit()
	{
	}

	void SwordKirby::OnCollisionEnter(Collider* other)
	{
		// 특정상태에선 AttackArea가 충돌 관리
		if (mState == eSwordKirbyState::DownAttack
			|| mState == eSwordKirbyState::JumpAttack
			|| mState == eSwordKirbyState::Slash
			|| mState == eSwordKirbyState::Slashing)
			return;

		// 플레이어 데미지 상태면 충돌처리 X
		if (GetOwner()->IsDamaged())
			return;

		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (enemy == nullptr)
			return;

		// BossEnemy는 플레이어 충돌 무시
		BossEnemy* bossEnemy = dynamic_cast<BossEnemy*>(other->GetOwner());
		if (bossEnemy != nullptr)
			return;

		// 커비 → 몬스터 방향
		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

		GetOwner()->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	}

	void SwordKirby::OnCollisionStay(Collider* other)
	{
	}

	void SwordKirby::OnCollisionExit(Collider* other)
	{
	}

	bool SwordKirby::IsTransformableCheck()
	{
		if (mState == eSwordKirbyState::DownAttack
			|| mState == eSwordKirbyState::JumpAttack
			|| mState == eSwordKirbyState::Slash
			|| mState == eSwordKirbyState::Slashing)
			return false;

		return true;
	}

	void SwordKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		// 특정 상태에선 충돌 무시
		if (mState == eSwordKirbyState::Transformations
			|| mState == eSwordKirbyState::DownAttack
			|| mState == eSwordKirbyState::JumpAttack
			|| mState == eSwordKirbyState::Slash
			|| mState == eSwordKirbyState::Slashing)
			return;

		mKeyReleaseTime = 0.f;
		mKeyPressdTime = 0.f;

		AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Sword);
		object::ActiveSceneAddGameObject(eLayerType::AbilityItem, abilityStar);

		GetOwner()->Damaged(DamageAmount);
		GetOwner()->SetKirbyType(eAbilityType::Normal);

		DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(GetOwner()->GetActiveKirby());
		defaultKirby->SetKirbyState(eDefaultKirbyState::Damage);

		SceneManager::GetInventory()->GetComponent<Animator>()->PlayAnimation(L"Inventory_Damage_Animation");

		if (HitDir != Vector2::Zero)
		{
			HitDir.Normalize();
			HitDir *= 100.f;
			mRigidBody->SetVelocity(HitDir);
		}

		if (HitDir.x < 0.f)
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Damage", false);
		}
		else
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Damage", false);
		}
	}

	void SwordKirby::CheckPixelCollision()
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

		Collider* col = GetOwner()->GetComponent<Collider>();
		Vector2 ColPos = col->GetPosition();
		Vector2 ColSize = col->GetSize();

		Vector2 LT = Vector2(ColPos.x - (ColSize.x / 2.f), ColPos.y - (ColSize.y / 2.f));
		Vector2 RT = Vector2(ColPos.x + (ColSize.x / 2.f), ColPos.y - (ColSize.y / 2.f));
		Vector2 MT = Vector2(ColPos.x, ColPos.y - (ColSize.y / 2.f));
		Vector2 LB = Vector2(ColPos.x - (ColSize.x / 2.f), ColPos.y + (ColSize.y / 2.f));
		Vector2 RB = Vector2(ColPos.x + (ColSize.x / 2.f), ColPos.y + (ColSize.y / 2.f));
		Vector2 MB = Vector2(ColPos.x, ColPos.y + (ColSize.y / 2.f));

		LT += offset;
		RT += offset;
		MT += offset;
		LB += offset;
		RB += offset;
		MB += offset;


		COLORREF LTColor = PixelTex->GetTexturePixel((int)LT.x, (int)LT.y);
		COLORREF RTColor = PixelTex->GetTexturePixel((int)RT.x, (int)RT.y);
		COLORREF MTColor = PixelTex->GetTexturePixel((int)MT.x, (int)MT.y);
		COLORREF LBColor = PixelTex->GetTexturePixel((int)LB.x, (int)LB.y);
		COLORREF RBColor = PixelTex->GetTexturePixel((int)RB.x, (int)RB.y);
		COLORREF MBColor = PixelTex->GetTexturePixel((int)MB.x, (int)MB.y);

		// 상단 처리
		COLORREF MTColorOffsetY = PixelTex->GetTexturePixel((int)MT.x, int(MT.y + 1));

		Vector2 pos = mTransform->GetPosition();

		if (MTColor == RGB(0, 255, 0))
		{
			pos.y += 1.f;
			mbTopStop = true;
		}
		else if (MTColorOffsetY == RGB(0, 255, 0))
		{
			mbTopStop = true;
		}
		else
		{
			if (LTColor == RGB(0, 255, 0))
			{
				pos.x += 1.f;
			}
			else if (RTColor == RGB(0, 255, 0))
			{
				pos.x -= 1.f;
			}

			mbTopStop = false;
		}

		mTransform->SetPosition(pos);



		// 바닥 처리
		if (LBColor == RGB(0, 0, 255) || RBColor == RGB(0, 0, 255) || MBColor == RGB(0, 0, 255)
			|| MBColor == RGB(255, 0, 0))
		{
			// 특정상태일때는 바닥 무시
			if (!(mState == eSwordKirbyState::Jump
				|| mState == eSwordKirbyState::Fly_Up))
			{
				// 이동
				Vector2 pos = mTransform->GetPosition();
				pos.y -= 1.f;
				mTransform->SetPosition(pos);
				mRigidBody->SetGround(true);

				// Blue 만 인식하도록 설정
				if (LBColor == RGB(0, 0, 255) || RBColor == RGB(0, 0, 255))
				{
					Landing_Effect* landingEffect = new Landing_Effect(GetOwner());
					object::ActiveSceneAddGameObject(eLayerType::Effect, landingEffect);
				}
			}
		}

		COLORREF LBColorOffsetY = PixelTex->GetTexturePixel((int)LB.x, int(LB.y + 1));
		COLORREF RBColorOffsetY = PixelTex->GetTexturePixel((int)RB.x, int(RB.y + 1));
		COLORREF MBColorOffsetY = PixelTex->GetTexturePixel((int)MB.x, int(MB.y + 1));

		// 바닥 ~ 바닥 + 1픽셀 범위가 아닐경우 Ground false 처리
		if (!(LBColor == RGB(0, 0, 255) || LBColorOffsetY == RGB(0, 0, 255)
			|| RBColor == RGB(0, 0, 255) || RBColorOffsetY == RGB(0, 0, 255)
			|| MBColor == RGB(255, 0, 0) || MBColorOffsetY == RGB(255, 0, 0)))
		{
			mRigidBody->SetGround(false);
		}


		// OnSlope Check 
		// 아래로 20픽셀까지 체크
		mbOnSlope = false;

		for (size_t i = 0; i < 20; i++)
		{
			COLORREF tempColor = PixelTex->GetTexturePixel((int)LB.x, int(LB.y + i));

			if (tempColor == RGB(255, 0, 0))
			{
				mbOnSlope = true;
				break;
			}
		}


		// Right Stop Check
		COLORREF RBColorOffsetX = PixelTex->GetTexturePixel(int(RB.x + 1), (int)RB.y);

		if (RBColor == RGB(0, 255, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 1.f;
			mTransform->SetPosition(pos);
			mbOnRightStop = true;
		}
		else if (RBColorOffsetX == RGB(0, 255, 0))
		{
			// 한픽셀 Offset 처리
			mbOnRightStop = true;
		}
		else
		{
			mbOnRightStop = false;
		}

		// Left Stop Check
		COLORREF LBColorOffsetX = PixelTex->GetTexturePixel(int(LB.x - 1), (int)LB.y);

		if (LBColor == RGB(0, 255, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x += 1.f;
			mTransform->SetPosition(pos);
			mbOnLeftStop = true;
		}
		else if (LBColorOffsetX == RGB(0, 255, 0))
		{
			// 한픽셀 Offset 처리
			mbOnLeftStop = true;
		}
		else
		{
			mbOnLeftStop = false;
		}

		// 반대방향키눌렀을때 Stop 해제
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::RIGHT))
		{
			mbOnLeftStop = false;
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			mbOnRightStop = false;
		}
	}

	void SwordKirby::Level_Transformations()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Idle", true);

			mState = eSwordKirbyState::Idle;
		}
	}

	void SwordKirby::Choice()
	{
		// 애니메이션
		if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::RIGHT)) && !GetOwner()->GetLevelEnter())
		{
			mAnimator->PlayAnimation(L"SwordKirby_Choice", false);
		}

		// 애니메이션이 끝나면 Idle 상태로 변경
		if (mAnimator->IsActiveAnimationComplete())
		{
			// 씬에 첫진입이라면 Enter애니메이션 재생
			if (GetOwner()->GetLevelEnter())
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"SwordKirby_Right_Enter", false);
				else
					mAnimator->PlayAnimation(L"SwordKirby_Left_Enter", false);

				mState = eSwordKirbyState::Enter;
				GetOwner()->SetLevelEnter(false);
			}
			else
			{
				mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);
				mState = eSwordKirbyState::Idle;
			}
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Enter", false);

			mState = eSwordKirbyState::Enter;
		}
	}

	void SwordKirby::Level_Enter()
	{
		// 애니메이션이 끝나면 Idle 상태로 변경
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);

			mState = eSwordKirbyState::Idle;
		}
	}

	void SwordKirby::Level_Idle()
	{
		if (Input::GetKeyDown(eKeyCode::UP)
			|| Input::GetKeyDown(eKeyCode::DOWN)
			|| Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			mAnimator->PlayAnimation(L"SwordKirby_Choice", false);
			mState = eSwordKirbyState::Choice;
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Enter", false);

			mState = eSwordKirbyState::Enter;
		}
	}

	void SwordKirby::Level_Run()
	{
		// BackGround Animator Set
		LevelSelectScene* levelSelectScene = dynamic_cast<LevelSelectScene*>(SceneManager::GetScene(L"LevelSelectScene"));
		eLevelState CurLevelState = levelSelectScene->GetCurLevelState();

		Vector2 pos = mTransform->GetPosition();

		if (CurLevelState == eLevelState::Level1 || CurLevelState == eLevelState::Level5)
		{
			if (mDir == eDirection::RIGHT)
				pos.x += 120.f * Time::DeltaTime();
			else
				pos.x -= 120.f * Time::DeltaTime();
		}
		else if (CurLevelState == eLevelState::Level3)
		{
			if (mDir == eDirection::RIGHT)
			{
				Vector2 vec = Vector2(766.f, 202.f) - Vector2(517.f, 77.f);
				vec.Normalize();
				pos += (vec * 120.f) * Time::DeltaTime();
			}
			else
			{
				Vector2 vec = Vector2(517.f, 77.f) - Vector2(766.f, 202.f);
				vec.Normalize();
				pos += (vec * 120.f) * Time::DeltaTime();
			}
		}
		else if (CurLevelState == eLevelState::Level4 || CurLevelState == eLevelState::Level7)
		{
			if (mDir == eDirection::RIGHT)
			{
				Vector2 vec = Vector2(1032.f, 83.f) - Vector2(792.f, 202.f);
				vec.Normalize();
				pos += (vec * 120.f) * Time::DeltaTime();
			}
			else
			{
				Vector2 vec = Vector2(792.f, 202.f) - Vector2(1032.f, 83.f);
				vec.Normalize();
				pos += (vec * 120.f) * Time::DeltaTime();
			}
		}
		else if (CurLevelState == eLevelState::Level8)
		{
			if (mDir == eDirection::RIGHT)
			{
				Vector2 vec = Vector2(766.f, 202.f) - Vector2(517.f, 77.f);
				vec.Normalize();
				pos += (vec * 120.f) * Time::DeltaTime();
			}
			else
			{
				Vector2 vec = Vector2(517.f, 77.f) - Vector2(766.f, 202.f);
				vec.Normalize();
				pos += (vec * 120.f) * Time::DeltaTime();
			}
		}

		mTransform->SetPosition(pos);

		static float time = 0.f;
		time += Time::DeltaTime();
		if (time > 0.3f)
		{
			Dash_Effect* DashEffect = new Dash_Effect(GetOwner());
			DashEffect->GetComponent<Animator>()->SetAffectedCamera(false);
			object::ActiveSceneAddGameObject(eLayerType::Effect, DashEffect);
			time = 0.f;
		}
	}

	void SwordKirby::Level_FlyUp()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y -= 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void SwordKirby::Level_Drop()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y += 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void SwordKirby::Transformations()
	{
		mRigidBody->SetGround(true);

		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Drop", true);

			mState = eSwordKirbyState::Drop;
		}
	}

	void SwordKirby::Idle()
	{
		// 애니메이션 

		// 땅에 닿은 상태가 아니라면 Drop으로 변경 비탈길에서는 예외처리해줘야함
		if (!mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Drop", true);

			mState = eSwordKirbyState::Drop;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"SwordKirby_Right_Walk", true);
				mState = eSwordKirbyState::Walk;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (!mbOnLeftStop)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"SwordKirby_Left_Walk", true);
				mState = eSwordKirbyState::Walk;
			}
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_Walk", true);
			mState = eSwordKirbyState::Walk;
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_Walk", true);
			mState = eSwordKirbyState::Walk;
		}

		// Run
		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"SwordKirby_Right_Run", true);
				mState = eSwordKirbyState::Run;

				Dash_Effect* DashEffect = new Dash_Effect(GetOwner());
				object::ActiveSceneAddGameObject(eLayerType::Effect, DashEffect);

				// 오디오 재생
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);
			}
		}

		if (Input::IsDoubleKeyPressed(eKeyCode::LEFT))
		{
			if (!mbOnLeftStop)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"SwordKirby_Left_Run", true);
				mState = eSwordKirbyState::Run;

				Dash_Effect* DashEffect = new Dash_Effect(GetOwner());
				object::ActiveSceneAddGameObject(eLayerType::Effect, DashEffect);

				// 오디오 재생
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);
			}
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Jump", false);

			mState = eSwordKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// 오디오 재생
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Down", false);

			mState = eSwordKirbyState::Down;
		}

		// Slash
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Slash", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Slash", false);

			mState = eSwordKirbyState::Slash;

			// 스킬 생성
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// 오디오 재생		
			ResourceManager::Find<Sound>(L"SwordKirbyAttackSound")->Play(false);
		}
	}

	void SwordKirby::Walk()
	{
		// Stop 상태라면 Idle 로 상태변경
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Idle", true);

			mState = eSwordKirbyState::Idle;
			return;
		}

		// Stop 상태가 아닌경우에만 이동
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// 좌우 이동
			Vector2 pos = mTransform->GetPosition();

			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 80.f * Time::DeltaTime();
				else
					pos.x -= 80.f * Time::DeltaTime();
			}

			mTransform->SetPosition(pos);
		}

		// 애니메이션

		// 땅에 닿은 상태가 아니면서 경사로가 아니라면 Drop으로 변경
		if (!mRigidBody->IsGround() && mbOnSlope == false)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Drop", true);

			mState = eSwordKirbyState::Drop;
		}

		// Idle
		// 좌우 어느 키입력도 없으면 Idle 상태로 변경
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Idle", true);

			mState = eSwordKirbyState::Idle;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_Walk", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_Walk", true);
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_Walk", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_Walk", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Jump", false);

			mState = eSwordKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// 오디오 재생
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Down", false);

			mState = eSwordKirbyState::Down;
		}

		// Slash
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Slash", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Slash", false);

			mState = eSwordKirbyState::Slash;

			// 스킬 생성
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// 오디오 재생		
			ResourceManager::Find<Sound>(L"SwordKirbyAttackSound")->Play(false);
		}
	}

	void SwordKirby::Run()
	{
		// Stop 상태라면 Idle 로 상태변경
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Idle", true);

			mState = eSwordKirbyState::Idle;

			return;
		}

		// Stop 상태가 아닌경우에만 이동
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// 좌우 이동
			Vector2 pos = mTransform->GetPosition();

			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 120.f * Time::DeltaTime();
				else
					pos.x -= 120.f * Time::DeltaTime();
			}

			mTransform->SetPosition(pos);
		}

		// 애니메이션

		// 땅에 닿은 상태가 아니면서 경사로가 아니라면 Drop으로 변경
		if (!mRigidBody->IsGround() && mbOnSlope == false)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Drop", true);

			mState = eSwordKirbyState::Drop;
		}

		// Idle
		// 좌우 어느 키입력도 없으면 Idle 상태로 변경
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Idle", true);

			mState = eSwordKirbyState::Idle;
		}

		// Run
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_Run", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_Run", true);
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_Run", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_Run", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Jump", false);

			mState = eSwordKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// 오디오 재생
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Down", false);

			mState = eSwordKirbyState::Down;
		}

		// Slash
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Slash", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Slash", false);

			mState = eSwordKirbyState::Slash;

			// 스킬 생성
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// 오디오 재생		
			ResourceManager::Find<Sound>(L"SwordKirbyAttackSound")->Play(false);
		}
	}

	void SwordKirby::Jump()
	{
		// 상하 이동
		if (Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			mKeyPressdTime += Time::DeltaTime();

			// 일정 누른 시간에만 상승
			if (mKeyPressdTime < 0.2f)
			{
				mRigidBody->AddForce(Vector2(0.f, -400.f));
			}

			// 키를 누른 시간이 일정시간이상 지나면 상태변경
			if (mKeyPressdTime > 0.4f)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"SwordKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"SwordKirby_Left_Turn", false);

				mState = eSwordKirbyState::Turn;

				mKeyPressdTime = 0.f;
				mKeyReleaseTime = 0.f;
				mRigidBody->SetVelocity(Vector2::Zero);
			}
		}

		if (!Input::GetKeyPressed(eKeyCode::A) && !Input::GetKeyPressed(eKeyCode::D))
		{
			mKeyReleaseTime += Time::DeltaTime();

			// 키를 뗀시간이 일정시간이상 지나면 상태변경
			if (mKeyReleaseTime > 0.125f)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"SwordKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"SwordKirby_Left_Turn", false);

				mState = eSwordKirbyState::Turn;

				mKeyPressdTime = 0.f;
				mKeyReleaseTime = 0.f;
				mRigidBody->SetVelocity(Vector2::Zero);
			}
		}

		// Stop 상태가 아닌경우에만 이동
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// 좌우 이동
			Vector2 pos = mTransform->GetPosition();

			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 80.f * Time::DeltaTime();
				else
					pos.x -= 80.f * Time::DeltaTime();
			}

			mTransform->SetPosition(pos);
		}


		// 애니메이션

		// Jump
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_Jump", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_Jump", true);
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_Jump", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_Jump", true);
		}

		// JumpAttack
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_JumpAttack", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_JumpAttack", false);

			mState = eSwordKirbyState::JumpAttack;

			// 스킬 생성
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// 오디오 재생		
			ResourceManager::Find<Sound>(L"SwordKirbyAttackSound")->Play(false);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_FlyStart", false);

			mState = eSwordKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
			mKeyPressdTime = 0.f;
			mKeyReleaseTime = 0.f;

			// 오디오 재생
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void SwordKirby::Turn()
	{
		// Stop 상태가 아닌경우에만 이동
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// 좌우 이동
			Vector2 pos = mTransform->GetPosition();

			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 80.f * Time::DeltaTime();
				else
					pos.x -= 80.f * Time::DeltaTime();
			}

			mTransform->SetPosition(pos);
		}

		// 애니메이션	
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
		}

		static float TurnTime = 0.f;
		TurnTime += Time::DeltaTime();

		// 애니메이션이 끝나면 상태 변경
		if (mAnimator->IsActiveAnimationComplete() || TurnTime > 0.3f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Drop", true);

			TurnTime = 0.f;
			mState = eSwordKirbyState::Drop;
		}

		// JumpAttack
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_JumpAttack", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_JumpAttack", false);

			mState = eSwordKirbyState::JumpAttack;

			// 스킬 생성
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// 오디오 재생		
			ResourceManager::Find<Sound>(L"SwordKirbyAttackSound")->Play(false);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_FlyStart", false);

			TurnTime = 0.f;
			mState = eSwordKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));

			// 오디오 재생
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void SwordKirby::Drop()
	{
		// Stop 상태가 아닌경우에만 이동
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// 좌우 이동
			Vector2 pos = mTransform->GetPosition();

			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 80.f * Time::DeltaTime();
				else
					pos.x -= 80.f * Time::DeltaTime();
			}

			mTransform->SetPosition(pos);
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_Drop", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_Drop", true);
		}

		// 방향전환 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && mDir == eDirection::LEFT)
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_Drop", true);
		}

		if (Input::GetKeyPressed(eKeyCode::LEFT) && mDir == eDirection::RIGHT)
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_Drop", true);
		}

		// JumpAttack
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_JumpAttack", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_JumpAttack", false);

			mState = eSwordKirbyState::JumpAttack;

			// 스킬 생성
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// 오디오 재생		
			ResourceManager::Find<Sound>(L"SwordKirbyAttackSound")->Play(false);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_FlyStart", false);

			mState = eSwordKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
		}

		if (mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Land", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Land", false);

			mState = eSwordKirbyState::Land;
			ResourceManager::Find<Sound>(L"LandSound")->Play(false);
		}
	}

	void SwordKirby::Land()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Idle", true);

			mState = eSwordKirbyState::Idle;
		}
	}

	void SwordKirby::Down()
	{
		// 애니메이션

		// 반대방향키가 눌렸을때 방향 전환
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_Down", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_Down", true);
		}

		// DownAttack
		if (Input::GetKeyPressed(eKeyCode::DOWN) && Input::GetKeyDown(eKeyCode::S))
		{
			Vector2 vel = mRigidBody->GetVelocity();

			if (mDir == eDirection::RIGHT)
			{
				mAnimator->PlayAnimation(L"SwordKirby_Right_DownAttack", false);
				vel.x += 100.f;
			}
			else
			{
				mAnimator->PlayAnimation(L"SwordKirby_Left_DownAttack", false);
				vel.x -= 100.f;
			}

			mState = eSwordKirbyState::DownAttack;
			mRigidBody->SetVelocity(vel);

			// 스킬 생성
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(50.f, 15.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// 오디오 재생		
			ResourceManager::Find<Sound>(L"SwordKirbyAttackSound")->Play(false);
		}

		// 키입력이없을땐 Idle 로 변경
		if (!Input::GetKeyPressed(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Idle", true);

			mState = eSwordKirbyState::Idle;
		}
	}

	void SwordKirby::Fly_Start()
	{
		// Stop 상태가 아닌경우에만 이동
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// 좌우 이동
			Vector2 pos = mTransform->GetPosition();

			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 80.f * Time::DeltaTime();
				else
					pos.x -= 80.f * Time::DeltaTime();
			}

			mTransform->SetPosition(pos);
		}

		// 방향전환
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
		}

		// Fly End
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_FlyEnd", false);

			mState = eSwordKirbyState::Fly_End;

			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);
		}

		// 애니메이션이 끝나면 Fly Down 상태로 변경
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_FlyDown", true);

			mState = eSwordKirbyState::Fly_Down;
		}
	}

	void SwordKirby::Fly_End()
	{
		// Stop 상태가 아닌경우에만 이동
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// 좌우 이동
			Vector2 pos = mTransform->GetPosition();

			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 80.f * Time::DeltaTime();
				else
					pos.x -= 80.f * Time::DeltaTime();
			}

			mTransform->SetPosition(pos);
		}


		// 방향 전환
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
		}

		// 애니메이션이 끝나면 Drop 상태로 변경
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Drop", true);

			mState = eSwordKirbyState::Drop;
		}
	}

	void SwordKirby::Fly_Down()
	{
		// Fly상태에선 속도제한
		mRigidBody->SetLimitVelocity(Vector2(50.f, 50.f));

		// Stop 상태가 아닌경우에만 이동
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// 좌우 이동
			Vector2 pos = mTransform->GetPosition();

			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 80.f * Time::DeltaTime();
				else
					pos.x -= 80.f * Time::DeltaTime();
			}

			mTransform->SetPosition(pos);
		}

		// 방향 전환
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_FlyDown", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_FlyDown", true);
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_FlyDown", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_FlyDown", true);
		}


		// Fly Up
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_FlyUp", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_FlyUp", true);

			mState = eSwordKirbyState::Fly_Up;
			mRigidBody->SetVelocity(Vector2(0.f, -300.f));
			mRigidBody->SetGround(false);
			mRigidBody->SetLimitVelocity(Vector2(300.f, 300.f));

			// 오디오 재생
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}

		// Fly End
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_FlyEnd", false);

			mState = eSwordKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			mRigidBody->SetLimitVelocity(Vector2(300.f, 300.f));

			// 오디오 재생
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void SwordKirby::Fly_Up()
	{
		// Stop 상태가 아닌경우에만 이동
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// 좌우 이동
			Vector2 pos = mTransform->GetPosition();

			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 80.f * Time::DeltaTime();
				else
					pos.x -= 80.f * Time::DeltaTime();
			}

			mTransform->SetPosition(pos);
		}


		// 방향 전환
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_FlyUp", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_FlyUp", true);
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SwordKirby_Right_FlyUp", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SwordKirby_Left_FlyUp", true);
		}

		// 누르고있을때 상승
		if (Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			// 상단에 충돌한 상태면 속도를 0으로 설정하고 고정위치 셋팅
			if (mbTopStop)
			{
				mRigidBody->SetVelocity(Vector2::Zero);
				// 좌우 이동
				Vector2 pos = mTransform->GetPosition();
				pos.y -= 1.f;
				mTransform->SetPosition(pos);
			}
			else
			{
				mRigidBody->SetVelocity(Vector2(0.f, -80.f));
			}
		}

		// 키를 누르고있지 않을때 Fly Down
		if (!Input::GetKeyPressed(eKeyCode::A) && !Input::GetKeyPressed(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_FlyDown", true);

			mState = eSwordKirbyState::Fly_Down;
		}

		// Fly End
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_FlyEnd", false);

			mState = eSwordKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			// 오디오 재생
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void SwordKirby::DownAttack()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Drop", true);

			mState = eSwordKirbyState::Drop;

			mRigidBody->SetVelocity(Vector2(0.f, mRigidBody->GetVelocity().y));
		}
	}

	void SwordKirby::JumpAttack()
	{
	}

	void SwordKirby::Slash()
	{
	}

	void SwordKirby::Slashing()
	{
	}
}