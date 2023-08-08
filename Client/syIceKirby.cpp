#include "syIceKirby.h"
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
#include "syIceKirby_Skill.h"
#include "syAbilityStar.h"

namespace sy
{
	IceKirby::IceKirby(class Player* owner)
		: Kirby(owner)
		, mState(eIceKirbyState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::RIGHT)
		, mbOnLeftStop(false)
		, mbOnRightStop(false)
		, mbTopStop(false)
		, mbOnSlope(false)
		, mSkill(nullptr)
	{
	}

	IceKirby::~IceKirby()
	{
	}

	void IceKirby::Initialize()
	{
		// �ؽ��� �ε�
		Texture* IceKirby_Right = ResourceManager::Load<Texture>(L"IceKirby_Right_Tex", L"..\\Resources\\Kirby\\IceKirby\\IceKirby_Right.bmp");
		Texture* IceKirby_Left = ResourceManager::Load<Texture>(L"IceKirby_Left_Tex", L"..\\Resources\\Kirby\\IceKirby\\IceKirby_Left.bmp");

		// Player ���� ������� ������Ʈ ��������� ����
		mAnimator = GetOwner()->GetComponent<Animator>();
		mTransform = GetOwner()->GetComponent<Transform>();

		mRigidBody = GetOwner()->GetComponent<Rigidbody>();
		mRigidBody->SetGround(true);

		// �ִϸ��̼� ����
		Vector2 Animationoffset = Vector2(0.f, -5.f);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Choice", Vector2(169.f, 355.f), Vector2(24.f, 33.f), Vector2(24.f, 0.f), 0.04f, 9, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Enter", Vector2(115.f, 466.f), Vector2(23.f, 31.f), Vector2(23.f, 0.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Enter", Vector2(459.f, 466.f), Vector2(23.f, 31.f), Vector2(-23.f, 0.f), 1.f, 1, Animationoffset);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Idle", Vector2(7.f, 4.f), Vector2(21.f, 25.f), Vector2(21.f, 0.f), 0.8f, 2, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Idle", Vector2(569.f, 4.f), Vector2(21.f, 25.f), Vector2(-21.f, 0.f), 0.8f, 2, Animationoffset);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Walk", Vector2(7.f, 136.f), Vector2(22.f, 27.f), Vector2(22.f, 0.f), 0.07f, 10, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Walk", Vector2(568.f, 136.f), Vector2(22.f, 27.f), Vector2(-22.f, 0.f), 0.07f, 10, Animationoffset);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Run", Vector2(0.f, 174.f), Vector2(25.f, 26.f), Vector2(25.f, 0.f), 0.043f, 8, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Run", Vector2(572.f, 174.f), Vector2(25.f, 26.f), Vector2(-25.f, 0.f), 0.043f, 8, Animationoffset);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Jump", Vector2(7.f, 100.f), Vector2(21.f, 28.f), Vector2(21.f, 0.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Jump", Vector2(569.f, 100.f), Vector2(21.f, 28.f), Vector2(-21.f, 0.f), 1.f, 1, Animationoffset);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Turn", Vector2(32.f, 103.f), Vector2(24.f, 25.f), Vector2(24.f, 0.f), 0.035f, 6, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Turn", Vector2(541.f, 103.f), Vector2(24.f, 25.f), Vector2(-24.f, 0.f), 0.035f, 6, Animationoffset);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Drop", Vector2(197.f, 102.f), Vector2(21.f, 26.f), Vector2(21.f, 0.f), 0.05f, 2, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Drop", Vector2(379.f, 102.f), Vector2(21.f, 26.f), Vector2(-21.f, 0.f), 0.05f, 2, Animationoffset);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Down", Vector2(7.f, 41.f), Vector2(25.f, 19.f), Vector2(25.f, 0.f), 0.8f, 2);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Down", Vector2(565.f, 41.f), Vector2(25.f, 19.f), Vector2(-25.f, 0.f), 0.8f, 2);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_FlyStart", Vector2(60.f, 207.f), Vector2(24.f, 27.f), Vector2(24.f, 0.f), 0.0667f, 3, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_FlyStart", Vector2(513.f, 207.f), Vector2(24.f, 27.f), Vector2(-24.f, 0.f), 0.0667f, 3, Animationoffset);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_FlyEnd", Vector2(108.f, 207.f), Vector2(24.f, 27.f), Vector2(-24.f, 0.f), 0.0667f, 3, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_FlyEnd", Vector2(465.f, 207.f), Vector2(24.f, 27.f), Vector2(24.f, 0.f), 0.0667f, 3, Animationoffset);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_FlyDown", Vector2(6.f, 280.f), Vector2(26.f, 31.f), Vector2(26.f, 0.f), 0.15f, 2, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_FlyDown", Vector2(565.f, 280.f), Vector2(26.f, 31.f), Vector2(-26.f, 0.f), 0.15f, 2, Animationoffset);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_FlyUp", Vector2(66.f, 280.f), Vector2(26.f, 31.f), Vector2(26.f, 0.f), 0.1f, 4, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_FlyUp", Vector2(505.f, 280.f), Vector2(26.f, 31.f), Vector2(-26.f, 0.f), 0.1f, 4, Animationoffset);

		mAnimator->CreateAnimation(IceKirby_Right, L"IceKirby_Right_Skill", Vector2(181.f, 573.f), Vector2(22.f, 27.f), Vector2(22.f, 0.f), 0.1f, 2, Animationoffset);
		mAnimator->CreateAnimation(IceKirby_Left, L"IceKirby_Left_Skill", Vector2(394.f, 573.f), Vector2(22.f, 27.f), Vector2(-22.f, 0.f), 0.1f, 2, Animationoffset);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"IceKirby_Right_Idle", true);

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

	void IceKirby::Update()
	{
		// ���� ����
		mDir = mTransform->GetDirection();

		// PlayerMode �� ���� ����ó�� 
		if (GetOwner()->GetPlayerMode() == ePlayerMode::LevelMode)
		{
			switch (mState)
			{
			case eIceKirbyState::Transformations:
				Transformations();
				break;
			case eIceKirbyState::Choice:
				Choice();
				break;
			case eIceKirbyState::Enter:
				Level_Enter();
				break;
			case eIceKirbyState::Idle:
				Level_Idle();
				break;
			case eIceKirbyState::Run:
				Level_Run();
				break;
			case eIceKirbyState::Fly_Up:
				Level_FlyUp();
				break;
			case eIceKirbyState::Drop:
				Level_Drop();
				break;
			default:
				break;
			}
		}
		else if (GetOwner()->GetPlayerMode() == ePlayerMode::PlayMode)
		{
			if (Input::GetKeyDown(eKeyCode::W)
				&& mState != eIceKirbyState::Skill)
			{
				eDefaultKirbyState state = eDefaultKirbyState::Idle;

				if(mState == eIceKirbyState::Idle)
					state = eDefaultKirbyState::Idle;
				else if (mState == eIceKirbyState::Walk)
					state = eDefaultKirbyState::Walk;
				else if (mState == eIceKirbyState::Run)
					state = eDefaultKirbyState::Run;
				else if (mState == eIceKirbyState::Down)
					state = eDefaultKirbyState::Down;
				else 
					state = eDefaultKirbyState::Drop;

				GetOwner()->ReleaseTransformations(state);

				AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Ice);
				object::ActiveSceneAddGameObject(eLayerType::AbilityItem, abilityStar);

				// ���º��� ���� ����
				return;
			}

			// �ȼ��浹 üũ
			CheckPixelCollision();

			// ����ó��
			switch (mState)
			{
			case eIceKirbyState::Transformations:
				Transformations();
				break;
			case eIceKirbyState::Idle:
				Idle();
				break;
			case eIceKirbyState::Walk:
				Walk();
				break;
			case eIceKirbyState::Run:
				Run();
				break;
			case eIceKirbyState::Jump:
				Jump();
				break;
			case eIceKirbyState::Turn:
				Turn();
				break;
			case eIceKirbyState::Drop:
				Drop();
				break;
			case eIceKirbyState::Down:
				Down();
				break;
			case eIceKirbyState::Fly_Start:
				Fly_Start();
				break;
			case eIceKirbyState::Fly_End:
				Fly_End();
				break;
			case eIceKirbyState::Fly_Down:
				Fly_Down();
				break;
			case eIceKirbyState::Fly_Up:
				Fly_Up();
				break;
			case eIceKirbyState::Skill:
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

	void IceKirby::Enter()
	{
		if (mDir == eDirection::RIGHT)
			mAnimator->PlayAnimation(L"IceKirby_Right_Enter", false);
		else
			mAnimator->PlayAnimation(L"IceKirby_Left_Enter", false);

		mState = eIceKirbyState::Transformations;
	}

	void IceKirby::Exit()
	{
	}

	void IceKirby::OnCollisionEnter(Collider* other)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (enemy == nullptr)
			return;

		// Ŀ�� �� ���� ����
		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

		GetOwner()->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	}

	void IceKirby::OnCollisionStay(Collider* other)
	{
	}

	void IceKirby::OnCollisionExit(Collider* other)
	{
	}

	bool IceKirby::IsTransformableCheck()
	{
		if (mState == eIceKirbyState::Skill)
			return false;

		return true;
	}

	void IceKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		// Ư�� ���¿��� �浹 ����
		if (mState == eIceKirbyState::Skill || mState == eIceKirbyState::Transformations)
			return;

		AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Ice);
		object::ActiveSceneAddGameObject(eLayerType::AbilityItem, abilityStar);

		GetOwner()->Damaged(DamageAmount);
		GetOwner()->PlayerTransformations(eAbilityType::Normal);

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

	void IceKirby::CheckPixelCollision()
	{
		// StageŸ�Կ����� �ȼ��ؽ��� �����ϱ�
		Texture* PixelTex = ResourceManager::Find<Texture>(L"Stage1_Pixel");

		if (PixelTex == nullptr)
			return;

		// Offset �ȼ� �»����ġ ����
		Vector2 offset = Vector2::Zero;

		std::wstring CurSceneName = SceneManager::GetActiveScene()->GetName();

		if (CurSceneName == L"Stage1Scene")
		{
			offset = Vector2::Zero;
		}
		else if (CurSceneName == L"Stage2Scene")
		{
			offset = Vector2(0, 347.f);
		}
		else if (CurSceneName == L"Stage3Scene")
		{
			offset = Vector2(0, 679.f);
		}
		else if (CurSceneName == L"Stage4Scene")
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
			if (!(mState == eIceKirbyState::Jump
				|| mState == eIceKirbyState::Fly_Up))
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

	void IceKirby::Choice()
	{
		// �ִϸ��̼�
		if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::RIGHT)) && !GetOwner()->GetLevelEnter())
		{
			mAnimator->PlayAnimation(L"IceKirby_Choice", false);
		}

		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			// ���� ù�����̶�� Enter�ִϸ��̼� ���
			if (GetOwner()->GetLevelEnter())
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"IceKirby_Right_Enter", false);
				else
					mAnimator->PlayAnimation(L"IceKirby_Left_Enter", false);

				mState = eIceKirbyState::Enter;
				GetOwner()->SetLevelEnter(false);
			}
			else
			{
				mAnimator->PlayAnimation(L"IceKirby_Right_Idle", true);
				mState = eIceKirbyState::Idle;
			}
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Enter", false);
			
			mState = eIceKirbyState::Enter;
		}
	}

	void IceKirby::Level_Enter()
	{
		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"IceKirby_Right_Idle", true);

			mState = eIceKirbyState::Idle;
		}
	}

	void IceKirby::Level_Idle()
	{
		if (Input::GetKeyDown(eKeyCode::UP)
			|| Input::GetKeyDown(eKeyCode::DOWN)
			|| Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			mAnimator->PlayAnimation(L"IceKirby_Choice", false);
			mState = eIceKirbyState::Choice;
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Enter", false);

			mState = eIceKirbyState::Enter;
		}
	}

	void IceKirby::Level_Run()
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

	void IceKirby::Level_FlyUp()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y -= 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void IceKirby::Level_Drop()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y += 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void IceKirby::Transformations()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Idle", true);

			mState = eIceKirbyState::Idle;
		}
	}

	void IceKirby::Idle()
	{
		// �ִϸ��̼� 

		// ���� ���� ���°� �ƴ϶�� Drop���� ���� ��Ż�濡���� ����ó���������
		if (!mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Drop", true);

			mState = eIceKirbyState::Drop;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"IceKirby_Right_Walk", true);
				mState = eIceKirbyState::Walk;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (!mbOnLeftStop)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"IceKirby_Left_Walk", true);
				mState = eIceKirbyState::Walk;
			}
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_Walk", true);
			mState = eIceKirbyState::Walk;
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"IceKirby_Right_Walk", true);
			mState = eIceKirbyState::Walk;
		}

		// Run
		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"IceKirby_Right_Run", true);
				mState = eIceKirbyState::Run;

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
				mAnimator->PlayAnimation(L"IceKirby_Left_Run", true);
				mState = eIceKirbyState::Run;

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
				mAnimator->PlayAnimation(L"IceKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Jump", false);

			mState = eIceKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Down", false);

			mState = eIceKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Skill", true);

			mState = eIceKirbyState::Skill;

			// ��ų ����
			mSkill = new IceKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);

			// ����� ���		
		}
	}

	void IceKirby::Walk()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Idle", true);

			mState = eIceKirbyState::Idle;
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
				mAnimator->PlayAnimation(L"IceKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Drop", true);

			mState = eIceKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Idle", true);

			mState = eIceKirbyState::Idle;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"IceKirby_Right_Walk", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_Walk", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"IceKirby_Right_Walk", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_Walk", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Jump", false);

			mState = eIceKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Down", false);

			mState = eIceKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Skill", true);

			mState = eIceKirbyState::Skill;

			// ��ų ����
			mSkill = new IceKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);


			// ����� ���		
		}
	}

	void IceKirby::Run()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Idle", true);

			mState = eIceKirbyState::Idle;

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
				mAnimator->PlayAnimation(L"IceKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Drop", true);

			mState = eIceKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Idle", true);

			mState = eIceKirbyState::Idle;
		}

		// Run
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"IceKirby_Right_Run", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_Run", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"IceKirby_Right_Run", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_Run", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Jump", false);

			mState = eIceKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Down", false);

			mState = eIceKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Skill", true);

			mState = eIceKirbyState::Skill;

			// ��ų ����
			mSkill = new IceKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);

			// ����� ���		
		}
	}

	void IceKirby::Jump()
	{
		// ���� �̵�
		static float KeyReleaseTime = 0.f;
		static float KeyPressdTime = 0.f;

		if (Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			KeyPressdTime += Time::DeltaTime();

			// ���� ���� �ð����� ���
			if (KeyPressdTime < 0.2f)
			{
				mRigidBody->AddForce(Vector2(0.f, -400.f));
			}

			// Ű�� ���� �ð��� �����ð��̻� ������ ���º���
			if (KeyPressdTime > 0.4f)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"IceKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"IceKirby_Left_Turn", false);

				mState = eIceKirbyState::Turn;

				KeyPressdTime = 0.f;
				KeyReleaseTime = 0.f;
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			}
		}

		if (!Input::GetKeyPressed(eKeyCode::A) && !Input::GetKeyPressed(eKeyCode::D))
		{
			KeyReleaseTime += Time::DeltaTime();

			// Ű�� ���ð��� �����ð��̻� ������ ���º���
			if (KeyReleaseTime > 0.125f)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"IceKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"IceKirby_Left_Turn", false);

				mState = eIceKirbyState::Turn;

				KeyPressdTime = 0.f;
				KeyReleaseTime = 0.f;
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
			mAnimator->PlayAnimation(L"IceKirby_Right_Jump", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_Jump", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"IceKirby_Right_Jump", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_Jump", true);
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Skill", true);

			mState = eIceKirbyState::Skill;

			// ��ų ����
			mSkill = new IceKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);

			// ����� ���		
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_FlyStart", false);

			mState = eIceKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
			KeyPressdTime = 0.f;
			KeyReleaseTime = 0.f;

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void IceKirby::Turn()
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
				mAnimator->PlayAnimation(L"IceKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Drop", true);

			TurnTime = 0.f;
			mState = eIceKirbyState::Drop;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Skill", true);

			mState = eIceKirbyState::Skill;

			// ��ų ����
			mSkill = new IceKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);

			// ����� ���		
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_FlyStart", false);

			TurnTime = 0.f;
			mState = eIceKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void IceKirby::Drop()
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
			mAnimator->PlayAnimation(L"IceKirby_Right_Drop", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_Drop", true);
		}

		// ������ȯ ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && mDir == eDirection::LEFT)
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"IceKirby_Right_Drop", true);
		}

		if (Input::GetKeyPressed(eKeyCode::LEFT) && mDir == eDirection::RIGHT)
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_Drop", true);
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Skill", true);

			mState = eIceKirbyState::Skill;

			// ��ų ����
			mSkill = new IceKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);


			// ����� ���		
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_FlyStart", false);

			mState = eIceKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
		}

		if (mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Idle", true);

			mState = eIceKirbyState::Idle;
			ResourceManager::Find<Sound>(L"LandSound")->Play(false);
		}
	}

	void IceKirby::Down()
	{
		// �ִϸ��̼�

		// �ݴ����Ű�� �������� ���� ��ȯ
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"IceKirby_Right_Down", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_Down", true);
		}

		// Ű�Է��̾����� Idle �� ����
		if (!Input::GetKeyPressed(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Idle", true);

			mState = eIceKirbyState::Idle;
		}
	}

	void IceKirby::Fly_Start()
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
				mAnimator->PlayAnimation(L"IceKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_FlyEnd", false);

			mState = eIceKirbyState::Fly_End;

			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);
		}

		// �ִϸ��̼��� ������ Fly Down ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_FlyDown", true);

			mState = eIceKirbyState::Fly_Down;
		}
	}

	void IceKirby::Fly_End()
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
				mAnimator->PlayAnimation(L"IceKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Drop", true);

			mState = eIceKirbyState::Drop;
		}
	}

	void IceKirby::Fly_Down()
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
			mAnimator->PlayAnimation(L"IceKirby_Right_FlyDown", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_FlyDown", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"IceKirby_Right_FlyDown", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_FlyDown", true);
		}


		// Fly Up
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_FlyUp", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_FlyUp", true);

			mState = eIceKirbyState::Fly_Up;
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
				mAnimator->PlayAnimation(L"IceKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_FlyEnd", false);

			mState = eIceKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			mRigidBody->SetLimitVelocity(Vector2(300.f, 300.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void IceKirby::Fly_Up()
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
			mAnimator->PlayAnimation(L"IceKirby_Right_FlyUp", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_FlyUp", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"IceKirby_Right_FlyUp", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"IceKirby_Left_FlyUp", true);
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
				mAnimator->PlayAnimation(L"IceKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_FlyDown", true);

			mState = eIceKirbyState::Fly_Down;
		}

		// Fly End
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_FlyEnd", false);

			mState = eIceKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			// ����� ���
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void IceKirby::Skill()
	{
		// Ű�Է��̾������ Idle �� ����
		if (!Input::GetKeyPressed(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"IceKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"IceKirby_Left_Idle", true);

			mState = eIceKirbyState::Idle;

			Destroy(mSkill);

			// ����� ����		
			ResourceManager::Find<Sound>(L"IceSkill_Sound")->Stop(true);
		}
	}
}