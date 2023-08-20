#include "syNinjaKirby.h"
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
#include "syNinjaKirby_Fire.h"
#include "syNinjaKirby_Shuriken.h"
#include "syNinjaKirby_ChargeEffect.h"
#include "syNinjaKirby_Fire.h"
#include "syBossEnemy.h"

namespace sy
{
	NinjaKirby::NinjaKirby(class Player* owner)
		: Kirby(owner)
		, mState(eNinjaKirbyState::Idle)
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
		, mChargeTime(0.f)
	{
	}

	NinjaKirby::~NinjaKirby()
	{
	}

	void NinjaKirby::Initialize()
	{
		// 텍스쳐 로드
		Texture* NinjaKirby_Right = ResourceManager::Load<Texture>(L"NinjaKirby_Right_Tex", L"..\\Resources\\Kirby\\NinjaKirby\\NinjaKirby_Right.bmp");
		Texture* NinjaKirby_Left = ResourceManager::Load<Texture>(L"NinjaKirby_Left_Tex", L"..\\Resources\\Kirby\\NinjaKirby\\NinjaKirby_Left.bmp");

		// Player 에서 만들었던 컴포넌트 멤버변수로 저장
		mAnimator = GetOwner()->GetComponent<Animator>();
		mTransform = GetOwner()->GetComponent<Transform>();

		mRigidBody = GetOwner()->GetComponent<Rigidbody>();
		mRigidBody->SetGround(true);

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(0.f, -3.f);
		std::vector<Vector2> NinjaKirby_Charge_offset = { Vector2(0.f, -7.f), Vector2(0.f, -5.f), Vector2(0.f, -7.f), Vector2(0.f, -5.f) };

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Choice", Vector2(314.f, 470.f), Vector2(24.f, 48.f), Vector2(24.f, 0.f), 0.03f, 12, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Enter", Vector2(316.f, 211.f), Vector2(22.f, 27.f), Vector2(22.f, 0.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Enter", Vector2(386.f, 211.f), Vector2(22.f, 27.f), Vector2(-22.f, 0.f), 1.f, 1, Animationoffset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Idle", Vector2(8.f, 6.f), Vector2(25.f, 25.f), Vector2(25.f, 0.f), 0.13f, 4, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Idle", Vector2(691.f, 6.f), Vector2(25.f, 25.f), Vector2(-25.f, 0.f), 0.13f, 4, Animationoffset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Walk", Vector2(0.f, 41.f), Vector2(33.f, 27.f), Vector2(33.f, 0.f), 0.0636f, 11, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Walk", Vector2(691.f, 41.f), Vector2(33.f, 27.f), Vector2(-33.f, 0.f), 0.0636f, 11, Animationoffset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Run", Vector2(0.f, 74.f), Vector2(42.f, 26.f), Vector2(42.f, 0.f), 0.043f, 8, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Run", Vector2(682.f, 74.f), Vector2(42.f, 26.f), Vector2(-42.f, 0.f), 0.043f, 8, Animationoffset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Jump", Vector2(7.f, 144.f), Vector2(25.f, 26.f), Vector2(25.f, 0.f), 0.13f, 2, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Jump", Vector2(692.f, 144.f), Vector2(25.f, 26.f), Vector2(-25.f, 0.f), 0.13f, 2, Animationoffset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Turn", Vector2(369.f, 42.f), Vector2(25.f, 27.f), Vector2(25.f, 0.f), 0.035f, 6, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Turn", Vector2(330.f, 42.f), Vector2(25.f, 27.f), Vector2(-25.f, 0.f), 0.035f, 6, Animationoffset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Drop", Vector2(173.f, 134.f), Vector2(27.f, 38.f), Vector2(27.f, 0.f), 0.05f, 2, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Drop", Vector2(524.f, 134.f), Vector2(27.f, 38.f), Vector2(-27.f, 0.f), 0.05f, 2, Animationoffset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Down", Vector2(204.f, 12.f), Vector2(25.f, 19.f), Vector2(25.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Down", Vector2(495.f, 12.f), Vector2(25.f, 19.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_FlyStart", Vector2(511.f, 180.f), Vector2(32.f, 25.f), Vector2(32.f, 0.f), 0.0667f, 3, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_FlyStart", Vector2(181.f, 180.f), Vector2(32.f, 25.f), Vector2(-32.f, 0.f), 0.0667f, 3, Animationoffset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_FlyEnd", Vector2(575.f, 180.f), Vector2(32.f, 25.f), Vector2(-32.f, 0.f), 0.0667f, 3, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_FlyEnd", Vector2(117.f, 180.f), Vector2(32.f, 25.f), Vector2(32.f, 0.f), 0.0667f, 3, Animationoffset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_FlyUp", Vector2(0.f, 209.f), Vector2(29.f, 31.f), Vector2(29.f, 0.f), 0.1f, 4, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_FlyUp", Vector2(695.f, 209.f), Vector2(29.f, 31.f), Vector2(-29.f, 0.f), 0.1f, 4, Animationoffset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_FlyDown", Vector2(634.f, 173.f), Vector2(27.f, 32.f), Vector2(27.f, 0.f), 0.15f, 2, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_FlyDown", Vector2(63.f, 173.f), Vector2(27.f, 32.f), Vector2(-27.f, 0.f), 0.15f, 2, Animationoffset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_ThrowShuriken", Vector2(0.f, 322.f), Vector2(49.f, 28.f), Vector2(49.f, 0.f), 0.05f, 7, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_ThrowShuriken", Vector2(675.f, 322.f), Vector2(49.f, 28.f), Vector2(-49.f, 0.f), 0.05f, 7, Animationoffset);

		mAnimator->CreateAnimation_Offset(NinjaKirby_Right, L"NinjaKirby_Right_Charge", Vector2(324.f, 406.f), Vector2(26.f, 36.f), Vector2(26.f, 0.f), 0.05f, 4, NinjaKirby_Charge_offset);
		mAnimator->CreateAnimation_Offset(NinjaKirby_Left, L"NinjaKirby_Left_Charge", Vector2(374.f, 406.f), Vector2(26.f, 36.f), Vector2(-26.f, 0.f), 0.05f, 4, NinjaKirby_Charge_offset);

		mAnimator->CreateAnimation(NinjaKirby_Right, L"NinjaKirby_Right_Fire", Vector2(464.f, 408.f), Vector2(29.f, 34.f), Vector2(29.f, 0.f), 0.05f, 8, Animationoffset);
		mAnimator->CreateAnimation(NinjaKirby_Left, L"NinjaKirby_Left_Fire", Vector2(231.f, 408.f), Vector2(29.f, 34.f), Vector2(-29.f, 0.f), 0.05f, 8, Animationoffset);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"NinjaKirby_Right_Idle", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"FlySound", L"..\\Resources\\Sound\\Effect\\Fly.wav");
		ResourceManager::Load<Sound>(L"JumpSound", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		ResourceManager::Load<Sound>(L"LandSound", L"..\\Resources\\Sound\\Effect\\Land.wav");
		ResourceManager::Load<Sound>(L"RunSound", L"..\\Resources\\Sound\\Effect\\Run.wav");
		ResourceManager::Load<Sound>(L"ClickSound", L"..\\Resources\\Sound\\Effect\\Click.wav");
		ResourceManager::Load<Sound>(L"NinjaChargeSound", L"..\\Resources\\Sound\\Effect\\NinjaCharge.wav");

		ResourceManager::Find<Sound>(L"JumpSound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"FlySound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"LandSound")->SetVolume(10.f);
		ResourceManager::Find<Sound>(L"RunSound")->SetVolume(100.f);
	}

	void NinjaKirby::Update()
	{
		// 방향 설정
		mDir = mTransform->GetDirection();

		// PlayerMode 에 따라서 상태처리 
		if (GetOwner()->GetPlayerMode() == ePlayerMode::LevelMode)
		{
			switch (mState)
			{
			case eNinjaKirbyState::Transformations:
				Level_Transformations();
				break;
			case eNinjaKirbyState::Choice:
				Choice();
				break;
			case eNinjaKirbyState::Enter:
				Level_Enter();
				break;
			case eNinjaKirbyState::Idle:
				Level_Idle();
				break;
			case eNinjaKirbyState::Run:
				Level_Run();
				break;
			case eNinjaKirbyState::Fly_Up:
				Level_FlyUp();
				break;
			case eNinjaKirbyState::Drop:
				Level_Drop();
				break;
			default:
				break;
			}
		}
		else if (GetOwner()->GetPlayerMode() == ePlayerMode::PlayMode)
		{
			if (Input::GetKeyDown(eKeyCode::W)
				&& mState != eNinjaKirbyState::ThrowShuriken && mState != eNinjaKirbyState::Charge && mState != eNinjaKirbyState::Fire)
			{
				eDefaultKirbyState state = eDefaultKirbyState::Idle;

				if (mState == eNinjaKirbyState::Idle)
					state = eDefaultKirbyState::Idle;
				else if (mState == eNinjaKirbyState::Walk)
					state = eDefaultKirbyState::Walk;
				else if (mState == eNinjaKirbyState::Run)
					state = eDefaultKirbyState::Run;
				else if (mState == eNinjaKirbyState::Down)
					state = eDefaultKirbyState::Down;
				else
					state = eDefaultKirbyState::Drop;

				GetOwner()->ReleaseTransformations(state);

				AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Ninja);
				object::ActiveSceneAddGameObject(eLayerType::AbilityItem, abilityStar);

				// 상태변경 방지 리턴
				return;
			}

			// 픽셀충돌 체크
			CheckPixelCollision();

			// 상태처리
			switch (mState)
			{
			case eNinjaKirbyState::Transformations:
				Transformations();
				break;
			case eNinjaKirbyState::Idle:
				Idle();
				break;
			case eNinjaKirbyState::Walk:
				Walk();
				break;
			case eNinjaKirbyState::Run:
				Run();
				break;
			case eNinjaKirbyState::Jump:
				Jump();
				break;
			case eNinjaKirbyState::Turn:
				Turn();
				break;
			case eNinjaKirbyState::Drop:
				Drop();
				break;
			case eNinjaKirbyState::Down:
				Down();
				break;
			case eNinjaKirbyState::Fly_Start:
				Fly_Start();
				break;
			case eNinjaKirbyState::Fly_End:
				Fly_End();
				break;
			case eNinjaKirbyState::Fly_Down:
				Fly_Down();
				break;
			case eNinjaKirbyState::Fly_Up:
				Fly_Up();
				break;
			case eNinjaKirbyState::ThrowShuriken:
				ThrowShuriken();
				break;
			case eNinjaKirbyState::Charge:
				Charge();
				break;
			case eNinjaKirbyState::Fire:
				Fire();
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

	void NinjaKirby::Enter()
	{
		if (mDir == eDirection::RIGHT)
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Enter", false);
		else
			mAnimator->PlayAnimation(L"NinjaKirby_Left_Enter", false);

		mState = eNinjaKirbyState::Transformations;
	}

	void NinjaKirby::Exit()
	{
	}

	void NinjaKirby::OnCollisionEnter(Collider* other)
	{
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

	void NinjaKirby::OnCollisionStay(Collider* other)
	{
	}

	void NinjaKirby::OnCollisionExit(Collider* other)
	{
	}

	bool NinjaKirby::IsTransformableCheck()
	{
		if (mState == eNinjaKirbyState::ThrowShuriken || mState == eNinjaKirbyState::Charge || mState == eNinjaKirbyState::Fire)
			return false;

		return true;
	}

	void NinjaKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		// 특정 상태에선 충돌 무시
		if (mState == eNinjaKirbyState::Fire || mState == eNinjaKirbyState::Transformations)
			return;

		mKeyPressdTime = 0.f;
		mKeyReleaseTime = 0.f;

		AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Ninja);
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

	void NinjaKirby::CheckPixelCollision()
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
			if (!(mState == eNinjaKirbyState::Jump
				|| mState == eNinjaKirbyState::Fly_Up))
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

	void NinjaKirby::Level_Transformations()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Idle", true);

			mState = eNinjaKirbyState::Idle;
		}
	}

	void NinjaKirby::Choice()
	{
		// 애니메이션
		if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::RIGHT)) && !GetOwner()->GetLevelEnter())
		{
			mAnimator->PlayAnimation(L"NinjaKirby_Choice", false);
		}

