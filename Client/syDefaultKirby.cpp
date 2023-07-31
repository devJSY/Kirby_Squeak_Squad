#include "syDefaultKirby.h"
#include "syTransform.h"
#include "syInput.h"
#include "syTime.h"
#include "syCamera.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syInput.h"
#include "syAnimator.h"
#include "syRigidbody.h"
#include "syCollider.h"
#include "syObject.h"
#include "syDash_Effect.h"
#include "syObject.h"
#include "syLevelSelectScene.h"
#include "sySound.h"
#include "syBreath_Effect.h"
#include "syNormal_Skill.h"

namespace sy
{
	DefaultKirby::DefaultKirby()
		: Player(eAbilityType::Normal, ePlayerMode::LevelMode)
		, mState(eDefaultKirbyState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::RIGHT)
		, mbLevelEnter(false)
		, mbOnLeftStop(false)
		, mbOnRightStop(false)
		, mbTopStop(false)
		, mbOnSlope(false)
	{
	}

	DefaultKirby::~DefaultKirby()
	{
	}

	void DefaultKirby::Initialize()
	{			
		// �ؽ��� �ε�
		Texture* DefaultKirby_Right = ResourceManager::Load<Texture>(L"DefaultKirby_Right_Tex", L"..\\Resources\\Kirby\\DefaultKirby\\DefaultKirby_Right.bmp");
		Texture* DefaultKirby_Left = ResourceManager::Load<Texture>(L"DefaultKirby_Left_Tex", L"..\\Resources\\Kirby\\DefaultKirby\\DefaultKirby_Left.bmp");

		// �θ�����ڿ��� ������� ������Ʈ ��������� ����
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		
		mRigidBody = GetComponent<Rigidbody>();
		mRigidBody->SetGround(true);

		// �ִϸ��̼� ����
		mAnimator->CreateAnimation(DefaultKirby_Right, L"Choice", Vector2(309.f, 324.f), Vector2(22.f, 28.f), Vector2(22.f, 0.f), 0.04f, 9);
		mAnimator->CreateAnimation(DefaultKirby_Right, L"Enter", Vector2(738.f, 7.f), Vector2(19.f, 22.f), Vector2(19.f, 0.f), 0.6f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Idle", Vector2(8.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Idle", Vector2(972.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Stop", Vector2(468.f, 8.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.3f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Stop", Vector2(510.f, 8.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.3f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Walk", Vector2(253.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.07f, 10);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Walk", Vector2(726.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.07f, 10);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Run", Vector2(569.f, 306.f), Vector2(24.f, 19.f), Vector2(24.f, 0.f), 0.043f, 8);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Run", Vector2(407.f, 306.f), Vector2(24.f, 19.f), Vector2(-24.f, 0.f), 0.043f, 8);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Jump", Vector2(716.f, 9.f), Vector2(20.f, 20.f), Vector2(20.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Jump", Vector2(264.f, 9.f), Vector2(20.f, 20.f), Vector2(-20.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Turn", Vector2(759.f, 9.f), Vector2(22.f, 20.f), Vector2(22.f, 0.f), 0.05f, 6); 
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Turn", Vector2(219.f, 9.f), Vector2(22.f, 20.f), Vector2(-22.f, 0.f), 0.05f, 6);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Damage", Vector2(0.f, 179.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.04f, 10);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Damage", Vector2(978.f, 179.f), Vector2(22.f, 22.f), Vector2(-22.f, 0.f), 0.04f, 10);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Drop", Vector2(892.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.05f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Drop", Vector2(87.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.05f, 2);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Down", Vector2(31.f, 19.f), Vector2(25.f, 10.f), Vector2(25.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Down", Vector2(944.f, 19.f), Vector2(25.f, 10.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyStart", Vector2(642.f, 37.f), Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.05f, 4);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyStart", Vector2(337.f, 37.f), Vector2(21.f, 24.f), Vector2(-21.f, 0.f), 0.05f, 4);
		
		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyEnd", Vector2(705.f, 37.f), Vector2(21.f, 24.f), Vector2(-21.f, 0.f), 0.05f, 4);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyEnd", Vector2(274.f, 37.f), Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.05f, 4);
		
		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyDown", Vector2(733.f, 36.f), Vector2(24.f, 25.f), Vector2(24.f, 0.f), 0.15f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyDown", Vector2(243.f, 36.f), Vector2(24.f, 25.f), Vector2(-24.f, 0.f), 0.15f, 2);
		
		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyUp", Vector2(785.f, 36.f), Vector2(26.f, 25.f), Vector2(26.f, 0.f), 0.07f, 4);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyUp", Vector2(189.f, 36.f), Vector2(26.f, 25.f), Vector2(-26.f, 0.f), 0.07f, 4);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhale_1", Vector2(796.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.06f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhale_1", Vector2(181.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.06f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhale_2", Vector2(842.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.06f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhale_2", Vector2(135.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.06f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhale_3", Vector2(896.f, 184.f), Vector2(26.f, 17.f), Vector2(26.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhale_3", Vector2(78.f, 184.f), Vector2(26.f, 17.f), Vector2(-26.f, 0.f), 0.1f, 4);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled", Vector2(738.f, 68.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.05f, 4);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled", Vector2(237.f, 68.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.05f, 4);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Idle", Vector2(8.f, 218.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Idle", Vector2(967.f, 218.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Walk", Vector2(143.f, 216.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.05f, 15);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Walk", Vector2(833.f, 216.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.05f, 15);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Run", Vector2(220.f, 278.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.03f, 16);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Run", Vector2(756.f, 278.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.03f, 16);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Jump", Vector2(550.f, 217.f), Vector2(23.f, 23.f), Vector2(23.f, 0.f), 1.5f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Jump", Vector2(427.f, 217.f), Vector2(23.f, 23.f), Vector2(-23.f, 0.f), 1.5f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Turn", Vector2(574.f, 216.f), Vector2(24.f, 23.f), Vector2(24.f, 0.f), 0.05f, 3);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Turn", Vector2(402.f, 216.f), Vector2(24.f, 23.f), Vector2(-24.f, 0.f), 0.05f, 3);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Drop", Vector2(652.f, 217.f), Vector2(26.f, 23.f), Vector2(26.f, 0.f), 0.1f, 2);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Drop", Vector2(322.f, 217.f), Vector2(26.f, 23.f), Vector2(-26.f, 0.f), 0.1f, 2);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Land", Vector2(707.f, 222.f), Vector2(30.f, 18.f), Vector2(30.f, 0.f), 0.1f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Land", Vector2(263.f, 222.f), Vector2(30.f, 18.f), Vector2(-30.f, 0.f), 0.1f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Damage", Vector2(235.f, 177.f), Vector2(26.f, 24.f), Vector2(26.f, 0.f), 0.1f, 3);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Damage", Vector2(739.f, 177.f), Vector2(26.f, 24.f), Vector2(-26.f, 0.f), 0.1f, 3);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Down", Vector2(838.f, 68.f), Vector2(32.f, 22.f), Vector2(32.f, 0.f), 0.15f, 5);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Down", Vector2(130.f, 68.f), Vector2(32.f, 22.f), Vector2(-32.f, 0.f), 0.15f, 5);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled_Skill", Vector2(764.f, 305.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.07f, 5);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled_Skill", Vector2(211.f, 305.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.07f, 5);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"BreathSound", L"..\\Resources\\Sound\\Effect\\Breath.wav");
		ResourceManager::Load<Sound>(L"DamageSound", L"..\\Resources\\Sound\\Effect\\Damage.wav");
		ResourceManager::Load<Sound>(L"FlySound", L"..\\Resources\\Sound\\Effect\\Fly.wav");
		ResourceManager::Load<Sound>(L"InhaleSkillSound", L"..\\Resources\\Sound\\Effect\\InhaleSkill.wav");
		ResourceManager::Load<Sound>(L"JumpSound", L"..\\Resources\\Sound\\Effect\\Jump.wav");
		ResourceManager::Load<Sound>(L"LandSound", L"..\\Resources\\Sound\\Effect\\Land.wav");
		ResourceManager::Load<Sound>(L"RunSound", L"..\\Resources\\Sound\\Effect\\Run.wav");
		ResourceManager::Load<Sound>(L"StarSpitSound", L"..\\Resources\\Sound\\Effect\\StarSpit.wav");
		ResourceManager::Load<Sound>(L"ClickSound", L"..\\Resources\\Sound\\Effect\\Click.wav");
		
		ResourceManager::Find<Sound>(L"BreathSound")->SetVolume(20.f);
		ResourceManager::Find<Sound>(L"JumpSound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"FlySound")->SetVolume(100.f);
		ResourceManager::Find<Sound>(L"InhaleSkillSound")->SetVolume(80.f);
		ResourceManager::Find<Sound>(L"LandSound")->SetVolume(10.f);
		ResourceManager::Find<Sound>(L"RunSound")->SetVolume(100.f);


		Player::Initialize();
	}

	void DefaultKirby::Update()
	{
		// ���� ����
		mDir = mTransform->GetDirection();

		// PlayerMode �� ���� ����ó�� 
		if (GetPlayerMode() == ePlayerMode::LevelMode)
		{
			switch (mState)
			{
			case eDefaultKirbyState::Choice:
				Choice();
				break;
			case eDefaultKirbyState::Enter:
				Enter();
				break;
			case eDefaultKirbyState::Idle:
				Level_Idle();
				break;
			case eDefaultKirbyState::Run:
				Level_Run();
				break;
			case eDefaultKirbyState::Fly_Up:
				Level_FlyUp();
				break;
			case eDefaultKirbyState::Drop:
				Level_Drop();
				break;
			default:
				break;
			}
		}
		else if (GetPlayerMode() == ePlayerMode::PlayMode)
		{
			// �ȼ��浹 üũ
			CheckPixelCollision();

			// ����ó��
			switch (mState)
			{
			case eDefaultKirbyState::Idle:
				Idle();
				break;
			case eDefaultKirbyState::Walk:
				Walk();
				break;
			case eDefaultKirbyState::Run:
				Run();
				break;
			case eDefaultKirbyState::Jump:
				Jump();
				break;
			case eDefaultKirbyState::Turn:
				Turn();
				break;
			case eDefaultKirbyState::Damage:
				Damage();
				break;
			case eDefaultKirbyState::Drop:
				Drop();
				break;
			case eDefaultKirbyState::Down:
				Down();
				break;
			case eDefaultKirbyState::Inhale_1:
				Inhale_1();
				break;
			case eDefaultKirbyState::Inhale_2:
				Inhale_2();
				break;
			case eDefaultKirbyState::Inhale_3:
				Inhale_3();
				break;
			case eDefaultKirbyState::Fly_Start:
				Fly_Start();
				break;
			case eDefaultKirbyState::Fly_End:
				Fly_End();
				break;
			case eDefaultKirbyState::Fly_Down:
				Fly_Down();
				break;
			case eDefaultKirbyState::Fly_Up:
				Fly_Up();
				break;
			case eDefaultKirbyState::Inhaled:
				Inhaled();
				break;
			case eDefaultKirbyState::Inhaled_Idle:
				Inhaled_Idle();
				break;
			case eDefaultKirbyState::Inhaled_Walk:
				Inhaled_Walk();
				break;
			case eDefaultKirbyState::Inhaled_Run:
				Inhaled_Run();
				break;
			case eDefaultKirbyState::Inhaled_Jump:
				Inhaled_Jump();
				break;
			case eDefaultKirbyState::Inhaled_Turn:
				Inhaled_Turn();
				break;
			case eDefaultKirbyState::Inhaled_Drop:
				Inhaled_Drop();
				break;
			case eDefaultKirbyState::Inhaled_Land:
				Inhaled_Land();
				break;
			case eDefaultKirbyState::Inhaled_Damage:
				Inhaled_Damage();
				break;
			case eDefaultKirbyState::Inhaled_Down:
				Inhaled_Down();
				break;
			case eDefaultKirbyState::Inhaled_Skill:
				Inhaled_Skill();
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

		Player::Update();
	}

	void DefaultKirby::Render(HDC hdc)
	{
		Player::Render(hdc);
	}

	void DefaultKirby::OnCollisionEnter(Collider* other)
	{
	}

	void DefaultKirby::OnCollisionStay(Collider* other)
	{

	}

	void DefaultKirby::OnCollisionExit(Collider* other)
	{

	}

	void DefaultKirby::CheckPixelCollision()
	{
		// StageŸ�Կ����� �ȼ��ؽ��� �����ϱ�
		Texture* PixelTex = ResourceManager::Find<Texture>(L"Stage1_Pixel");

		if (PixelTex == nullptr)
			return;

		// Offset �ȼ� �»����ġ ����
		Vector2 offset = Vector2::Zero;

		std::wstring CurSceneName =SceneManager::GetActiveScene()->GetName();

		if (CurSceneName == L"Stage1Scene")
		{
			offset = Vector2::Zero;
		}
		else if(CurSceneName == L"Stage2Scene")
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

		Collider* col = GetComponent<Collider>();
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
			if (!(mState == eDefaultKirbyState::Jump 
				|| mState == eDefaultKirbyState::Fly_Up
				|| mState == eDefaultKirbyState::Inhaled_Jump))
			{
				// �̵�
				Vector2 pos = mTransform->GetPosition();
				pos.y -= 1.f;
				mTransform->SetPosition(pos);
				mRigidBody->SetGround(true);
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

	void DefaultKirby::Choice()
	{
		// �ִϸ��̼�
		if ((Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::RIGHT)) && !mbLevelEnter)
		{
			mAnimator->PlayAnimation(L"Choice", false);
		}		

		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			// ���� ù�����̶�� Enter�ִϸ��̼� ���
			if (mbLevelEnter)
			{
				mAnimator->PlayAnimation(L"Enter", false);
				mState = eDefaultKirbyState::Enter;
				mbLevelEnter = false;
			}
			else
			{
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
				mState = eDefaultKirbyState::Idle;
			}
		}
	}

	void DefaultKirby::Enter()
	{
		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}
	}

	void DefaultKirby::Level_Idle()
	{
		if (Input::GetKeyDown(eKeyCode::UP) 
			|| Input::GetKeyDown(eKeyCode::DOWN)
			|| Input::GetKeyDown(eKeyCode::RIGHT)
			|| Input::GetKeyDown(eKeyCode::LEFT))
		{
			mAnimator->PlayAnimation(L"Choice", false);
			mState = eDefaultKirbyState::Choice;
		}

		if (Input::GetKeyDown(eKeyCode::W)
			|| Input::GetKeyDown(eKeyCode::A)
			|| Input::GetKeyDown(eKeyCode::D))
		{
			mAnimator->PlayAnimation(L"Enter", false);
			mState = eDefaultKirbyState::Enter;
		}
	}

	void DefaultKirby::Level_Run()
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
			Dash_Effect* DashEffect = new Dash_Effect(this);
			object::ActiveSceneAddGameObject(eLayerType::Effect, DashEffect);
			time = 0.f;
		}		
	}

	void DefaultKirby::Level_FlyUp()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y -= 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void DefaultKirby::Level_Drop()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y += 120.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void DefaultKirby::Idle()
	{
		// �ִϸ��̼� 

		// ���� ���� ���°� �ƴ϶�� Drop���� ���� ��Ż�濡���� ����ó���������
		if (!mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Drop", true);

			mState = eDefaultKirbyState::Drop;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Walk", true);
				mState = eDefaultKirbyState::Walk;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (!mbOnLeftStop)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Walk", true);
				mState = eDefaultKirbyState::Walk;
			}
		}

		// Run
		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{		
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Run", true);
				mState = eDefaultKirbyState::Run;

				Dash_Effect* DashEffect = new Dash_Effect(this);
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
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Run", true);
				mState = eDefaultKirbyState::Run;

				Dash_Effect* DashEffect = new Dash_Effect(this);
				object::ActiveSceneAddGameObject(eLayerType::Effect, DashEffect);

				// ����� ���
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);
			}
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Jump", false);			
			
			mState = eDefaultKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Damage
		if (Input::GetKeyDown(eKeyCode::W))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Damage", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Damage", false);

			mState = eDefaultKirbyState::Damage;
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Down", false);

			mState = eDefaultKirbyState::Down;
		}

		// Inhale_1
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhale_1", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhale_1", true);

			mState = eDefaultKirbyState::Inhale_1;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Play(true);
		}
	}

	void DefaultKirby::Walk()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
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
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Drop", true);

			mState = eDefaultKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}

		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Walk", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Walk", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Walk", true);
		}		
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Walk", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Jump", false);

			mState = eDefaultKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Down", false);

			mState = eDefaultKirbyState::Down;
		}

		// Inhale_1
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhale_1", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhale_1", true);

			mState = eDefaultKirbyState::Inhale_1;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Play(true);
		}
	}

	void DefaultKirby::Run()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;

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
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Drop", true);

			mState = eDefaultKirbyState::Drop;
		}

		// Idle
		// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}

		// Run
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Run", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Run", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Run", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Run", true);
		}

		// Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Jump", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Jump", false);

			mState = eDefaultKirbyState::Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Down", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Down", false);

			mState = eDefaultKirbyState::Down;
		}

		// Inhale_1
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhale_1", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhale_1", true);

			mState = eDefaultKirbyState::Inhale_1;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Play(true);
		}
	}

	void DefaultKirby::Jump()
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
					mAnimator->PlayAnimation(L"DefaultKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"DefaultKirby_Left_Turn", false);

				mState = eDefaultKirbyState::Turn;

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
					mAnimator->PlayAnimation(L"DefaultKirby_Right_Turn", false);
				else
					mAnimator->PlayAnimation(L"DefaultKirby_Left_Turn", false);

				mState = eDefaultKirbyState::Turn;

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
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Jump", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Jump", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Jump", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Jump", true);
		}

		// Inhale_1
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhale_1", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhale_1", true);

			KeyPressdTime = 0.f;
			KeyReleaseTime = 0.f;
			mState = eDefaultKirbyState::Inhale_1;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Play(true);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyStart", false);

			mState = eDefaultKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
			KeyPressdTime = 0.f;
			KeyReleaseTime = 0.f;

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void DefaultKirby::Turn()
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
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Drop", true);

			TurnTime = 0.f;
			mState = eDefaultKirbyState::Drop;
		}

		// Inhale_1
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhale_1", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhale_1", true);

			TurnTime = 0.f;
			mState = eDefaultKirbyState::Inhale_1;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Play(true);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyStart", false);

			TurnTime = 0.f;
			mState = eDefaultKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"FlySound")->Play(false);
		}
	}

	void DefaultKirby::Damage()
	{
		// �ִϸ��̼�
		
		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}
	}

	void DefaultKirby::Drop()
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
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Drop", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Drop", true);
		}


		// Inhale_1
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhale_1", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhale_1", true);

			mState = eDefaultKirbyState::Inhale_1;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Play(true);
		}

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyStart", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyStart", false);

			mState = eDefaultKirbyState::Fly_Start;
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
		}

		if (mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
			ResourceManager::Find<Sound>(L"LandSound")->Play(false);
		}
	}

	void DefaultKirby::Down()
	{
		// �ִϸ��̼�
		
		// �ݴ����Ű�� �������� ���� ��ȯ
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Down", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Down", true);
		}

		// Ű�Է��̾����� Idle �� ����
		if (!Input::GetKeyPressed(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}
	}

	void DefaultKirby::Inhale_1()
	{
		static float inhaleTime = 0;

		inhaleTime += Time::DeltaTime();

		if (inhaleTime > 0.5f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhale_2", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhale_2", true);

			mState = eDefaultKirbyState::Inhale_2;

			inhaleTime = 0.f;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Play(true);
		}

		// Ű�Է��̾����� Idle �� ����
		if (!Input::GetKeyPressed(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;

			inhaleTime = 0.f;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Stop(true);
		}

		// ���͸� ������ ���º�ȯ
		if (false)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled", false);

			mState = eDefaultKirbyState::Inhaled;

			inhaleTime = 0.f;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Stop(true);
		}
	}

	void DefaultKirby::Inhale_2()
	{
		static float inhaleTime = 0;

		inhaleTime += Time::DeltaTime();

		if (inhaleTime > 1.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhale_3", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhale_3", false);

			mState = eDefaultKirbyState::Inhale_3;

			inhaleTime = 0.f;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Stop(true);
		}

		// Ű�Է��̾����� Idle �� ����
		if (!Input::GetKeyPressed(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;

			inhaleTime = 0.f;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Stop(true);
		}

		// ���͸� ������ ���º�ȯ
		if (true)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled", false);

			mState = eDefaultKirbyState::Inhaled;

			inhaleTime = 0.f;

			// ����� ���
			ResourceManager::Find<Sound>(L"InhaleSkillSound")->Stop(true);
		}
	}

	void DefaultKirby::Inhale_3()
	{
		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}
	}
	void DefaultKirby::Fly_Start()
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
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyEnd", false);

			mState = eDefaultKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(this);
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);
		}

		// �ִϸ��̼��� ������ Fly Down ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyDown", true);

			mState = eDefaultKirbyState::Fly_Down;
		}
	}

	void DefaultKirby::Fly_End()
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
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Drop", true);

			mState = eDefaultKirbyState::Drop;
		}
	}

	void DefaultKirby::Fly_Down()
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
			mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyDown", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyDown", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyDown", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyDown", true);
		}


		// Fly Up
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyUp", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyUp", true);

			mState = eDefaultKirbyState::Fly_Up;			
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
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyEnd", false);

			mState = eDefaultKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(this);
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			mRigidBody->SetLimitVelocity(Vector2(300.f, 300.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);
		}
	}

	void DefaultKirby::Fly_Up()
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
			mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyUp", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyUp", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyUp", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyUp", true);
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
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyDown", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyDown", true);

			mState = eDefaultKirbyState::Fly_Down;
		}

		// Fly End
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyEnd", false);

			mState = eDefaultKirbyState::Fly_End;
			Breath_Effect* BreathEffect = new Breath_Effect(this);
			object::ActiveSceneAddGameObject(eLayerType::Effect, BreathEffect);

			// ����� ���
			ResourceManager::Find<Sound>(L"BreathSound")->Play(false);			
		}
	}

	void DefaultKirby::Inhaled()
	{
		// �ִϸ��̼��� ������ Inhaled_Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Idle", true);

			mState = eDefaultKirbyState::Inhaled_Idle;
		}
	}

	void DefaultKirby::Inhaled_Idle()
	{
		// �ִϸ��̼� 
	
		// ���� ���� ���°� �ƴ϶�� Inhaled_Drop���� ����
		if (!mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Drop", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Drop", true);

			mState = eDefaultKirbyState::Inhaled_Drop;
		}

		// Inhaled_Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Walk", true);
				mState = eDefaultKirbyState::Inhaled_Walk;
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (!mbOnLeftStop)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Walk", true);
				mState = eDefaultKirbyState::Inhaled_Walk;
			}
		}

		// Inhaled_Run
		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{
			if (!mbOnRightStop)
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Run", true);
				mState = eDefaultKirbyState::Inhaled_Run;

				Dash_Effect* DashEffect = new Dash_Effect(this);
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
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Run", true);
				mState = eDefaultKirbyState::Inhaled_Run;

				Dash_Effect* DashEffect = new Dash_Effect(this);
				object::ActiveSceneAddGameObject(eLayerType::Effect, DashEffect);

				// ����� ���
				ResourceManager::Find<Sound>(L"RunSound")->Play(false);
			}
		}

		// Inhaled_Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Jump", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Jump", false);

			mState = eDefaultKirbyState::Inhaled_Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Inhaled_Damage
		if (Input::GetKeyDown(eKeyCode::W))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Damage", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Damage", false);

			mState = eDefaultKirbyState::Inhaled_Damage;
		}

		// Inhaled_Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Down", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Down", false);

			mState = eDefaultKirbyState::Inhaled_Down;
		}

		// Inhaled_Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Skill", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Skill", false);

			mState = eDefaultKirbyState::Inhaled_Skill;

			// ����� ���
			ResourceManager::Find<Sound>(L"StarSpitSound")->Play(false);
		}
	}

	void DefaultKirby::Inhaled_Walk()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Idle", true);

			mState = eDefaultKirbyState::Inhaled_Idle;
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
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Drop", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Drop", true);

			mState = eDefaultKirbyState::Inhaled_Drop;
		}

		// Inhaled_Idle
		// �¿� ��� Ű�Էµ� ������ Inhaled_Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Idle", true);

			mState = eDefaultKirbyState::Inhaled_Idle;
		}

		// Inhaled_Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Walk", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Walk", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Walk", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Walk", true);
		}

		// Inhaled_Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Jump", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Jump", false);

			mState = eDefaultKirbyState::Inhaled_Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Inhaled_Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Down", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Down", false);

			mState = eDefaultKirbyState::Inhaled_Down;
		}

		// Inhaled_Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Skill", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Skill", false);

			mState = eDefaultKirbyState::Inhaled_Skill;

			// ����� ���
			ResourceManager::Find<Sound>(L"StarSpitSound")->Play(false);
		}
	}

	void DefaultKirby::Inhaled_Run()
	{
		// Stop ���¶�� Idle �� ���º���
		if (mbOnLeftStop || mbOnRightStop)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Idle", true);

			mState = eDefaultKirbyState::Inhaled_Idle;
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
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Drop", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Drop", true);

			mState = eDefaultKirbyState::Inhaled_Drop;
		}

		// Inhaled_Idle
		// �¿� ��� Ű�Էµ� ������ Inhaled_Idle ���·� ����
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Idle", true);

			mState = eDefaultKirbyState::Inhaled_Idle;
		}

		// Inhaled_Run
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Run", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Run", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Run", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Run", true);
		}

		// Inhaled_Jump
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Jump", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Jump", false);

			mState = eDefaultKirbyState::Inhaled_Jump;
			mRigidBody->SetGround(false);
			mRigidBody->SetVelocity(Vector2(0.f, -160.f));

			// ����� ���
			ResourceManager::Find<Sound>(L"JumpSound")->Play(false);
		}

		// Inhaled_Down
		if (Input::GetKeyDown(eKeyCode::DOWN))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Down", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Down", false);

			mState = eDefaultKirbyState::Inhaled_Down;
		}

		// Inhaled_Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Skill", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Skill", false);

			mState = eDefaultKirbyState::Inhaled_Skill;

			// ����� ���
			ResourceManager::Find<Sound>(L"StarSpitSound")->Play(false);
		}
	}

	void DefaultKirby::Inhaled_Jump()
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
					mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Turn", false);
				else
					mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Turn", false);

				mState = eDefaultKirbyState::Inhaled_Turn;

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
					mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Turn", false);
				else
					mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Turn", false);

				mState = eDefaultKirbyState::Inhaled_Turn;

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
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Jump", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Jump", true);
		}

		// Ű ���� �Է� ����ó��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Jump", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Jump", true);
		}

		// Inhaled_Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Skill", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Skill", false);

			KeyPressdTime = 0.f;
			KeyReleaseTime = 0.f;
			mState = eDefaultKirbyState::Inhaled_Skill;

			// ����� ���
			ResourceManager::Find<Sound>(L"StarSpitSound")->Play(false);
		}
	}

	void DefaultKirby::Inhaled_Turn()
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
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Drop", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Drop", true);

			TurnTime = 0.f;
			mState = eDefaultKirbyState::Inhaled_Drop;
		}

		// Inhaled_Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Skill", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Skill", false);

			mState = eDefaultKirbyState::Inhaled_Skill;

			// ����� ���
			ResourceManager::Find<Sound>(L"StarSpitSound")->Play(false);
		}
	}

	void DefaultKirby::Inhaled_Drop()
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
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Drop", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Drop", true);
		}

		// Inhaled_Skill
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Skill", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Skill", false);

			mState = eDefaultKirbyState::Inhaled_Skill;

			// ����� ���
			ResourceManager::Find<Sound>(L"StarSpitSound")->Play(false);
		}

		if (mRigidBody->IsGround())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Land", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Land", false);

			mState = eDefaultKirbyState::Inhaled_Land;

			// ����� ���
			ResourceManager::Find<Sound>(L"LandSound")->Play(false);
		}
	}

	void DefaultKirby::Inhaled_Land()
	{
		// �ִϸ��̼��� ������ ���� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Idle", true);

			mState = eDefaultKirbyState::Inhaled_Idle;
		}
	}

	void DefaultKirby::Inhaled_Damage()
	{
		// �ִϸ��̼�

		// �ִϸ��̼��� ������ Inhaled_Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Inhaled_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Inhaled_Idle", true);

			mState = eDefaultKirbyState::Inhaled_Idle;
		}
	}

	void DefaultKirby::Inhaled_Down()
	{
		// ����� ��ü�� Ÿ������ ���¼���



		// �ִϸ��̼��� ������ Idle ���·� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}
	}

	void DefaultKirby::Inhaled_Skill()
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

		// �ִϸ��̼��� ������ ���� ����
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Drop", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Drop", true);

			mState = eDefaultKirbyState::Drop;
		}
	}
}
