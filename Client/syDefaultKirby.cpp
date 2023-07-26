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
	{
	}

	DefaultKirby::~DefaultKirby()
	{
	}

	void DefaultKirby::Initialize()
	{			
		// 텍스쳐 로드
		Texture* DefaultKirby_Right = ResourceManager::Load<Texture>(L"DefaultKirby_Right_Tex", L"..\\Resources\\Kirby\\DefaultKirby\\DefaultKirby_Right.bmp");
		Texture* DefaultKirby_Left = ResourceManager::Load<Texture>(L"DefaultKirby_Left_Tex", L"..\\Resources\\Kirby\\DefaultKirby\\DefaultKirby_Left.bmp");

		// 부모생성자에서 만들었던 컴포넌트 멤버변수로 저장
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		
		mRigidBody = AddComponent<Rigidbody>();
		mRigidBody->SetGround(true);

		// 애니메이션 생성
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

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Turn", Vector2(759.f, 9.f), Vector2(22.f, 20.f), Vector2(22.f, 0.f), 0.05f, 6); // 0.035
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

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Inhaled", Vector2(738.f, 68.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.05f, 4);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Inhaled", Vector2(237.f, 68.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.05f, 4);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Idle", Vector2(8.f, 218.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 1.f, 1);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Idle", Vector2(967.f, 218.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 1.f, 1);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Walk", Vector2(143.f, 216.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.05f, 15);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Walk", Vector2(833.f, 216.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.05f, 15);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Run", Vector2(220.f, 278.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.03f, 16);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Run", Vector2(756.f, 278.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.03f, 16);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Jump", Vector2(550.f, 217.f), Vector2(23.f, 23.f), Vector2(23.f, 0.f), 1.5f, 1);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Jump", Vector2(427.f, 217.f), Vector2(23.f, 23.f), Vector2(-23.f, 0.f), 1.5f, 1);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Turn", Vector2(574.f, 216.f), Vector2(24.f, 23.f), Vector2(24.f, 0.f), 0.05f, 3);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Turn", Vector2(402.f, 216.f), Vector2(24.f, 23.f), Vector2(-24.f, 0.f), 0.05f, 3);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Drop", Vector2(652.f, 217.f), Vector2(26.f, 23.f), Vector2(26.f, 0.f), 0.1f, 2);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Drop", Vector2(322.f, 217.f), Vector2(26.f, 23.f), Vector2(-26.f, 0.f), 0.1f, 2);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Land", Vector2(707.f, 222.f), Vector2(30.f, 18.f), Vector2(30.f, 0.f), 0.1f, 1);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Land", Vector2(263.f, 222.f), Vector2(30.f, 18.f), Vector2(-30.f, 0.f), 0.1f, 1);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Damage", Vector2(235.f, 177.f), Vector2(26.f, 24.f), Vector2(26.f, 0.f), 0.1f, 3);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Damage", Vector2(739.f, 177.f), Vector2(26.f, 24.f), Vector2(-26.f, 0.f), 0.1f, 3);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Down", Vector2(838.f, 68.f), Vector2(32.f, 22.f), Vector2(32.f, 0.f), 0.15f, 5);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Down", Vector2(130.f, 68.f), Vector2(32.f, 22.f), Vector2(-32.f, 0.f), 0.15f, 5);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Skill", Vector2(764.f, 305.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.07f, 5);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Skill", Vector2(211.f, 305.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.07f, 5);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);

		Player::Initialize();
	}

	void DefaultKirby::Update()
	{
		// 방향 설정
		mDir = mTransform->GetDirection();

		// PlayerMode 에 따라서 상태처리 
		if (GetPlayerMode() == ePlayerMode::LevelMode)
		{
			// LevelMode 에선 Rigth 방향 고정
			mTransform->SetDirection(eDirection::RIGHT);

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
			case eDefaultKirbyState::Fly_Up:
				Level_FlyUp();
				break;
			case eDefaultKirbyState::Drop:
				Level_Drop();
				break;
			case eDefaultKirbyState::End:
				break;
			default:
				break;
			}
		}
		else if (GetPlayerMode() == ePlayerMode::PlayMode)
		{
			// 상태처리
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
			case eDefaultKirbyState::End:
				break;
			default:
				break;
			}
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

	void DefaultKirby::Choice()
	{
		// 애니메이션
		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mAnimator->PlayAnimation(L"Choice", false);
		}		

		// 애니메이션이 끝나면 Idle 상태로 변경
		if (mAnimator->IsActiveAnimationComplete())
		{
			// 씬에 첫진입이라면 Enter애니메이션 재생
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
		// 애니메이션이 끝나면 Idle 상태로 변경
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

	void DefaultKirby::Level_FlyUp()
	{
	}

	void DefaultKirby::Level_Drop()
	{
	}

	void DefaultKirby::Idle()
	{
		// 애니메이션 
	
		// Walk
		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Walk", true);
			mState = eDefaultKirbyState::Walk;
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Walk", true);
			mState = eDefaultKirbyState::Walk;
		}

		// Run
		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Run", true);
			mState = eDefaultKirbyState::Run;
		}

		if (Input::IsDoubleKeyPressed(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Run", true);
			mState = eDefaultKirbyState::Run;
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
		}
	}

	void DefaultKirby::Walk()
	{
		// 이동
		Vector2 pos = mTransform->GetPosition();

		if (mDir == eDirection::RIGHT)
			pos.x += 50.f * Time::DeltaTime();
		else
			pos.x -= 50.f * Time::DeltaTime();

		mTransform->SetPosition(pos);

		// 애니메이션

		// Idle
		// 좌우 어느 키입력도 없으면 Idle 상태로 변경
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

		// 키 동시 입력 예외처리
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

		// Run
		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{
			mTransform->SetDirection(eDirection::RIGHT);
			mAnimator->PlayAnimation(L"DefaultKirby_Right_Run", true);
			mState = eDefaultKirbyState::Run;
		}

		if (Input::IsDoubleKeyPressed(eKeyCode::LEFT))
		{
			mTransform->SetDirection(eDirection::LEFT);
			mAnimator->PlayAnimation(L"DefaultKirby_Left_Run", true);
			mState = eDefaultKirbyState::Run;
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
		}
	}

	void DefaultKirby::Run()
	{
		// 이동
		Vector2 pos = mTransform->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				pos.x += 150.f * Time::DeltaTime();
			else
				pos.x -= 150.f * Time::DeltaTime();
		}

		mTransform->SetPosition(pos);

		// 애니메이션

		// Idle
		// 좌우 어느 키입력도 없으면 Idle 상태로 변경
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

		// 키 동시 입력 예외처리
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
		}
	}

	void DefaultKirby::Jump()
	{
		// 상하 이동
		static float KeyReleaseTime = 0.f;
		static float KeyPressdTime = 0.f;

		if (Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			KeyPressdTime += Time::DeltaTime();

			// 일정 누른 시간에만 상승
			if (KeyPressdTime < 0.2f)
			{
				mRigidBody->AddForce(Vector2(0.f, -700.f));
			}

			// 키를 누른 시간이 일정시간이상 지나면 상태변경
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

			// 키를 뗀시간이 일정시간이상 지나면 상태변경
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


		// 좌우 이동
		Vector2 pos = mTransform->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				pos.x += 50.f * Time::DeltaTime();
			else
				pos.x -= 50.f * Time::DeltaTime();
		}

		mTransform->SetPosition(pos);

		// 애니메이션

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

		// 키 동시 입력 예외처리
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

			mState = eDefaultKirbyState::Inhale_1;
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
		}
	}

	void DefaultKirby::Turn()
	{
		//// 이동
		Vector2 pos = mTransform->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				pos.x += 50.f * Time::DeltaTime();
			else
				pos.x -= 50.f * Time::DeltaTime();
		}

		mTransform->SetPosition(pos);

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

		// 애니메이션이 끝나면 Idle 상태로 변경
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
	}

	void DefaultKirby::Damage()
	{
		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPosition();

		//tr->SetPosition(pos);
		// 
		// 애니메이션
		
		// 애니메이션이 끝나면 Idle 상태로 변경
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
		// 좌우 이동
		Vector2 pos = mTransform->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				pos.x += 50.f * Time::DeltaTime();
			else
				pos.x -= 50.f * Time::DeltaTime();
		}

		mTransform->SetPosition(pos);

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
		}
	}

	void DefaultKirby::Down()
	{
		// 애니메이션
		
		// 반대방향키가 눌렸을때 방향 전환
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

		// 키입력이없을땐 Idle 로 변경
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
		}

		// 키입력이없을땐 Idle 로 변경
		if (!Input::GetKeyPressed(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;

			inhaleTime = 0.f;
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
		}

		// 키입력이없을땐 Idle 로 변경
		if (!Input::GetKeyPressed(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;

			inhaleTime = 0.f;
		}
	}

	void DefaultKirby::Inhale_3()
	{
		// 애니메이션이 끝나면 Idle 상태로 변경
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
		// 좌우 이동
		Vector2 pos = mTransform->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				pos.x += 50.f * Time::DeltaTime();
			else
				pos.x -= 50.f * Time::DeltaTime();
		}

		mTransform->SetPosition(pos);

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
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyEnd", false);

			mState = eDefaultKirbyState::Fly_End;
		}

		// 애니메이션이 끝나면 Fly Down 상태로 변경
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
		// 좌우 이동
		Vector2 pos = mTransform->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				pos.x += 50.f * Time::DeltaTime();
			else
				pos.x -= 50.f * Time::DeltaTime();
		}

		mTransform->SetPosition(pos);

		// 애니메이션이 끝나면 Drop 상태로 변경
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
		// 좌우 이동
		Vector2 pos = mTransform->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				pos.x += 50.f * Time::DeltaTime();
			else
				pos.x -= 50.f * Time::DeltaTime();
		}

		mTransform->SetPosition(pos);

		// 눌렀을때 상승
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			mRigidBody->SetVelocity(Vector2(0.f, -150.f));
		}

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

		// Fly Start
		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D)
			|| Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyUp", true);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyUp", true);

			mState = eDefaultKirbyState::Fly_Up;
		}

		// Fly End
		if (Input::GetKeyDown(eKeyCode::S))
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_FlyEnd", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_FlyEnd", false);

			mState = eDefaultKirbyState::Fly_End;
		}
	}

	void DefaultKirby::Fly_Up()
	{
		// 좌우 이동
		Vector2 pos = mTransform->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (mDir == eDirection::RIGHT)
				pos.x += 50.f * Time::DeltaTime();
			else
				pos.x -= 50.f * Time::DeltaTime();
		}

		mTransform->SetPosition(pos);

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

		// 누르고있을때 상승
		if (Input::GetKeyPressed(eKeyCode::A) || Input::GetKeyPressed(eKeyCode::D))
		{
			mRigidBody->SetVelocity(Vector2(0.f, -130.f));
		}

		// 키를 누르고있지 않을때 Fly Down
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
		}
	}
}
