#include "syFireKirby.h"
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
#include "syFireKirby_Skill.h"
#include "syCollider.h"
#include "syAbilityStar.h"

namespace sy
{
	FireKirby::FireKirby(class Player* owner)
		: Kirby(owner)
		, mState(eFireKirbyState::Idle)
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

	FireKirby::~FireKirby()
	{
	}

	void FireKirby::Initialize()
	{
		// �ؽ��� �ε�
		Texture* FireKirby_Right = ResourceManager::Load<Texture>(L"FireKirby_Right_Tex", L"..\\Resources\\Kirby\\FireKirby\\FireKirby_Right.bmp");
		Texture* FireKirby_Left = ResourceManager::Load<Texture>(L"FireKirby_Left_Tex", L"..\\Resources\\Kirby\\FireKirby\\FireKirby_Left.bmp");

		// Player ���� ������� ������Ʈ ��������� ����
		mAnimator = GetOwner()->GetComponent<Animator>();
		mTransform = GetOwner()->GetComponent<Transform>();

		mRigidBody = GetOwner()->GetComponent<Rigidbody>();
		mRigidBody->SetGround(true);

		// �ִϸ��̼� ����
		Vector2 Animationoffset = Vector2(0.f, -7.f);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Choice", Vector2(187.f, 558.f), Vector2(28.f, 48.f), Vector2(28.f, 0.f), 0.03f, 12, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Enter", Vector2(368.f, 1153.f), Vector2(22.f, 29.f), Vector2(22.f, 0.f), 0.5f, 2, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Enter", Vector2(304.f, 1153.f), Vector2(22.f, 29.f), Vector2(-22.f, 0.f), 0.5f, 2, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Idle", Vector2(8.f, 4.f), Vector2(23.f, 32.f), Vector2(23.f, 0.f), 0.08f, 8, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Idle", Vector2(663.f, 4.f), Vector2(23.f, 32.f), Vector2(-23.f, 0.f), 0.08f, 8, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Walk", Vector2(7.f, 292.f), Vector2(25.f, 36.f), Vector2(25.f, 0.f), 0.035f, 20, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Walk", Vector2(662.f, 292.f), Vector2(25.f, 36.f), Vector2(-25.f, 0.f), 0.035f, 20, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Run", Vector2(0.f, 342.f), Vector2(48.f, 30.f), Vector2(48.f, 0.f), 0.043f, 8, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Run", Vector2(646.f, 342.f), Vector2(48.f, 30.f), Vector2(-48.f, 0.f), 0.043f, 8, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Jump", Vector2(0.f, 251.f), Vector2(24.f, 27.f), Vector2(24.f, 0.f), 0.2f, 2, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Jump", Vector2(670.f, 251.f), Vector2(24.f, 27.f), Vector2(-24.f, 0.f), 0.2f, 2, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Turn", Vector2(423.f, 251.f), Vector2(31.f, 29.f), Vector2(31.f, 0.f), 0.035f, 6, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Turn", Vector2(240.f, 251.f), Vector2(31.f, 29.f), Vector2(-31.f, 0.f), 0.035f, 6, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Drop", Vector2(239.f, 242.f), Vector2(22.f, 36.f), Vector2(22.f, 0.f), 0.05f, 2, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Drop", Vector2(433.f, 242.f), Vector2(22.f, 36.f), Vector2(-22.f, 0.f), 0.05f, 2, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Down", Vector2(230.f, 10.f), Vector2(27.f, 26.f), Vector2(27.f, 0.f), 0.08f, 8);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Down", Vector2(437.f, 10.f), Vector2(27.f, 26.f), Vector2(-27.f, 0.f), 0.08f, 8);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_FlyStart", Vector2(62.f, 382.f), Vector2(26.f, 31.f), Vector2(26.f, 0.f), 0.0667f, 3, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_FlyStart", Vector2(606.f, 382.f), Vector2(26.f, 31.f), Vector2(-26.f, 0.f), 0.0667f, 3, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_FlyEnd", Vector2(114.f, 382.f), Vector2(26.f, 31.f), Vector2(-26.f, 0.f), 0.0667f, 3, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_FlyEnd", Vector2(554.f, 382.f), Vector2(26.f, 31.f), Vector2(26.f, 0.f), 0.0667f, 3, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_FlyDown", Vector2(7.f, 520.f), Vector2(26.f, 41.f), Vector2(26.f, 0.f), 0.05f, 6, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_FlyDown", Vector2(661.f, 520.f), Vector2(26.f, 41.f), Vector2(-26.f, 0.f), 0.05f, 6, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_FlyUp", Vector2(7.f, 469.f), Vector2(26.f, 41.f), Vector2(26.f, 0.f), 0.05f, 8, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_FlyUp", Vector2(661.f, 469.f), Vector2(26.f, 41.f), Vector2(-26.f, 0.f), 0.05f, 8, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_Skill", Vector2(187.f, 1109.f), Vector2(31.f, 29.f), Vector2(31.f, 0.f), 0.05f, 4, Animationoffset);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_Skill", Vector2(476.f, 1109.f), Vector2(31.f, 29.f), Vector2(-31.f, 0.f), 0.05f, 4, Animationoffset);

		mAnimator->CreateAnimation(FireKirby_Right, L"FireKirby_Right_DashSkill", Vector2(0.f, 836.f), Vector2(59.f, 38.f), Vector2(59.f, 0.f), 0.03f, 9);
		mAnimator->CreateAnimation(FireKirby_Left, L"FireKirby_Left_DashSkill", Vector2(635.f, 836.f), Vector2(59.f, 38.f), Vector2(-59.f, 0.f), 0.043f, 9);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"FireKirby_Right_Idle", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"FlySound", L"..\\Resources\\Sound\\Effect\\Fly.wav");
		ResourceManager::Load<Sound>(L"JumpSound", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		ResourceManager::Load<Sound>(L"LandSound", L"..\\Resources\\Sound\\Effect\\Land.wav");
		ResourceManager::Load<Sound>(L"RunSound", L"..\\Resources\\Sound\\Effect\\Run.wav");
		ResourceManager::Load<Sound>(L"ClickSound", L"..\\Resources\\Sound\\Effect\\Click.wav");
		ResourceManager::Load<Sound>(L"FireKirby_Right_DashSkill_Sound", L"..\\Resources\\Sound\\Effect\\NinjaCharge.wav");

		ResourceManager::Find<Sound>(L"JumpSound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"FlySound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"LandSound")->SetVolume(10.f);
		ResourceManager::Find<Sound>(L"RunSound")->SetVolume(100.f);
	}

	void FireKirby::Update()
	{
		// ���� ����
		mDir = mTransform->GetDirection();

		// PlayerMode �� ���� ����ó�� 
		if (GetOwner()->GetPlayerMode() == ePlayerMode::LevelMode)
		{
			switch (mState)
			{
			case eFireKirbyState::Transformations:
				Transformations();
				break;
			case eFireKirbyState::Choice:
				Choice();
				break;
			case eFireKirbyState::Enter:
				Level_Enter();
				break;
			case eFireKirbyState::Idle:
				Level_Idle();
				break;
			case eFireKirbyState::Run:
				Level_Run();
				break;
			case eFireKirbyState::Fly_Up:
				Level_FlyUp();
				break;
			case eFireKirbyState::Drop:
				Level_Drop();
				break;
			default:
				break;
			}
		}
		else if (GetOwner()->GetPlayerMode() == ePlayerMode::PlayMode)
		{
			if (Input::GetKeyDown(eKeyCode::W) 
				&& mState != eFireKirbyState::Skill && mState != eFireKirbyState::DASH_Skill)
			{
				eDefaultKirbyState state = eDefaultKirbyState::Idle;

				if (mState == eFireKirbyState::Idle)
					state = eDefaultKirbyState::Idle;
				else if (mState == eFireKirbyState::Walk)
					state = eDefaultKirbyState::Walk;
				else if (mState == eFireKirbyState::Run)
					state = eDefaultKirbyState::Run;
				else if (mState == eFireKirbyState::Down)
					state = eDefaultKirbyState::Down;
				else
					state = eDefaultKirbyState::Drop;

				GetOwner()->ReleaseTransformations(state);

				AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Fire);
				object::ActiveSceneAddGameObject(eLayerType::AbilityItem, abilityStar);

				// ���º��� ���� ����
				return;
			}

			// �ȼ��浹 üũ
			CheckPixelCollision();

			// ����ó��
			switch (mState)
			{
			case eFireKirbyState::Transformations:
				Transformations();
				break;
			case eFireKirbyState::Idle:
				Idle();
				break;
			case eFireKirbyState::Walk:
				Walk();
				break;
			case eFireKirbyState::Run:
				Run();
				break;
			case eFireKirbyState::Jump:
				Jump();
				break;
			case eFireKirbyState::Turn:
				Turn();
				break;
			case eFireKirbyState::Drop:
				Drop();
				break;
			case eFireKirbyState::Down:
				Down();
				break;
			case eFireKirbyState::Fly_Start:
				Fly_Start();
				break;
			case eFireKirbyState::Fly_End:
				Fly_End();
				break;
			case eFireKirbyState::Fly_Down:
				Fly_Down();
				break;
			case eFireKirbyState::Fly_Up:
				Fly_Up();
				break;
			case eFireKirbyState::Skill:
				Skill();
				break;
			case eFireKirbyState::DASH_Skill:
				DASH_Skill();
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

	void FireKirby::Enter()
	{
		if (mDir == eDirection::RIGHT)
			mAnimator->PlayAnimation(L"FireKirby_Right_Enter", false);
		else
			mAnimator->PlayAnimation(L"FireKirby_Left_Enter", false);

		mState = eFireKirbyState::Transformations;
	}

	void FireKirby::Exit()
	{
		// Dash_Skill���� ������ Collider Size ���󺹱�
		Collider* col = GetOwner()->GetComponent<Collider>();
		col->SetSize(Vector2(15.f, 15.f));	
	}

	void FireKirby::OnCollisionEnter(Collider* other)
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

	void FireKirby::OnCollisionStay(Collider* other)
	{
	}

	void FireKirby::OnCollisionExit(Collider* other)
	{
	}

	bool FireKirby::IsTransformableCheck()
	{
		if (mState == eFireKirbyState::Skill || mState == eFireKirbyState::DASH_Skill)
			return false;

		return true;
	}

	void FireKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		// Ư�� ���¿��� �浹 ����
		if (mState == eFireKirbyState::Skill || mState == eFireKirbyState::DASH_Skill || mState == eFireKirbyState::Transformations)
			return;

		AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Fire);
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

	void FireKirby::CheckPixelCollision()
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
			if (!(mState == eFireKirbyState::Jump
				|| mState == eFireKirbyState::Fly_Up))
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

	void FireKirby::Choice()
	{
		// �ִϸ��̼�
		if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::RIGHT)) && !GetOwner()->GetLevelEnter())
		{
			mAnimator->PlayAnimation(L"FireKirby_Choice", false);
		}

		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			// ���� ù�����̶�� Enter�ִϸ��̼� ���
			if (GetOwner()->GetLevelEnter())
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"FireKirby_Right_Enter", false);
				else
					mAnimator->PlayAnimation(L"FireKirby_Left_Enter", false);

				mState = eFireKirbyState::Enter;
				GetOwner()->SetLevelEnter(false);
			}
			else
			{
				mAnimator->PlayAnimation(L"FireKirby_Right_Idle", true);
				mState = eFireKirbyState::Idle;
			}
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Enter", false);

			mState = eFireKirbyState::Enter;
		}
	}

	void FireKirby::Level_Enter()
	{
		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"FireKirby_Right_Idle", true);

			mState = eFireKirbyState::Idle;
		}
	}

	void FireKirby::Level_Idle()
	{
		if (Input::GetKeyDown(eKeyCode::UP)
			|| Input::GetKeyDown(eKeyCode::DOWN)
			|| Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			mAnimator->PlayAnimation(L"FireKirby_Choice", false);
			mState = eFireKirbyState::Choice;
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Enter", false);

			mState = eFireKirbyState::Enter;
		}
	}

	void FireKirby::Level_Run()
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

	void FireKirby::Level_FlyUp()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y -= 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void FireKirby::Level_Drop()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y += 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void FireKirby::Transformations()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Idle", true);

			mState = eFireKirbyState::Idle;
		}
	}

	void FireKirby::Idle()
	{
		// �ִϸ��̼� 

		// ���� ���� ���°� �ƴ϶�� Drop���� ���� ��Ż�濡���� ����ó���������
		if (!mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Drop", true);

			mState = eFireKirbyState::Drop;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"FireKirby_Right_Walk", true);
				mState = eFireKirbyState::Walk;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (!mbOnLeftStop)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"FireKirby_Left_Walk", true);
				mState = eFireKirbyState::Walk;
			}
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_Walk", true);
			mState = eFireKirbyState::Walk;
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_Walk", true);
			mState = eFireKirbyState::Walk;
		}

		// Run
		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"FireKirby_Right_Run", true);
				mState = eFireKirbyState::Run;

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
				mAnimator->PlayAnimation(L"FireKirby_Left_Run", true);
				mState = eFireKirbyState::Run;

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
				mAnimator->PlayAnimation(L"FireKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Jump", false);

			mState = eFireKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Down", false);

			mState = eFireKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Skill", true);

			mState = eFireKirbyState::Skill;

			// ��ų ����
			mSkill = new FireKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);

			// ����� ���		
		}
	}

	void FireKirby::Walk()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Idle", true);

			mState = eFireKirbyState::Idle;
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
				mAnimator->PlayAnimation(L"FireKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Drop", true);

			mState = eFireKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Idle", true);

			mState = eFireKirbyState::Idle;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_Walk", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_Walk", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_Walk", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_Walk", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Jump", false);

			mState = eFireKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Down", false);

			mState = eFireKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Skill", true);

			mState = eFireKirbyState::Skill;

			// ��ų ����
			mSkill = new FireKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);


			// ����� ���		
		}
	}

	void FireKirby::Run()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Idle", true);

			mState = eFireKirbyState::Idle;

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
				mAnimator->PlayAnimation(L"FireKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Drop", true);

			mState = eFireKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Idle", true);

			mState = eFireKirbyState::Idle;
		}

		// Run
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_Run", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_Run", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_Run", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_Run", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Jump", false);

			mState = eFireKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Down", false);

			mState = eFireKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Skill", true);

			mState = eFireKirbyState::Skill;

			// ��ų ����
			mSkill = new FireKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);

			// ����� ���		
		}

		// DASH_Skill
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::S))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_DashSkill", true);
			mState = eFireKirbyState::DASH_Skill;

			// ����� ���		
			ResourceManager::Find<Sound>(L"FireKirby_Right_DashSkill_Sound")->Play(false);
		}

		// DASH_Skill
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::S))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_DashSkill", true);
			mState = eFireKirbyState::DASH_Skill;

			// ����� ���		
			ResourceManager::Find<Sound>(L"FireKirby_Right_DashSkill_Sound")->Play(false);
		}
	}

	void FireKirby::Jump()
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
					mAnimator->PlayAnimation(L"FireKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"FireKirby_Left_Turn", false);

				mState = eFireKirbyState::Turn;

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
					mAnimator->PlayAnimation(L"FireKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"FireKirby_Left_Turn", false);

				mState = eFireKirbyState::Turn;

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
			mAnimator->PlayAnimation(L"FireKirby_Right_Jump", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_Jump", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_Jump", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_Jump", true);
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Skill", true);

			mState = eFireKirbyState::Skill;

			// ��ų ����
			mSkill = new FireKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);

			// ����� ���		
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_FlyStart", false);

			mState = eFireKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
			KeyPressdTime = 0.f;
			KeyReleaseTime = 0.f;

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}

		// DASH_Skill
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::S))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_DashSkill", true);
			mState = eFireKirbyState::DASH_Skill;

			// ����� ���		
			ResourceManager::Find<Sound>(L"FireKirby_Right_DashSkill_Sound")->Play(false);
		}

		// DASH_Skill
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::S))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_DashSkill", true);
			mState = eFireKirbyState::DASH_Skill;

			// ����� ���		
			ResourceManager::Find<Sound>(L"FireKirby_Right_DashSkill_Sound")->Play(false);
		}
	}

	void FireKirby::Turn()
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
				mAnimator->PlayAnimation(L"FireKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Drop", true);

			TurnTime = 0.f;
			mState = eFireKirbyState::Drop;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Skill", true);

			mState = eFireKirbyState::Skill;

			// ��ų ����
			mSkill = new FireKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);

			// ����� ���		
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_FlyStart", false);

			TurnTime = 0.f;
			mState = eFireKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}

		// DASH_Skill
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::S))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_DashSkill", true);
			mState = eFireKirbyState::DASH_Skill;

			// ����� ���		
			ResourceManager::Find<Sound>(L"FireKirby_Right_DashSkill_Sound")->Play(false);
		}

		// DASH_Skill
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::S))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_DashSkill", true);
			mState = eFireKirbyState::DASH_Skill;

			// ����� ���		
			ResourceManager::Find<Sound>(L"FireKirby_Right_DashSkill_Sound")->Play(false);
		}
	}

	void FireKirby::Drop()
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
			mAnimator->PlayAnimation(L"FireKirby_Right_Drop", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_Drop", true);
		}

		// ������ȯ ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && mDir == eDirection::LEFT)
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_Drop", true);
		}

		if (Input::GetKeyPressed(eKeyCode::LEFT) && mDir == eDirection::RIGHT)
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_Drop", true);
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Skill", true);

			mState = eFireKirbyState::Skill;

			// ��ų ����
			mSkill = new FireKirby_Skill(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, mSkill);


			// ����� ���		
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_FlyStart", false);

			mState = eFireKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
		}

		if (mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Idle", true);

			mState = eFireKirbyState::Idle;
			ResourceManager::Find<Sound>(L"LandSound")->Play(false);
		}

		// DASH_Skill
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::S))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_DashSkill", true);
			mState = eFireKirbyState::DASH_Skill;

			// ����� ���		
			ResourceManager::Find<Sound>(L"FireKirby_Right_DashSkill_Sound")->Play(false);
		}

		// DASH_Skill
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::S))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_DashSkill", true);
			mState = eFireKirbyState::DASH_Skill;

			// ����� ���		
			ResourceManager::Find<Sound>(L"FireKirby_Right_DashSkill_Sound")->Play(false);
		}
	}

	void FireKirby::Down()
	{
		// �ִϸ��̼�

		// �ݴ����Ű�� �������� ���� ��ȯ
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_Down", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_Down", true);
		}

		// Ű�Է��̾����� Idle �� ����
		if (!Input::GetKeyPressed(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Idle", true);

			mState = eFireKirbyState::Idle;
		}
	}

	void FireKirby::Fly_Start()
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
				mAnimator->PlayAnimation(L"FireKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_FlyEnd", false);

			mState = eFireKirbyState::Fly_End;

			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);
		}

		// �ִϸ��̼��� ������ Fly Down ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_FlyDown", true);

			mState = eFireKirbyState::Fly_Down;
		}
	}

	void FireKirby::Fly_End()
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
				mAnimator->PlayAnimation(L"FireKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Drop", true);

			mState = eFireKirbyState::Drop;
		}
	}

	void FireKirby::Fly_Down()
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
			mAnimator->PlayAnimation(L"FireKirby_Right_FlyDown", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_FlyDown", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_FlyDown", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_FlyDown", true);
		}


		// Fly Up
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_FlyUp", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_FlyUp", true);

			mState = eFireKirbyState::Fly_Up;
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
				mAnimator->PlayAnimation(L"FireKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_FlyEnd", false);

			mState = eFireKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			mRigidBody->SetLimitVelocity(Vector2(300.f, 300.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void FireKirby::Fly_Up()
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
			mAnimator->PlayAnimation(L"FireKirby_Right_FlyUp", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_FlyUp", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"FireKirby_Right_FlyUp", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"FireKirby_Left_FlyUp", true);
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
				mAnimator->PlayAnimation(L"FireKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_FlyDown", true);

			mState = eFireKirbyState::Fly_Down;
		}

		// Fly End
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_FlyEnd", false);

			mState = eFireKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			// ����� ���
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void FireKirby::Skill()
	{
		// Ű�Է��̾������ Idle �� ����
		if (!Input::GetKeyPressed(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Idle", true);

			mState = eFireKirbyState::Idle;

			Destroy(mSkill);

			// ����� ����			
			ResourceManager::Find<Sound>(L"FireSkill_Sound")->Stop(true);
		}
	}

	void FireKirby::DASH_Skill()
	{
		mRigidBody->SetGround(true);
		Collider* col = GetOwner()->GetComponent<Collider>();
		col->SetSize(Vector2(59.f, 25.f));

		// Stop ���°� �ƴѰ�쿡�� �̵�
		if (!(mbOnLeftStop || mbOnRightStop))
		{
			// �¿� �̵�
			Vector2 pos = mTransform->GetPosition();

			if (mDir == eDirection::RIGHT)
				pos.x += 200.f * Time::DeltaTime();
			else
				pos.x -= 200.f * Time::DeltaTime();			

			mTransform->SetPosition(pos);
		}

		static float Duration = 0.f;
		Duration += Time::DeltaTime();

		// ���ӽð��� ������ ���� ����
		if (Duration > 1.5f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"FireKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"FireKirby_Left_Drop", true);

			Duration = 0.f;
			mState = eFireKirbyState::Drop;
			mRigidBody->SetGround(false);
			col->SetSize(Vector2(15.f, 15.f));
		}
	}
}