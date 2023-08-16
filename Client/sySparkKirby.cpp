#include "sySparkKirby.h"
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
#include "syAbilityStar.h"
#include "sySparkKirby_Skill.h"
#include "syBossEnemy.h"

namespace sy
{
	SparkKirby::SparkKirby(class Player* owner)
		: Kirby(owner)
		, mState(eSparkKirbyState::Idle)
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
		, mSkill(nullptr)
	{
	}

	SparkKirby::~SparkKirby()
	{
	}

	void SparkKirby::Initialize()
	{
		// �ؽ��� �ε�
		Texture* SparkKirby_Right = ResourceManager::Load<Texture>(L"SparkKirby_Right_Tex", L"..\\Resources\\Kirby\\SparkKirby\\SparkKirby_Right.bmp");
		Texture* SparkKirby_Left = ResourceManager::Load<Texture>(L"SparkKirby_Left_Tex", L"..\\Resources\\Kirby\\SparkKirby\\SparkKirby_Left.bmp");

		// Player ���� ������� ������Ʈ ��������� ����
		mAnimator = GetOwner()->GetComponent<Animator>();
		mTransform = GetOwner()->GetComponent<Transform>();

		mRigidBody = GetOwner()->GetComponent<Rigidbody>();
		mRigidBody->SetGround(true);

		// �ִϸ��̼� ����
		Vector2 Animationoffset = Vector2(0.f, 10.f);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Choice", Vector2(2304.f, 512.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.05f, 6, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_Enter", Vector2(2304.f, 3840.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.5f, 2, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_Enter", Vector2(2304.f, 3840.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.5f, 2, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_Idle", Vector2(0.f, 0.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.125f, 8, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_Idle", Vector2(0.f, 0.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.125f, 8, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_Walk", Vector2(1792.f, 768.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.025f, 20, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_Walk", Vector2(1792.f, 768.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.025f, 20, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_Run", Vector2(1792.f, 1280.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.05f, 8, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_Run", Vector2(1792.f, 1280.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.05f, 8, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_Jump", Vector2(1536.f, 512.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.1f, 2, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_Jump", Vector2(1536.f, 512.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.1f, 2, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_Turn", Vector2(2304.f, 512.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.035f, 6, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_Turn", Vector2(2304.f, 512.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.035f, 6, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_Drop", Vector2(1024.f, 768.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.05f, 2, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_Drop", Vector2(1024.f, 768.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.05f, 2, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_Down", Vector2(2048.f, 0.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.125f, 8, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_Down", Vector2(2048.f, 0.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.125f, 8, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_FlyStart", Vector2(768.f, 1792.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.05f, 4, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_FlyStart", Vector2(768.f, 1792.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.05f, 4, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_FlyEnd", Vector2(1536.f, 2560.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.1f, 2, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_FlyEnd", Vector2(1536.f, 2560.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.1f, 2, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_FlyDown", Vector2(0.f, 2304.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.04f, 10, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_FlyDown", Vector2(0.f, 2304.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.04f, 10, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_FlyUp", Vector2(1792.f, 1792.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.02f, 29, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_FlyUp", Vector2(1792.f, 1792.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.02f, 29, Animationoffset);

		mAnimator->CreateAnimation(SparkKirby_Right, L"SparkKirby_Right_Skill", Vector2(1792.f, 3328.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.03f, 3, Animationoffset);
		mAnimator->CreateAnimation(SparkKirby_Left, L"SparkKirby_Left_Skill", Vector2(1792.f, 3328.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.03f, 3, Animationoffset);
		
		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"FlySound", L"..\\Resources\\Sound\\Effect\\Fly.wav");
		ResourceManager::Load<Sound>(L"JumpSound", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		ResourceManager::Load<Sound>(L"LandSound", L"..\\Resources\\Sound\\Effect\\Land.wav");
		ResourceManager::Load<Sound>(L"RunSound", L"..\\Resources\\Sound\\Effect\\Run.wav");
		ResourceManager::Load<Sound>(L"ClickSound", L"..\\Resources\\Sound\\Effect\\Click.wav");


		ResourceManager::Find<Sound>(L"JumpSound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"FlySound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"LandSound")->SetVolume(10.f);
		ResourceManager::Find<Sound>(L"RunSound")->SetVolume(100.f);
	}

	void SparkKirby::Update()
	{
		// ���� ����
		mDir = mTransform->GetDirection();

		// PlayerMode �� ���� ����ó�� 
		if (GetOwner()->GetPlayerMode() == ePlayerMode::LevelMode)
		{
			switch (mState)
			{
			case eSparkKirbyState::Transformations:
				Level_Transformations();
				break;
			case eSparkKirbyState::Choice:
				Choice();
				break;
			case eSparkKirbyState::Enter:
				Level_Enter();
				break;
			case eSparkKirbyState::Idle:
				Level_Idle();
				break;
			case eSparkKirbyState::Run:
				Level_Run();
				break;
			case eSparkKirbyState::Fly_Up:
				Level_FlyUp();
				break;
			case eSparkKirbyState::Drop:
				Level_Drop();
				break;
			default:
				break;
			}
		}
		else if (GetOwner()->GetPlayerMode() == ePlayerMode::PlayMode)
		{
			if (Input::GetKeyDown(eKeyCode::W)
				&& mState != eSparkKirbyState::Skill)
			{
				eDefaultKirbyState state = eDefaultKirbyState::Idle;

				if (mState == eSparkKirbyState::Idle)
					state = eDefaultKirbyState::Idle;
				else if (mState == eSparkKirbyState::Walk)
					state = eDefaultKirbyState::Walk;
				else if (mState == eSparkKirbyState::Run)
					state = eDefaultKirbyState::Run;
				else if (mState == eSparkKirbyState::Down)
					state = eDefaultKirbyState::Down;
				else
					state = eDefaultKirbyState::Drop;

				GetOwner()->ReleaseTransformations(state);

				AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Spark);
				object::ActiveSceneAddGameObject(eLayerType::AbilityItem, abilityStar);

				// ���º��� ���� ����
				return;
			}

			// �ȼ��浹 üũ
			CheckPixelCollision();

			// ����ó��
			switch (mState)
			{
			case eSparkKirbyState::Transformations:
				Transformations();
				break;
			case eSparkKirbyState::Idle:
				Idle();
				break;
			case eSparkKirbyState::Walk:
				Walk();
				break;
			case eSparkKirbyState::Run:
				Run();
				break;
			case eSparkKirbyState::Jump:
				Jump();
				break;
			case eSparkKirbyState::Turn:
				Turn();
				break;
			case eSparkKirbyState::Drop:
				Drop();
				break;
			case eSparkKirbyState::Down:
				Down();
				break;
			case eSparkKirbyState::Fly_Start:
				Fly_Start();
				break;
			case eSparkKirbyState::Fly_End:
				Fly_End();
				break;
			case eSparkKirbyState::Fly_Down:
				Fly_Down();
				break;
			case eSparkKirbyState::Fly_Up:
				Fly_Up();
				break;
			case eSparkKirbyState::Skill:
				Skill();
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

	void SparkKirby::Enter()
	{
		if (mDir == eDirection::RIGHT)
			mAnimator->PlayAnimation(L"SparkKirby_Right_Enter", false);
		else
			mAnimator->PlayAnimation(L"SparkKirby_Left_Enter", false);

		mState = eSparkKirbyState::Transformations;
	}

	void SparkKirby::Exit()
	{
	}

	void SparkKirby::OnCollisionEnter(Collider* other)
	{
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

	void SparkKirby::OnCollisionStay(Collider* other)
	{
	}

	void SparkKirby::OnCollisionExit(Collider* other)
	{
	}

	bool SparkKirby::IsTransformableCheck()
	{
		if (mState == eSparkKirbyState::Skill)
			return false;

		return true;
	}

	void SparkKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		// Ư�� ���¿��� �浹 ����
		if (mState == eSparkKirbyState::Transformations || mState == eSparkKirbyState::Skill)
			return;

		mKeyPressdTime = 0.f;
		mKeyReleaseTime = 0.f;

		AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Spark);
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

	void SparkKirby::CheckPixelCollision()
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
			if (!(mState == eSparkKirbyState::Jump
				|| mState == eSparkKirbyState::Fly_Up))
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

	void SparkKirby::Level_Transformations()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);

			mState = eSparkKirbyState::Idle;
		}
	}

	void SparkKirby::Choice()
	{
		// �ִϸ��̼�
		if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::RIGHT)) && !GetOwner()->GetLevelEnter())
		{
			mAnimator->PlayAnimation(L"SparkKirby_Choice", false);
		}

		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			// ���� ù�����̶�� Enter�ִϸ��̼� ���
			if (GetOwner()->GetLevelEnter())
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"SparkKirby_Right_Enter", false);
				else
					mAnimator->PlayAnimation(L"SparkKirby_Left_Enter", false);

				mState = eSparkKirbyState::Enter;
				GetOwner()->SetLevelEnter(false);
			}
			else
			{
				mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);
				mState = eSparkKirbyState::Idle;
			}
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Enter", false);

			mState = eSparkKirbyState::Enter;
		}
	}

	void SparkKirby::Level_Enter()
	{
		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);

			mState = eSparkKirbyState::Idle;
		}
	}

	void SparkKirby::Level_Idle()
	{
		if (Input::GetKeyDown(eKeyCode::UP)
			|| Input::GetKeyDown(eKeyCode::DOWN)
			|| Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			mAnimator->PlayAnimation(L"SparkKirby_Choice", false);
			mState = eSparkKirbyState::Choice;
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Enter", false);

			mState = eSparkKirbyState::Enter;
		}
	}

	void SparkKirby::Level_Run()
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

	void SparkKirby::Level_FlyUp()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y -= 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void SparkKirby::Level_Drop()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y += 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void SparkKirby::Transformations()
	{
		mRigidBody->SetGround(true);

		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Drop", true);

			mState = eSparkKirbyState::Drop;
		}
	}

	void SparkKirby::Idle()
	{
		// �ִϸ��̼� 

		// ���� ���� ���°� �ƴ϶�� Drop���� ���� ��Ż�濡���� ����ó���������
		if (!mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Drop", true);

			mState = eSparkKirbyState::Drop;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"SparkKirby_Right_Walk", true);
				mState = eSparkKirbyState::Walk;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (!mbOnLeftStop)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"SparkKirby_Left_Walk", true);
				mState = eSparkKirbyState::Walk;
			}
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_Walk", true);
			mState = eSparkKirbyState::Walk;
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SparkKirby_Right_Walk", true);
			mState = eSparkKirbyState::Walk;
		}

		// Run
		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"SparkKirby_Right_Run", true);
				mState = eSparkKirbyState::Run;

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
				mAnimator->PlayAnimation(L"SparkKirby_Left_Run", true);
				mState = eSparkKirbyState::Run;

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
				mAnimator->PlayAnimation(L"SparkKirby_Right_Jump", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Jump", true);

			mState = eSparkKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Down", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Down", true);

