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
		// �ؽ��� �ε�
		Texture* SwordKirby_Right = ResourceManager::Load<Texture>(L"SwordKirby_Right_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Right.bmp");
		Texture* SwordKirby_Left = ResourceManager::Load<Texture>(L"SwordKirby_Left_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Left.bmp");

		Texture* SwordKirby_Right_Slash_Tex = ResourceManager::Load<Texture>(L"SwordKirby_Right_Slash_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Right_Slash.bmp");
		Texture* SwordKirby_Left_Slash_Tex = ResourceManager::Load<Texture>(L"SwordKirby_Left_Slash_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Left_Slash.bmp");

		Texture* SwordKirby_Right_Slashing_Tex = ResourceManager::Load<Texture>(L"SwordKirby_Right_Slashing_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Right_Slashing.png");
		Texture* SwordKirby_Left_Slashing_Tex = ResourceManager::Load<Texture>(L"SwordKirby_Left_Slashing_Tex", L"..\\Resources\\Kirby\\SwordKirby\\SwordKirby_Left_Slashing.png");

		SwordKirby_Right->SetScale(Vector2(0.35f, 0.35f));
		SwordKirby_Left->SetScale(Vector2(0.35f, 0.35f));

		// Player ���� ������� ������Ʈ ��������� ����
		mAnimator = GetOwner()->GetComponent<Animator>();
		mTransform = GetOwner()->GetComponent<Transform>();

		mRigidBody = GetOwner()->GetComponent<Rigidbody>();
		mRigidBody->SetGround(true);

		// �ִϸ��̼� ����
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
		// ���� ����
		mDir = mTransform->GetDirection();

		// PlayerMode �� ���� ����ó�� 
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

				// ���º��� ���� ����
				return;
			}

			// �ȼ��浹 üũ
			CheckPixelCollision();

			// ����ó��
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

			// �̵�����
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
		// Ư�����¿��� AttackArea�� �浹 ����
		if (mState == eSwordKirbyState::DownAttack
			|| mState == eSwordKirbyState::JumpAttack
			|| mState == eSwordKirbyState::Slash
			|| mState == eSwordKirbyState::Slashing)
			return;

		// �÷��̾� ������ ���¸� �浹ó�� X
		if (GetOwner()->IsDamaged())
			return;

		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (enemy == nullptr)
			return;

		// BossEnemy�� �÷��̾� �浹 ����
		BossEnemy* bossEnemy = dynamic_cast<BossEnemy*>(other->GetOwner());
		if (bossEnemy != nullptr)
			return;

		// Ŀ�� �� ���� ����
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
		// Ư�� ���¿��� �浹 ����
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

		// StageŸ�Կ����� �ȼ��ؽ��� �����ϱ�
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

		// Offset �ȼ� �»����ġ ����
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

		// ��� ó��
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



		// �ٴ� ó��
		if (LBColor == RGB(0, 0, 255) || RBColor == RGB(0, 0, 255) || MBColor == RGB(0, 0, 255)
			|| MBColor == RGB(255, 0, 0))
		{
			// Ư�������϶��� �ٴ� ����
			if (!(mState == eSwordKirbyState::Jump
				|| mState == eSwordKirbyState::Fly_Up))
			{
				// �̵�
				Vector2 pos = mTransform->GetPosition();
				pos.y -= 1.f;
				mTransform->SetPosition(pos);
				mRigidBody->SetGround(true);

				// Blue �� �ν��ϵ��� ����
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

		// �ٴ� ~ �ٴ� + 1�ȼ� ������ �ƴҰ�� Ground false ó��
		if (!(LBColor == RGB(0, 0, 255) || LBColorOffsetY == RGB(0, 0, 255)
			|| RBColor == RGB(0, 0, 255) || RBColorOffsetY == RGB(0, 0, 255)
			|| MBColor == RGB(255, 0, 0) || MBColorOffsetY == RGB(255, 0, 0)))
		{
			mRigidBody->SetGround(false);
		}


		// OnSlope Check 
		// �Ʒ��� 20�ȼ����� üũ
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
			// �̵�
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 1.f;
			mTransform->SetPosition(pos);
			mbOnRightStop = true;
		}
		else if (RBColorOffsetX == RGB(0, 255, 0))
		{
			// ���ȼ� Offset ó��
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
			// �̵�
			Vector2 pos = mTransform->GetPosition();
			pos.x += 1.f;
			mTransform->SetPosition(pos);
			mbOnLeftStop = true;
		}
		else if (LBColorOffsetX == RGB(0, 255, 0))
		{
			// ���ȼ� Offset ó��
			mbOnLeftStop = true;
		}
		else
		{
			mbOnLeftStop = false;
		}

		// �ݴ����Ű�������� Stop ����
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
		// �ִϸ��̼�
		if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::RIGHT)) && !GetOwner()->GetLevelEnter())
		{
			mAnimator->PlayAnimation(L"SwordKirby_Choice", false);
		}

		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			// ���� ù�����̶�� Enter�ִϸ��̼� ���
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
		// �ִϸ��̼��� ������ Idle ���·� ����
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
		// �ִϸ��̼� 

		// ���� ���� ���°� �ƴ϶�� Drop���� ���� ��Ż�濡���� ����ó���������
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

		// Ű ���� �Է� ����ó��
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

				// ����� ���
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

				// ����� ���
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

			// ����� ���
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

			// ��ų ����
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// ����� ���		
			ResourceManager::Find<Sound>(L"SwordKirbyAttackSound")->Play(false);
		}
	}

	void SwordKirby::Walk()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Idle", true);

			mState = eSwordKirbyState::Idle;
			return;
		}

		// Stop ���°� �ƴѰ�쿡�� �̵�
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// �¿� �̵�
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

		// �ִϸ��̼�

		// ���� ���� ���°� �ƴϸ鼭 ���ΰ� �ƴ϶�� Drop���� ����
		if (!mRigidBody->IsGround() && mbOnSlope == false)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Drop", true);

			mState = eSwordKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
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

		// Ű ���� �Է� ����ó��
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

			// ����� ���
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

			// ��ų ����
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// ����� ���		
			ResourceManager::Find<Sound>(L"SwordKirbyAttackSound")->Play(false);
		}
	}

	void SwordKirby::Run()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Idle", true);

			mState = eSwordKirbyState::Idle;

			return;
		}

		// Stop ���°� �ƴѰ�쿡�� �̵�
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// �¿� �̵�
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

		// �ִϸ��̼�

		// ���� ���� ���°� �ƴϸ鼭 ���ΰ� �ƴ϶�� Drop���� ����
		if (!mRigidBody->IsGround() && mbOnSlope == false)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SwordKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SwordKirby_Left_Drop", true);

			mState = eSwordKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
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

		// Ű ���� �Է� ����ó��
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

			// ����� ���
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

			// ��ų ����
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// ����� ���		
			ResourceManager::Find<Sound>(L"SwordKirbyAttackSound")->Play(false);
		}
	}

	void SwordKirby::Jump()
	{
		// ���� �̵�
		if (Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			mKeyPressdTime += Time::DeltaTime();

			// ���� ���� �ð����� ���
			if (mKeyPressdTime < 0.2f)
			{
				mRigidBody->AddForce(Vector2(0.f, -400.f));
			}

			// Ű�� ���� �ð��� �����ð��̻� ������ ���º���
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

			// Ű�� ���ð��� �����ð��̻� ������ ���º���
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

		// Stop ���°� �ƴѰ�쿡�� �̵�
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// �¿� �̵�
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


		// �ִϸ��̼�

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

		// Ű ���� �Է� ����ó��
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

			// ��ų ����
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// ����� ���		
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

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void SwordKirby::Turn()
	{
		// Stop ���°� �ƴѰ�쿡�� �̵�
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// �¿� �̵�
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

		// �ִϸ��̼�	
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

		// �ִϸ��̼��� ������ ���� ����
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

			// ��ų ����
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// ����� ���		
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

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void SwordKirby::Drop()
	{
		// Stop ���°� �ƴѰ�쿡�� �̵�
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// �¿� �̵�
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

		// ������ȯ ����ó��
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

			// ��ų ����
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(100.f, 100.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// ����� ���		
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
		// �ִϸ��̼�

		// �ݴ����Ű�� �������� ���� ��ȯ
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

			// ��ų ����
			SwordKirby_AttackArea* AttackArea = new SwordKirby_AttackArea(GetOwner(), Vector2(50.f, 15.f));
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			// ����� ���		
			ResourceManager::Find<Sound>(L"SwordKirbyAttackSound")->Play(false);
		}

		// Ű�Է��̾����� Idle �� ����
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
		// Stop ���°� �ƴѰ�쿡�� �̵�
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// �¿� �̵�
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

		// ������ȯ
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

		// �ִϸ��̼��� ������ Fly Down ���·� ����
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
		// Stop ���°� �ƴѰ�쿡�� �̵�
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// �¿� �̵�
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


		// ���� ��ȯ
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
		}

		// �ִϸ��̼��� ������ Drop ���·� ����
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
		// Fly���¿��� �ӵ�����
		mRigidBody->SetLimitVelocity(Vector2(50.f, 50.f));

		// Stop ���°� �ƴѰ�쿡�� �̵�
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// �¿� �̵�
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

		// ���� ��ȯ
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

		// Ű ���� �Է� ����ó��
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

			// ����� ���
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

			// ����� ���
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void SwordKirby::Fly_Up()
	{
		// Stop ���°� �ƴѰ�쿡�� �̵�
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// �¿� �̵�
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


		// ���� ��ȯ
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

		// Ű ���� �Է� ����ó��
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

		// ������������ ���
		if (Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			// ��ܿ� �浹�� ���¸� �ӵ��� 0���� �����ϰ� ������ġ ����
			if (mbTopStop)
			{
				mRigidBody->SetVelocity(Vector2::Zero);
				// �¿� �̵�
				Vector2 pos = mTransform->GetPosition();
				pos.y -= 1.f;
				mTransform->SetPosition(pos);
			}
			else
			{
				mRigidBody->SetVelocity(Vector2(0.f, -80.f));
			}
		}

		// Ű�� ���������� ������ Fly Down
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

			// ����� ���
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