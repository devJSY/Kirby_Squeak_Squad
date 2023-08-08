#include "syTornadoKirby.h"
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

namespace sy
{
	TornadoKirby::TornadoKirby(class Player* owner)
		: Kirby(owner)
		, mState(eTornadoKirbyState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::RIGHT)
		, mbOnLeftStop(false)
		, mbOnRightStop(false)
		, mbTopStop(false)
		, mbOnSlope(false)
	{
	}

	TornadoKirby::~TornadoKirby()
	{
	}

	void TornadoKirby::Initialize()
	{
		// �ؽ��� �ε�
		Texture* TornadoKirby_Right = ResourceManager::Load<Texture>(L"TornadoKirby_Right_Tex", L"..\\Resources\\Kirby\\TornadoKirby\\TornadoKirby_Right.bmp");
		Texture* TornadoKirby_Left = ResourceManager::Load<Texture>(L"TornadoKirby_Left_Tex", L"..\\Resources\\Kirby\\TornadoKirby\\TornadoKirby_Left.bmp");

		// Player ���� ������� ������Ʈ ��������� ����
		mAnimator = GetOwner()->GetComponent<Animator>();
		mTransform = GetOwner()->GetComponent<Transform>();

		mRigidBody = GetOwner()->GetComponent<Rigidbody>();
		mRigidBody->SetGround(true);

		// �ִϸ��̼� ����
		Vector2 Animationoffset = Vector2(0.f, -5.f);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Choice", Vector2(223.f, 541.f), Vector2(25.f, 50.f), Vector2(25.f, 0.f), 0.03f, 12, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Enter", Vector2(396.f, 1064.f), Vector2(24.f, 30.f), Vector2(24.f, 0.f), 0.5f, 2, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Enter", Vector2(280.f, 1064.f), Vector2(24.f, 30.f), Vector2(-24.f, 0.f), 0.5f, 2, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Idle", Vector2(8.f, 8.f), Vector2(28.f, 28.f), Vector2(28.f, 0.f), 0.05f, 4, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Idle", Vector2(664.f, 8.f), Vector2(28.f, 28.f), Vector2(-28.f, 0.f), 0.05f, 4, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Walk", Vector2(7.f, 302.f), Vector2(28.f, 30.f), Vector2(28.f, 0.f), 0.035f, 20, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Walk", Vector2(665.f, 302.f), Vector2(28.f, 30.f), Vector2(-28.f, 0.f), 0.035f, 20, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Run", Vector2(0.f, 347.f), Vector2(33.f, 28.f), Vector2(33.f, 0.f), 0.043f, 8, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Run", Vector2(667.f, 347.f), Vector2(33.f, 28.f), Vector2(-33.f, 0.f), 0.043f, 8, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Jump", Vector2(0.f, 259.f), Vector2(25.f, 28.f), Vector2(25.f, 0.f), 0.2f, 2, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Jump", Vector2(675.f, 259.f), Vector2(25.f, 28.f), Vector2(-25.f, 0.f), 0.2f, 2, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Turn", Vector2(63.f, 257.f), Vector2(25.f, 30.f), Vector2(25.f, 0.f), 0.035f, 6, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Turn", Vector2(612.f, 257.f), Vector2(25.f, 30.f), Vector2(-25.f, 0.f), 0.035f, 6, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Drop", Vector2(235.f, 255.f), Vector2(28.f, 32.f), Vector2(28.f, 0.f), 0.05f, 2, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Drop", Vector2(437.f, 255.f), Vector2(28.f, 32.f), Vector2(-28.f, 0.f), 0.05f, 2, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Down", Vector2(250.f, 14.f), Vector2(27.f, 22.f), Vector2(27.f, 0.f), 0.15f, 4);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Down", Vector2(423.f, 14.f), Vector2(27.f, 22.f), Vector2(-27.f, 0.f), 0.15f, 4);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_FlyStart", Vector2(67.f, 382.f), Vector2(29.f, 31.f), Vector2(29.f, 0.f), 0.0667f, 3, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_FlyStart", Vector2(604.f, 382.f), Vector2(29.f, 31.f), Vector2(-29.f, 0.f), 0.0667f, 3, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_FlyEnd", Vector2(125.f, 382.f), Vector2(29.f, 31.f), Vector2(-29.f, 0.f), 0.0667f, 3, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_FlyEnd", Vector2(546.f, 382.f), Vector2(29.f, 31.f), Vector2(29.f, 0.f), 0.0667f, 3, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_FlyUp", Vector2(0.f, 468.f), Vector2(27.f, 35.f), Vector2(27.f, 0.f), 0.05f, 8, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_FlyUp", Vector2(673.f, 468.f), Vector2(27.f, 35.f), Vector2(-27.f, 0.f), 0.05f, 8, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_FlyDown", Vector2(0.f, 509.f), Vector2(27.f, 37.f), Vector2(27.f, 0.f), 0.05f, 6, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_FlyDown", Vector2(673.f, 509.f), Vector2(27.f, 37.f), Vector2(-27.f, 0.f), 0.05f, 6, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_SkillEnter", Vector2(0.f, 1145.f), Vector2(32.f, 32.f), Vector2(32.f, 0.f), 0.03f, 12, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_SkillEnter", Vector2(668.f, 1145.f), Vector2(32.f, 32.f), Vector2(-32.f, 0.f), 0.03f, 12, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Right_Skill", Vector2(0.f, 1189.f), Vector2(34.f, 28.f), Vector2(34.f, 0.f), 0.04f, 8, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Left_Skill", Vector2(666.f, 1189.f), Vector2(34.f, 28.f), Vector2(-34.f, 0.f), 0.04f, 8, Animationoffset);