			mState = eSparkKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Skill", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Skill", false);

			mState = eSparkKirbyState::Skill;

			// ��ų ����
			mSkill = new SparkKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);
		}
	}

	void SparkKirby::Walk()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Idle", true);

			mState = eSparkKirbyState::Idle;
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
				mAnimator->PlayAnimation(L"SparkKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Drop", true);

			mState = eSparkKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Idle", true);

			mState = eSparkKirbyState::Idle;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SparkKirby_Right_Walk", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_Walk", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SparkKirby_Right_Walk", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_Walk", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Jump", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Jump", true);

			mState = eSparkKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Down", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Down", true);

			mState = eSparkKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Skill", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Skill", false);

			mState = eSparkKirbyState::Skill;

			// ��ų ����
			mSkill = new SparkKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);
		}
	}

	void SparkKirby::Run()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Idle", true);

			mState = eSparkKirbyState::Idle;

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
				mAnimator->PlayAnimation(L"SparkKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Drop", true);

			mState = eSparkKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Idle", true);

			mState = eSparkKirbyState::Idle;
		}

		// Run
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SparkKirby_Right_Run", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_Run", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SparkKirby_Right_Run", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_Run", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Jump", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Jump", true);

			mState = eSparkKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Down", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Down", true);

			mState = eSparkKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Skill", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Skill", false);

			mState = eSparkKirbyState::Skill;

			// ��ų ����
			mSkill = new SparkKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);
		}
	}

	void SparkKirby::Jump()
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
					mAnimator->PlayAnimation(L"SparkKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"SparkKirby_Left_Turn", false);

				mState = eSparkKirbyState::Turn;

				mKeyPressdTime = 0.f;
				mKeyReleaseTime = 0.f;
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			}
		}

		if (!Input::GetKeyPressed(eKeyCode::A) && !Input::GetKeyPressed(eKeyCode::D))
		{
			mKeyReleaseTime += Time::DeltaTime();

			// Ű�� ���ð��� �����ð��̻� ������ ���º���
			if (mKeyReleaseTime > 0.125f)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"SparkKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"SparkKirby_Left_Turn", false);

				mState = eSparkKirbyState::Turn;

				mKeyPressdTime = 0.f;
				mKeyReleaseTime = 0.f;
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
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
			mAnimator->PlayAnimation(L"SparkKirby_Right_Jump", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_Jump", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SparkKirby_Right_Jump", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_Jump", true);
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Skill", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Skill", false);

			mState = eSparkKirbyState::Skill;

			mKeyPressdTime = 0.f;
			mKeyReleaseTime = 0.f;

			// ��ų ����
			mSkill = new SparkKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_FlyStart", false);

			mState = eSparkKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
			mKeyPressdTime = 0.f;
			mKeyReleaseTime = 0.f;

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void SparkKirby::Turn()
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
				mAnimator->PlayAnimation(L"SparkKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Drop", true);

			TurnTime = 0.f;
			mState = eSparkKirbyState::Drop;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Skill", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Skill", false);

			mState = eSparkKirbyState::Skill;

			// ��ų ����
			mSkill = new SparkKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_FlyStart", false);

			TurnTime = 0.f;
			mState = eSparkKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void SparkKirby::Drop()
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
			mAnimator->PlayAnimation(L"SparkKirby_Right_Drop", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_Drop", true);
		}

		// ������ȯ ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && mDir == eDirection::LEFT)
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SparkKirby_Right_Drop", true);
		}

		if (Input::GetKeyPressed(eKeyCode::LEFT) && mDir == eDirection::RIGHT)
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_Drop", true);
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Skill", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Skill", false);

			mState = eSparkKirbyState::Skill;

			// ��ų ����
			mSkill = new SparkKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_FlyStart", false);

			mState = eSparkKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
		}

		if (mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Idle", true);

			mState = eSparkKirbyState::Idle;
			ResourceManager::Find<Sound>(L"LandSound")->Play(false);
		}
	}

	void SparkKirby::Down()
	{
		// �ִϸ��̼�

		// �ݴ����Ű�� �������� ���� ��ȯ
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SparkKirby_Right_Down", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_Down", true);
		}

		// Ű�Է��̾����� Idle �� ����
		if (!Input::GetKeyPressed(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Idle", true);

			mState = eSparkKirbyState::Idle;
		}
	}

	void SparkKirby::Fly_Start()
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
				mAnimator->PlayAnimation(L"SparkKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_FlyEnd", false);

			mState = eSparkKirbyState::Fly_End;

			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);
		}

		// �ִϸ��̼��� ������ Fly Down ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_FlyDown", true);

			mState = eSparkKirbyState::Fly_Down;
		}
	}

	void SparkKirby::Fly_End()
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
				mAnimator->PlayAnimation(L"SparkKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Drop", true);

			mState = eSparkKirbyState::Drop;
		}
	}

	void SparkKirby::Fly_Down()
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
			mAnimator->PlayAnimation(L"SparkKirby_Right_FlyDown", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_FlyDown", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SparkKirby_Right_FlyDown", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_FlyDown", true);
		}


		// Fly Up
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_FlyUp", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_FlyUp", true);

			mState = eSparkKirbyState::Fly_Up;
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
				mAnimator->PlayAnimation(L"SparkKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_FlyEnd", false);

			mState = eSparkKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			mRigidBody->SetLimitVelocity(Vector2(300.f, 300.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void SparkKirby::Fly_Up()
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
			mAnimator->PlayAnimation(L"SparkKirby_Right_FlyUp", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_FlyUp", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"SparkKirby_Right_FlyUp", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"SparkKirby_Left_FlyUp", true);
		}

		// ������������ ���
		if (Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			// ��ܿ� �浹�� ���¸� �ӵ��� 0���� �����ϰ� ������ġ ����
			if (mbTopStop)
			{
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
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
				mAnimator->PlayAnimation(L"SparkKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_FlyDown", true);

			mState = eSparkKirbyState::Fly_Down;
		}

		// Fly End
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_FlyEnd", false);

			mState = eSparkKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			// ����� ���
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void SparkKirby::Skill()
	{
		// Ű�Է��̾������ Idle �� ����
		if (!Input::GetKeyPressed(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SparkKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SparkKirby_Left_Idle", true);

			mState = eSparkKirbyState::Idle;

			Destroy(mSkill);

			// ����� ����		
			ResourceManager::Find<Sound>(L"SparkSound")->Stop(true);		
		}
	}
}