		// 애니메이션이 끝나면 Idle 상태로 변경
		if (mAnimator->IsActiveAnimationComplete())
		{
			// 씬에 첫진입이라면 Enter애니메이션 재생
			if (GetOwner()->GetLevelEnter())
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"NinjaKirby_Right_Enter", false);
				else
					mAnimator->PlayAnimation(L"NinjaKirby_Left_Enter", false);

				mState = eNinjaKirbyState::Enter;
				GetOwner()->SetLevelEnter(false);
			}
			else
			{
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Idle", true);
				mState = eNinjaKirbyState::Idle;
			}
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Enter", false);

			mState = eNinjaKirbyState::Enter;
		}
	}

	void NinjaKirby::Level_Enter()
	{
		// 애니메이션이 끝나면 Idle 상태로 변경
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Idle", true);

			mState = eNinjaKirbyState::Idle;
		}
	}

	void NinjaKirby::Level_Idle()
	{
		if (Input::GetKeyDown(eKeyCode::UP)
			|| Input::GetKeyDown(eKeyCode::DOWN)
			|| Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			mAnimator->PlayAnimation(L"NinjaKirby_Choice", false);
			mState = eNinjaKirbyState::Choice;
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Enter", false);

			mState = eNinjaKirbyState::Enter;
		}
	}

	void NinjaKirby::Level_Run()
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

	void NinjaKirby::Level_FlyUp()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y -= 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void NinjaKirby::Level_Drop()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y += 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void NinjaKirby::Transformations()
	{
		mRigidBody->SetGround(true);

		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Drop", true);

			mState = eNinjaKirbyState::Drop;
		}
	}

	void NinjaKirby::Idle()
	{
		// 애니메이션 

		// 땅에 닿은 상태가 아니라면 Drop으로 변경 비탈길에서는 예외처리해줘야함
		if (!mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Drop", true);

			mState = eNinjaKirbyState::Drop;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Walk", true);
				mState = eNinjaKirbyState::Walk;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (!mbOnLeftStop)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Walk", true);
				mState = eNinjaKirbyState::Walk;
			}
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_Walk", true);
			mState = eNinjaKirbyState::Walk;
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Walk", true);
			mState = eNinjaKirbyState::Walk;
		}

		// Run
		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Run", true);
				mState = eNinjaKirbyState::Run;

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
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Run", true);
				mState = eNinjaKirbyState::Run;

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
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Jump", false);

			mState = eNinjaKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// 오디오 재생
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Down", false);

			mState = eNinjaKirbyState::Down;
		}

		// Shuriken
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_ThrowShuriken", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_ThrowShuriken", false);

			mState = eNinjaKirbyState::ThrowShuriken;

			// 스킬 생성
			NinjaKirby_Shuriken* shuriken = new NinjaKirby_Shuriken(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, shuriken);
		}

		if (Input::GetKeyPressed(eKeyCode::S))
		{
			mChargeTime += Time::DeltaTime();
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			mChargeTime = 0.f;
		}

		// Charge
		if (mChargeTime > 0.5f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Charge", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Charge", true);

			mState = eNinjaKirbyState::Charge;

			ResourceManager::Find<Sound>(L"NinjaChargeSound")->Play(false);
			mChargeTime = 0.f;
		}
	}

	void NinjaKirby::Walk()
	{
		// Stop 상태라면 Idle 로 상태변경
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Idle", true);

			mState = eNinjaKirbyState::Idle;
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
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Drop", true);

			mState = eNinjaKirbyState::Drop;
		}

		// Idle
		// 좌우 어느 키입력도 없으면 Idle 상태로 변경
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Idle", true);

			mState = eNinjaKirbyState::Idle;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Walk", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_Walk", true);
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Walk", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_Walk", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Jump", false);

			mState = eNinjaKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// 오디오 재생
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Down", false);

			mState = eNinjaKirbyState::Down;
		}

		// Shuriken
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_ThrowShuriken", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_ThrowShuriken", false);

			mState = eNinjaKirbyState::ThrowShuriken;

			// 스킬 생성
			NinjaKirby_Shuriken* shuriken = new NinjaKirby_Shuriken(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, shuriken);
		}

		if (Input::GetKeyPressed(eKeyCode::S))
		{
			mChargeTime += Time::DeltaTime();
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			mChargeTime = 0.f;
		}

		// Charge
		if (mChargeTime > 0.5f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Charge", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Charge", true);

			mState = eNinjaKirbyState::Charge;

			ResourceManager::Find<Sound>(L"NinjaChargeSound")->Play(false);
			mChargeTime = 0.f;
		}
	}

	void NinjaKirby::Run()
	{
		// Stop 상태라면 Idle 로 상태변경
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Idle", true);

			mState = eNinjaKirbyState::Idle;

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
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Drop", true);

			mState = eNinjaKirbyState::Drop;
		}

		// Idle
		// 좌우 어느 키입력도 없으면 Idle 상태로 변경
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Idle", true);

			mState = eNinjaKirbyState::Idle;
		}

		// Run
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Run", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_Run", true);
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Run", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_Run", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Jump", false);

			mState = eNinjaKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// 오디오 재생
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Down", false);

			mState = eNinjaKirbyState::Down;
		}

		// Shuriken
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_ThrowShuriken", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_ThrowShuriken", false);

			mState = eNinjaKirbyState::ThrowShuriken;

			// 스킬 생성
			NinjaKirby_Shuriken* shuriken = new NinjaKirby_Shuriken(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, shuriken);
		}

		if (Input::GetKeyPressed(eKeyCode::S))
		{
			mChargeTime += Time::DeltaTime();
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			mChargeTime = 0.f;
		}

		// Charge
		if (mChargeTime > 0.5f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Charge", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Charge", true);

			mState = eNinjaKirbyState::Charge;

			ResourceManager::Find<Sound>(L"NinjaChargeSound")->Play(false);
			mChargeTime = 0.f;
		}
	}

	void NinjaKirby::Jump()
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
					mAnimator->PlayAnimation(L"NinjaKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"NinjaKirby_Left_Turn", false);

				mState = eNinjaKirbyState::Turn;

				mKeyPressdTime = 0.f;
				mKeyReleaseTime = 0.f;
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			}
		}

		if (!Input::GetKeyPressed(eKeyCode::A) && !Input::GetKeyPressed(eKeyCode::D))
		{
			mKeyReleaseTime += Time::DeltaTime();

			// 키를 뗀시간이 일정시간이상 지나면 상태변경
			if (mKeyReleaseTime > 0.125f)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"NinjaKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"NinjaKirby_Left_Turn", false);

				mState = eNinjaKirbyState::Turn;

				mKeyPressdTime = 0.f;
				mKeyReleaseTime = 0.f;
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
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
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Jump", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_Jump", true);
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Jump", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_Jump", true);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyStart", false);

			mState = eNinjaKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
			mKeyPressdTime = 0.f;
			mKeyReleaseTime = 0.f;

			// 오디오 재생
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}

		// Shuriken
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_ThrowShuriken", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_ThrowShuriken", false);

			mState = eNinjaKirbyState::ThrowShuriken;

			mKeyPressdTime = 0.f;
			mKeyReleaseTime = 0.f;

			// 스킬 생성
			NinjaKirby_Shuriken* shuriken = new NinjaKirby_Shuriken(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, shuriken);
		}

		if (Input::GetKeyPressed(eKeyCode::S))
		{
			mChargeTime += Time::DeltaTime();
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			mChargeTime = 0.f;
		}

		// Charge
		if (mChargeTime > 0.5f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Charge", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Charge", true);

			mState = eNinjaKirbyState::Charge;

			mKeyPressdTime = 0.f;
			mKeyReleaseTime = 0.f;

			ResourceManager::Find<Sound>(L"NinjaChargeSound")->Play(false);
			mChargeTime = 0.f;
		}
	}

	void NinjaKirby::Turn()
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
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Drop", true);

			TurnTime = 0.f;
			mState = eNinjaKirbyState::Drop;
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyStart", false);

			TurnTime = 0.f;
			mState = eNinjaKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));

			// 오디오 재생
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}

		// Shuriken
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_ThrowShuriken", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_ThrowShuriken", false);

			mState = eNinjaKirbyState::ThrowShuriken;

			// 스킬 생성
			NinjaKirby_Shuriken* shuriken = new NinjaKirby_Shuriken(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, shuriken);
		}

		if (Input::GetKeyPressed(eKeyCode::S))
		{
			mChargeTime += Time::DeltaTime();
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			mChargeTime = 0.f;
		}

		// Charge
		if (mChargeTime > 0.5f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Charge", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Charge", true);

			mState = eNinjaKirbyState::Charge;

			ResourceManager::Find<Sound>(L"NinjaChargeSound")->Play(false);
			mChargeTime = 0.f;
		}
	}

	void NinjaKirby::Drop()
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
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Drop", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_Drop", true);
		}

		// 방향전환 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && mDir == eDirection::LEFT)
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Drop", true);
		}

		if (Input::GetKeyPressed(eKeyCode::LEFT) && mDir == eDirection::RIGHT)
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_Drop", true);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyStart", false);

			mState = eNinjaKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
		}

		if (mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Idle", true);

			mState = eNinjaKirbyState::Idle;
			ResourceManager::Find<Sound>(L"LandSound")->Play(false);
		}

		// Shuriken
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_ThrowShuriken", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_ThrowShuriken", false);

			mState = eNinjaKirbyState::ThrowShuriken;

			// 스킬 생성
			NinjaKirby_Shuriken* shuriken = new NinjaKirby_Shuriken(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, shuriken);
		}

		if (Input::GetKeyPressed(eKeyCode::S))
		{
			mChargeTime += Time::DeltaTime();
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			mChargeTime = 0.f;
		}

		// Charge
		if (mChargeTime > 0.5f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Charge", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Charge", true);

			mState = eNinjaKirbyState::Charge;

			ResourceManager::Find<Sound>(L"NinjaChargeSound")->Play(false);
			mChargeTime = 0.f;
		}
	}

	void NinjaKirby::Down()
	{
		// 애니메이션

		// 반대방향키가 눌렸을때 방향 전환
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"NinjaKirby_Right_Down", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_Down", true);
		}

		// 키입력이없을땐 Idle 로 변경
		if (!Input::GetKeyPressed(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Idle", true);

			mState = eNinjaKirbyState::Idle;
		}
	}

	void NinjaKirby::Fly_Start()
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
				mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyEnd", false);

			mState = eNinjaKirbyState::Fly_End;

			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);
		}

		// 애니메이션이 끝나면 Fly Down 상태로 변경
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyDown", true);

			mState = eNinjaKirbyState::Fly_Down;
		}
	}

	void NinjaKirby::Fly_End()
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
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Drop", true);

			mState = eNinjaKirbyState::Drop;
		}
	}

	void NinjaKirby::Fly_Down()
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
			mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyDown", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyDown", true);
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyDown", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyDown", true);
		}


		// Fly Up
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyUp", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyUp", true);

			mState = eNinjaKirbyState::Fly_Up;
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
				mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyEnd", false);

			mState = eNinjaKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			mRigidBody->SetLimitVelocity(Vector2(300.f, 300.f));

			// 오디오 재생
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void NinjaKirby::Fly_Up()
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
			mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyUp", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyUp", true);
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyUp", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyUp", true);
		}

		// 누르고있을때 상승
		if (Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			// 상단에 충돌한 상태면 속도를 0으로 설정하고 고정위치 셋팅
			if (mbTopStop)
			{
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
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
				mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyDown", true);

			mState = eNinjaKirbyState::Fly_Down;
		}

		// Fly End
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_FlyEnd", false);

			mState = eNinjaKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			// 오디오 재생
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void NinjaKirby::ThrowShuriken()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Drop", true);

			mState = eNinjaKirbyState::Drop;
		}

		if (Input::GetKeyPressed(eKeyCode::S))
		{
			mChargeTime += Time::DeltaTime();
		}

		if (Input::GetKeyUp(eKeyCode::S))
		{
			mChargeTime = 0.f;
		}

		// Charge
		if (mChargeTime > 0.5f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"NinjaKirby_Right_Charge", true);
			else
				mAnimator->PlayAnimation(L"NinjaKirby_Left_Charge", true);

			mState = eNinjaKirbyState::Charge;

			ResourceManager::Find<Sound>(L"NinjaChargeSound")->Play(false);
			mChargeTime = 0.f;
		}
	}

	void NinjaKirby::Charge()
	{
		static bool	bFireTrig = false;
		static float Duration = 0.f;

		if (!bFireTrig)
		{
			Duration += Time::DeltaTime();
		}
		
		if (Duration > 0.5f)
		{
			Duration = 0.f;
			bFireTrig = true;
			NinjaKirby_ChargeEffect* effect = new NinjaKirby_ChargeEffect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect);
		}

		if (!Input::GetKeyPressed(eKeyCode::S))
		{
			if (bFireTrig)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"NinjaKirby_Right_Fire", false);
				else
					mAnimator->PlayAnimation(L"NinjaKirby_Left_Fire", false);

				mState = eNinjaKirbyState::Fire;			
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"NinjaKirby_Right_Drop", true);
				else
					mAnimator->PlayAnimation(L"NinjaKirby_Left_Drop", true);

				mState = eNinjaKirbyState::Drop;
			}

			bFireTrig = false;
			Duration = 0.f;
		}	
	}

	void NinjaKirby::Fire()
	{
		static float Duration = 0.f;

		Duration += Time::DeltaTime();



		static bool bActive[4] = { true, true, true, true };

		if (bActive[0])
		{
			NinjaKirby_Fire* effect = new NinjaKirby_Fire(GetOwner(), GetOwner()->GetComponent<Transform>()->GetPosition());
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect);

			bActive[0] = false;
		}
		else if (Duration >= 0.2f && bActive[1])
		{
			Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

			NinjaKirby_Fire* effect1 = new NinjaKirby_Fire(GetOwner(),Vector2(pos.x + 20.f, pos.y));
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect1);

			NinjaKirby_Fire* effect2 = new NinjaKirby_Fire(GetOwner(), Vector2(pos.x - 20.f, pos.y));
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect2);

			bActive[1] = false;
		}
		else if (Duration >= 0.4f && bActive[2])
		{
			Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

			NinjaKirby_Fire* effect1 = new NinjaKirby_Fire(GetOwner(), Vector2(pos.x + 40.f, pos.y));
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect1);

			NinjaKirby_Fire* effect2 = new NinjaKirby_Fire(GetOwner(), Vector2(pos.x - 40.f, pos.y));
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect2);

			bActive[2] = false;
		}
		else if (Duration >= 0.6f && bActive[3])
		{
			Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

			NinjaKirby_Fire* effect1 = new NinjaKirby_Fire(GetOwner(), Vector2(pos.x + 60.f, pos.y));
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect1);

			NinjaKirby_Fire* effect2 = new NinjaKirby_Fire(GetOwner(), Vector2(pos.x - 60.f, pos.y));
			object::ActiveSceneAddGameObject(eLayerType::Effect, effect2);

			bActive[3] = false;
		}


		if (Duration > 1.f)
		{
			if (mAnimator->IsActiveAnimationComplete())
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"NinjaKirby_Right_Drop", true);
				else
					mAnimator->PlayAnimation(L"NinjaKirby_Left_Drop", true);

				mState = eNinjaKirbyState::Drop;
			}

			Duration = 0.f;
			bActive[0] = bActive[1] = bActive[2] = bActive[3] = true;
		}
	}
}