		mAnimator->CreateAnimation(TornadoKirby_Left, L"TornadoKirby_Right_SkillExit", Vector2(316.f, 1145.f), Vector2(32.f, 32.f), Vector2(32.f, 0.f), 0.03f, 12, Animationoffset);
		mAnimator->CreateAnimation(TornadoKirby_Right, L"TornadoKirby_Left_SkillExit", Vector2(352.f, 1145.f), Vector2(32.f, 32.f), Vector2(-32.f, 0.f), 0.03f, 12, Animationoffset);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"TornadoKirby_Right_Idle", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"FlySound", L"..\\Resources\\Sound\\Effect\\Fly.wav");
		ResourceManager::Load<Sound>(L"JumpSound", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		ResourceManager::Load<Sound>(L"LandSound", L"..\\Resources\\Sound\\Effect\\Land.wav");
		ResourceManager::Load<Sound>(L"RunSound", L"..\\Resources\\Sound\\Effect\\Run.wav");
		ResourceManager::Load<Sound>(L"ClickSound", L"..\\Resources\\Sound\\Effect\\Click.wav");
		ResourceManager::Load<Sound>(L"TornadoSkill_Sound", L"..\\Resources\\Sound\\Effect\\TornadoSkill.wav");

		ResourceManager::Find<Sound>(L"JumpSound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"FlySound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"LandSound")->SetVolume(10.f);
		ResourceManager::Find<Sound>(L"RunSound")->SetVolume(100.f);
	}

	void TornadoKirby::Update()
	{
		// ���� ����
		mDir = mTransform->GetDirection();

		// PlayerMode �� ���� ����ó�� 
		if (GetOwner()->GetPlayerMode() == ePlayerMode::LevelMode)
		{
			switch (mState)
			{
			case eTornadoKirbyState::Transformations:
				Transformations();
				break;
			case eTornadoKirbyState::Choice:
				Choice();
				break;
			case eTornadoKirbyState::Enter:
				Level_Enter();
				break;
			case eTornadoKirbyState::Idle:
				Level_Idle();
				break;
			case eTornadoKirbyState::Run:
				Level_Run();
				break;
			case eTornadoKirbyState::Fly_Up:
				Level_FlyUp();
				break;
			case eTornadoKirbyState::Drop:
				Level_Drop();
				break;
			default:
				break;
			}
		}
		else if (GetOwner()->GetPlayerMode() == ePlayerMode::PlayMode)
		{
			if (Input::GetKeyDown(eKeyCode::W) 
				&& mState != eTornadoKirbyState::Skill)
			{
				eDefaultKirbyState state = eDefaultKirbyState::Idle;

				if (mState == eTornadoKirbyState::Idle)
					state = eDefaultKirbyState::Idle;
				else if (mState == eTornadoKirbyState::Walk)
					state = eDefaultKirbyState::Walk;
				else if (mState == eTornadoKirbyState::Run)
					state = eDefaultKirbyState::Run;
				else if (mState == eTornadoKirbyState::Down)
					state = eDefaultKirbyState::Down;
				else
					state = eDefaultKirbyState::Drop;

				GetOwner()->ReleaseTransformations(state);

				AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Tornado);
				object::ActiveSceneAddGameObject(eLayerType::AbilityItem, abilityStar);

				// ���º��� ���� ����
				return;
			}

			// �ȼ��浹 üũ
			CheckPixelCollision();

			// ����ó��
			switch (mState)
			{
			case eTornadoKirbyState::Transformations:
				Transformations();
				break;
			case eTornadoKirbyState::Idle:
				Idle();
				break;
			case eTornadoKirbyState::Walk:
				Walk();
				break;
			case eTornadoKirbyState::Run:
				Run();
				break;
			case eTornadoKirbyState::Jump:
				Jump();
				break;
			case eTornadoKirbyState::Turn:
				Turn();
				break;
			case eTornadoKirbyState::Drop:
				Drop();
				break;
			case eTornadoKirbyState::Down:
				Down();
				break;
			case eTornadoKirbyState::Fly_Start:
				Fly_Start();
				break;
			case eTornadoKirbyState::Fly_End:
				Fly_End();
				break;
			case eTornadoKirbyState::Fly_Down:
				Fly_Down();
				break;
			case eTornadoKirbyState::Fly_Up:
				Fly_Up();
				break;
			case eTornadoKirbyState::Skill_Enter:
				Skill_Enter();
				break;
			case eTornadoKirbyState::Skill:
				Skill();
				break;
			case eTornadoKirbyState::Skill_Exit:
				Skill_Exit();
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

	void TornadoKirby::Enter()
	{
		if (mDir == eDirection::RIGHT)
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Enter", false);
		else
			mAnimator->PlayAnimation(L"TornadoKirby_Left_Enter", false);

		mState = eTornadoKirbyState::Transformations;
	}

	void TornadoKirby::Exit()
	{
		// Skill ���� ������ Limit ���󺹱�
		mRigidBody->SetLimitVelocity(Vector2(300.f, 300.f));
	}

	void TornadoKirby::OnCollisionEnter(Collider* other)
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

	void TornadoKirby::OnCollisionStay(Collider* other)
	{
	}

	void TornadoKirby::OnCollisionExit(Collider* other)
	{
	}

	bool TornadoKirby::IsTransformableCheck()
	{
		if (mState == eTornadoKirbyState::Skill_Enter || mState == eTornadoKirbyState::Skill || mState == eTornadoKirbyState::Skill_Exit)
			return false;

		return true;
	}

	void TornadoKirby::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		// Ư�� ���¿��� �浹 ����
		if (mState == eTornadoKirbyState::Skill_Enter 
			|| mState == eTornadoKirbyState::Skill 
			|| mState == eTornadoKirbyState::Skill_Exit
			|| mState == eTornadoKirbyState::Transformations)
			return;

		AbilityStar* abilityStar = new AbilityStar(GetOwner(), eAbilityType::Tornado);
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

	void TornadoKirby::CheckPixelCollision()
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
			if (!(mState == eTornadoKirbyState::Jump
				|| mState == eTornadoKirbyState::Fly_Up))
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

	void TornadoKirby::Choice()
	{
		// �ִϸ��̼�
		if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::RIGHT)) && !GetOwner()->GetLevelEnter())
		{
			mAnimator->PlayAnimation(L"TornadoKirby_Choice", false);
		}

		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			// ���� ù�����̶�� Enter�ִϸ��̼� ���
			if (GetOwner()->GetLevelEnter())
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"TornadoKirby_Right_Enter", false);
				else
					mAnimator->PlayAnimation(L"TornadoKirby_Left_Enter", false);

				mState = eTornadoKirbyState::Enter;
				GetOwner()->SetLevelEnter(false);
			}
			else
			{
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Idle", true);
				mState = eTornadoKirbyState::Idle;
			}
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Enter", false);

			mState = eTornadoKirbyState::Enter;
		}
	}

	void TornadoKirby::Level_Enter()
	{
		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Idle", true);

			mState = eTornadoKirbyState::Idle;
		}
	}

	void TornadoKirby::Level_Idle()
	{
		if (Input::GetKeyDown(eKeyCode::UP)
			|| Input::GetKeyDown(eKeyCode::DOWN)
			|| Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			mAnimator->PlayAnimation(L"TornadoKirby_Choice", false);
			mState = eTornadoKirbyState::Choice;
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Enter", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Enter", false);

			mState = eTornadoKirbyState::Enter;
		}
	}

	void TornadoKirby::Level_Run()
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

	void TornadoKirby::Level_FlyUp()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y -= 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void TornadoKirby::Level_Drop()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y += 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void TornadoKirby::Transformations()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Idle", true);

			mState = eTornadoKirbyState::Idle;
		}
	}

	void TornadoKirby::Idle()
	{
		// �ִϸ��̼� 

		// ���� ���� ���°� �ƴ϶�� Drop���� ���� ��Ż�濡���� ����ó���������
		if (!mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Drop", true);

			mState = eTornadoKirbyState::Drop;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Walk", true);
				mState = eTornadoKirbyState::Walk;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (!mbOnLeftStop)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Walk", true);
				mState = eTornadoKirbyState::Walk;
			}
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_Walk", true);
			mState = eTornadoKirbyState::Walk;
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Walk", true);
			mState = eTornadoKirbyState::Walk;
		}

		// Run
		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Run", true);
				mState = eTornadoKirbyState::Run;

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
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Run", true);
				mState = eTornadoKirbyState::Run;

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
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Jump", false);

			mState = eTornadoKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Down", false);

			mState = eTornadoKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			mState = eTornadoKirbyState::Skill_Enter;

			// ����� ���		
			ResourceManager::Find<Sound>(L"TornadoSkill_Sound")->Play(true);
		}
	}

	void TornadoKirby::Walk()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Idle", true);

			mState = eTornadoKirbyState::Idle;
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
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Drop", true);

			mState = eTornadoKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Idle", true);

			mState = eTornadoKirbyState::Idle;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Walk", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_Walk", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Walk", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_Walk", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Jump", false);

			mState = eTornadoKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Down", false);

			mState = eTornadoKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			mState = eTornadoKirbyState::Skill_Enter;

			// ����� ���		
			ResourceManager::Find<Sound>(L"TornadoSkill_Sound")->Play(true);
		}
	}

	void TornadoKirby::Run()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Idle", true);

			mState = eTornadoKirbyState::Idle;

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
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Drop", true);

			mState = eTornadoKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Idle", true);

			mState = eTornadoKirbyState::Idle;
		}

		// Run
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Run", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_Run", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Run", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_Run", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Jump", false);

			mState = eTornadoKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Down", false);

			mState = eTornadoKirbyState::Down;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			mState = eTornadoKirbyState::Skill_Enter;

			// ����� ���		
			ResourceManager::Find<Sound>(L"TornadoSkill_Sound")->Play(true);
		}
	}

	void TornadoKirby::Jump()
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
					mAnimator->PlayAnimation(L"TornadoKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"TornadoKirby_Left_Turn", false);

				mState = eTornadoKirbyState::Turn;

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
					mAnimator->PlayAnimation(L"TornadoKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"TornadoKirby_Left_Turn", false);

				mState = eTornadoKirbyState::Turn;

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
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Jump", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_Jump", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Jump", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_Jump", true);
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			mState = eTornadoKirbyState::Skill_Enter;

			// ����� ���		
			ResourceManager::Find<Sound>(L"TornadoSkill_Sound")->Play(true);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyStart", false);

			mState = eTornadoKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
			KeyPressdTime = 0.f;
			KeyReleaseTime = 0.f;

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void TornadoKirby::Turn()
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
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Drop", true);

			TurnTime = 0.f;
			mState = eTornadoKirbyState::Drop;
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			mState = eTornadoKirbyState::Skill_Enter;

			// ����� ���		
			ResourceManager::Find<Sound>(L"TornadoSkill_Sound")->Play(true);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyStart", false);

			TurnTime = 0.f;
			mState = eTornadoKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void TornadoKirby::Drop()
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
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Drop", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_Drop", true);
		}

		// ������ȯ ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && mDir == eDirection::LEFT)
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Drop", true);
		}

		if (Input::GetKeyPressed(eKeyCode::LEFT) && mDir == eDirection::RIGHT)
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_Drop", true);
		}

		// Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_SkillEnter", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_SkillEnter", false);

			mState = eTornadoKirbyState::Skill_Enter;

			// ����� ���		
			ResourceManager::Find<Sound>(L"TornadoSkill_Sound")->Play(true);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyStart", false);

			mState = eTornadoKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
		}

		if (mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Idle", true);

			mState = eTornadoKirbyState::Idle;
			ResourceManager::Find<Sound>(L"LandSound")->Play(false);
		}
	}

	void TornadoKirby::Down()
	{
		// �ִϸ��̼�

		// �ݴ����Ű�� �������� ���� ��ȯ
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"TornadoKirby_Right_Down", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_Down", true);
		}

		// Ű�Է��̾����� Idle �� ����
		if (!Input::GetKeyPressed(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Idle", true);

			mState = eTornadoKirbyState::Idle;
		}
	}

	void TornadoKirby::Fly_Start()
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
				mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyEnd", false);

			mState = eTornadoKirbyState::Fly_End;

			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);
		}

		// �ִϸ��̼��� ������ Fly Down ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyDown", true);

			mState = eTornadoKirbyState::Fly_Down;
		}
	}

	void TornadoKirby::Fly_End()
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
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Drop", true);

			mState = eTornadoKirbyState::Drop;
		}
	}

	void TornadoKirby::Fly_Down()
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
			mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyDown", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyDown", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyDown", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyDown", true);
		}


		// Fly Up
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyUp", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyUp", true);

			mState = eTornadoKirbyState::Fly_Up;
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
				mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyEnd", false);

			mState = eTornadoKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			mRigidBody->SetLimitVelocity(Vector2(300.f, 300.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void TornadoKirby::Fly_Up()
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
			mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyUp", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyUp", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyUp", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyUp", true);
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
				mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyDown", true);

			mState = eTornadoKirbyState::Fly_Down;
		}

		// Fly End
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_FlyEnd", false);

			mState = eTornadoKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(GetOwner());
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			// ����� ���
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void TornadoKirby::Skill_Enter()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Skill", true);

			mState = eTornadoKirbyState::Skill;
		}
	}

	void TornadoKirby::Skill()
	{
		// �¿� �̵�
		Vector2 pos = mTransform->GetPosition();

		if (mDir == eDirection::RIGHT)
			pos.x += 150.f * Time::DeltaTime();
		else
			pos.x -= 150.f * Time::DeltaTime();

		mTransform->SetPosition(pos);

		mRigidBody->SetLimitVelocity(Vector2(50.f, 50.f));

		if (Input::GetKeyDown(eKeyCode::S) || Input::GetKeyPressed(eKeyCode::S))
		{
			mRigidBody->SetVelocity(Vector2(0.f, -50.f));
			mRigidBody->SetGround(false);
		}

		static float Duration = 0.f;
		Duration += Time::DeltaTime();

		if (Duration > 3.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_SkillExit", false);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_SkillExit", false);

			mState = eTornadoKirbyState::Skill_Exit;
			Duration = 0.f;
			mRigidBody->SetLimitVelocity(Vector2(300.f, 300.f));
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void TornadoKirby::Skill_Exit()
	{
		// �ִϸ��̼��� ������ ���� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"TornadoKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"TornadoKirby_Left_Drop", true);

			mState = eTornadoKirbyState::Drop;

			ResourceManager::Find<Sound>(L"TornadoSkill_Sound")->Stop(true);
		}
	}
}