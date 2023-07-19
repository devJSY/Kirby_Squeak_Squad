#include "syDefaultKirby.h"
#include "syTransform.h"
#include "syInput.h"
#include "syTime.h"
#include "syCamera.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syInput.h"
#include "syAnimator.h"

namespace sy
{
	DefaultKirby::DefaultKirby()
		: Player(eAbilityType::Normal)
		, mState(eDefaultKirbyState::Idle)
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

		Animator* animator = GetAnimator();

		// 애니메이션 생성
		animator->CreateAnimation(DefaultKirby_Right, L"Choice", Vector2(309.f, 324.f), Vector2(22.f, 28.f), Vector2(22.f, 0.f), 0.04f, 9);
		animator->CreateAnimation(DefaultKirby_Right, L"Enter", Vector2(738.f, 7.f), Vector2(19.f, 22.f), Vector2(19.f, 0.f), 0.6f, 1);

		animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Idle", Vector2(8.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);
		animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Idle", Vector2(972.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);

		animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Stop", Vector2(468.f, 8.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.3f, 1);
		animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Stop", Vector2(510.f, 8.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.3f, 1);

		animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Walk", Vector2(253.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.07f, 10);
		animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Walk", Vector2(726.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.07f, 10);

		animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Run", Vector2(569.f, 306.f), Vector2(24.f, 19.f), Vector2(24.f, 0.f), 0.043f, 8);
		animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Run", Vector2(407.f, 306.f), Vector2(24.f, 19.f), Vector2(-24.f, 0.f), 0.043f, 8);

		animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Jump", Vector2(716.f, 9.f), Vector2(20.f, 20.f), Vector2(20.f, 0.f), 1.f, 1);
		animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Jump", Vector2(264.f, 9.f), Vector2(20.f, 20.f), Vector2(-20.f, 0.f), 1.f, 1);

		animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Turn", Vector2(759.f, 9.f), Vector2(22.f, 20.f), Vector2(22.f, 0.f), 0.035f, 6);
		animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Turn", Vector2(219.f, 9.f), Vector2(22.f, 20.f), Vector2(-22.f, 0.f), 0.035f, 6);

		animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Damage", Vector2(0.f, 179.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.04f, 10);
		animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Damage", Vector2(978.f, 179.f), Vector2(22.f, 22.f), Vector2(-22.f, 0.f), 0.04f, 10);

		//animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Drop", Vector2(892.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.05f, 2);
		//animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Drop", Vector2(87.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.05f, 2);

		//animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Down", Vector2(31.f, 19.f), Vector2(25.f, 10.f), Vector2(25.f, 0.f), 1.f, 1);
		//animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Down", Vector2(944.f, 19.f), Vector2(25.f, 10.f), Vector2(-25.f, 0.f), 1.f, 1);

		//animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyStart", Vector2(642.f, 37.f), Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.05f, 4);
		//animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyStart", Vector2(337.f, 37.f), Vector2(21.f, 24.f), Vector2(-21.f, 0.f), 0.05f, 4);

		//animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyEnd", Vector2(705.f, 37.f), Vector2(21.f, 24.f), Vector2(-21.f, 0.f), 0.05f, 4);
		//animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyEnd", Vector2(274.f, 37.f), Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.05f, 4);

		//animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyDown", Vector2(733.f, 36.f), Vector2(24.f, 25.f), Vector2(24.f, 0.f), 0.15f, 2);
		//animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyDown", Vector2(243.f, 36.f), Vector2(24.f, 25.f), Vector2(-24.f, 0.f), 0.15f, 2);

		//animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyUp", Vector2(785.f, 36.f), Vector2(26.f, 25.f), Vector2(26.f, 0.f), 0.07f, 4);
		//animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyUp", Vector2(189.f, 36.f), Vector2(26.f, 25.f), Vector2(-26.f, 0.f), 0.07f, 4);

		//animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_B_1", Vector2(796.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		//animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_B_1", Vector2(181.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);
		//animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_B_2", Vector2(842.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		//animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_B_2", Vector2(135.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);

		//animator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_B_3", Vector2(896.f, 184.f), Vector2(26.f, 17.f), Vector2(26.f, 0.f), 0.1f, 4);
		//animator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_B_3", Vector2(78.f, 184.f), Vector2(26.f, 17.f), Vector2(-26.f, 0.f), 0.1f, 4);

		//animator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Idle", Vector2(8.f, 218.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 1.f, 1);
		//animator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Idle", Vector2(967.f, 218.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 1.f, 1);

		//animator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Walk", Vector2(143.f, 216.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.05f, 15);
		//animator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Walk", Vector2(833.f, 216.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.05f, 15);

		//animator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Run", Vector2(220.f, 278.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.03f, 16);
		//animator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Run", Vector2(756.f, 278.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.03f, 16);

		//animator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Jump", Vector2(550.f, 217.f), Vector2(23.f, 23.f), Vector2(23.f, 0.f), 1.5f, 1);
		//animator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Jump", Vector2(427.f, 217.f), Vector2(23.f, 23.f), Vector2(-23.f, 0.f), 1.5f, 1);

		//animator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Turn", Vector2(574.f, 216.f), Vector2(24.f, 23.f), Vector2(24.f, 0.f), 0.05f, 3);
		//animator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Turn", Vector2(402.f, 216.f), Vector2(24.f, 23.f), Vector2(-24.f, 0.f), 0.05f, 3);

		//animator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Drop", Vector2(652.f, 217.f), Vector2(26.f, 23.f), Vector2(26.f, 0.f), 0.1f, 2);
		//animator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Drop", Vector2(322.f, 217.f), Vector2(26.f, 23.f), Vector2(-26.f, 0.f), 0.1f, 2);

		//animator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Land", Vector2(707.f, 222.f), Vector2(30.f, 18.f), Vector2(30.f, 0.f), 0.1f, 1);
		//animator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Land", Vector2(263.f, 222.f), Vector2(30.f, 18.f), Vector2(-30.f, 0.f), 0.1f, 1);

		//animator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Damage", Vector2(235.f, 177.f), Vector2(26.f, 24.f), Vector2(26.f, 0.f), 0.1f, 3);
		//animator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Damage", Vector2(739.f, 177.f), Vector2(26.f, 24.f), Vector2(-26.f, 0.f), 0.1f, 3);

		//animator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Down", Vector2(838.f, 68.f), Vector2(32.f, 22.f), Vector2(32.f, 0.f), 0.15f, 5);
		//animator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Down", Vector2(130.f, 68.f), Vector2(32.f, 22.f), Vector2(-32.f, 0.f), 0.15f, 5);

		//animator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Inhale", Vector2(738.f, 68.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.05f, 4);
		//animator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Inhale", Vector2(237.f, 68.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.05f, 4);

		//animator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Skill", Vector2(764.f, 305.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.07f, 5);
		//animator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Skill", Vector2(211.f, 305.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.07f, 5);

		animator->SetAffectedCamera(true);
		animator->PlayAnimation(L"DefaultKirby_Right_Idle", true);

		Player::Initialize();
	}

	void DefaultKirby::Update()
	{
		// 상태처리
		switch (mState)
		{
		case sy::eDefaultKirbyState::Idle:
			Idle();
			break;
		case sy::eDefaultKirbyState::Stop:
			Stop();
			break;
		case sy::eDefaultKirbyState::Walk:
			Walk();
			break;
		case sy::eDefaultKirbyState::Run:
			Run();
			break;
		case sy::eDefaultKirbyState::Jump:
			Jump();
			break;
		case sy::eDefaultKirbyState::Turn:
			Turn();
			break;
		case sy::eDefaultKirbyState::Damage:
			Damage();
			break;
		case sy::eDefaultKirbyState::End:
			break;
		default:
			break;
		}

		Player::Update();
	}

	void DefaultKirby::Render(HDC hdc)
	{
		Player::Render(hdc);
	}

	void DefaultKirby::Idle()
	{
		// 애니메이션, 키입력 방향 설정
		Animator* animator = GetAnimator();

		if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::RIGHT))
		{
			SetDirection(eDirection::RIGHT);
			animator->PlayAnimation(L"DefaultKirby_Right_Walk", true);
			mState = eDefaultKirbyState::Walk;
		}

		if (Input::GetKeyDown(eKeyCode::LEFT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			SetDirection(eDirection::LEFT);
			animator->PlayAnimation(L"DefaultKirby_Left_Walk", true);
			mState = eDefaultKirbyState::Walk;
		}

		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{
			SetDirection(eDirection::RIGHT);
			animator->PlayAnimation(L"DefaultKirby_Right_Run", true);
			mState = eDefaultKirbyState::Run;
		}

		if (Input::IsDoubleKeyPressed(eKeyCode::LEFT))
		{
			SetDirection(eDirection::LEFT);
			animator->PlayAnimation(L"DefaultKirby_Left_Run", true);
			mState = eDefaultKirbyState::Run;
		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (GetDirection() == eDirection::RIGHT)
				animator->PlayAnimation(L"DefaultKirby_Right_Jump", false);
			else
				animator->PlayAnimation(L"DefaultKirby_Left_Jump", false);			
			
			mState = eDefaultKirbyState::Jump;
		}

		if (Input::GetKeyDown(eKeyCode::W))
		{
			if (GetDirection() == eDirection::RIGHT)
				animator->PlayAnimation(L"DefaultKirby_Right_Damage", false);
			else
				animator->PlayAnimation(L"DefaultKirby_Left_Damage", false);

			mState = eDefaultKirbyState::Damage;
		}
	}

	void DefaultKirby::Stop()
	{
		// 애니메이션
		Animator* animator = GetAnimator();
		eDirection Dir = GetDirection();

		// 애니메이션이 끝나면 Idle 상태로 변경
		if (animator->IsActiveAnimationComplete())
		{
			if (Dir == eDirection::RIGHT)
				animator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				animator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}
	}

	void DefaultKirby::Walk()
	{
		// 애니메이션, 방향 설정
		Animator* animator = GetAnimator();
		eDirection Dir = GetDirection();

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			// 방향 전환시 Stop 애니메이션 실행
			if (Dir == eDirection::LEFT)
			{
				SetDirection(eDirection::RIGHT);
				animator->PlayAnimation(L"DefaultKirby_Left_Stop", false);
				mState = eDefaultKirbyState::Stop;
			}
			else
			{
				SetDirection(eDirection::RIGHT);
				animator->PlayAnimation(L"DefaultKirby_Right_Walk", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			// 방향 전환시 Stop 애니메이션 실행
			if (Dir == eDirection::RIGHT)
			{
				SetDirection(eDirection::LEFT);
				animator->PlayAnimation(L"DefaultKirby_Right_Stop", false);
				mState = eDefaultKirbyState::Stop;
			}
			else
			{
				SetDirection(eDirection::LEFT);
				animator->PlayAnimation(L"DefaultKirby_Left_Walk", true);
			}
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			SetDirection(eDirection::RIGHT);
			animator->PlayAnimation(L"DefaultKirby_Right_Walk", true);
		}		
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			SetDirection(eDirection::LEFT);
			animator->PlayAnimation(L"DefaultKirby_Left_Walk", true);
		}

		if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT))
		{
			SetDirection(eDirection::RIGHT);
			animator->PlayAnimation(L"DefaultKirby_Right_Run", true);
			mState = eDefaultKirbyState::Run;
		}

		if (Input::IsDoubleKeyPressed(eKeyCode::LEFT))
		{
			SetDirection(eDirection::LEFT);
			animator->PlayAnimation(L"DefaultKirby_Left_Run", true);
			mState = eDefaultKirbyState::Run;
		}

		// 좌우 어느 키입력도 없으면 Idle 상태로 변경
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (Dir == eDirection::RIGHT)
				animator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				animator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (Dir == eDirection::RIGHT)
				animator->PlayAnimation(L"DefaultKirby_Right_Jump", false);
			else
				animator->PlayAnimation(L"DefaultKirby_Left_Jump", false);

			mState = eDefaultKirbyState::Jump;
		}


		// 이동
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Dir == eDirection::RIGHT)
			pos.x += 50.f * Time::DeltaTime();
		else
			pos.x -= 50.f * Time::DeltaTime();

		tr->SetPosition(pos);
	}

	void DefaultKirby::Run()
	{
		// 애니메이션
		Animator* animator = GetAnimator();
		eDirection Dir = GetDirection();

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			// 방향 전환시 Stop 애니메이션 실행
			if (Dir == eDirection::LEFT)
			{
				SetDirection(eDirection::RIGHT);
				animator->PlayAnimation(L"DefaultKirby_Left_Stop", false);
				mState = eDefaultKirbyState::Stop;
			}
			else
			{
				SetDirection(eDirection::RIGHT);
				animator->PlayAnimation(L"DefaultKirby_Right_Run", true);
			}
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			// 방향 전환시 Stop 애니메이션 실행
			if (Dir == eDirection::RIGHT)
			{
				SetDirection(eDirection::LEFT);
				animator->PlayAnimation(L"DefaultKirby_Right_Stop", false);
				mState = eDefaultKirbyState::Stop;
			}
			else
			{
				SetDirection(eDirection::LEFT);
				animator->PlayAnimation(L"DefaultKirby_Left_Run", true);
			}
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			SetDirection(eDirection::RIGHT);
			animator->PlayAnimation(L"DefaultKirby_Right_Run", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			SetDirection(eDirection::LEFT);
			animator->PlayAnimation(L"DefaultKirby_Left_Run", true);
		}

		// 좌우 어느 키입력도 없으면 Idle 상태로 변경
		if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (Dir == eDirection::RIGHT)
				animator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				animator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}

		if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
		{
			if (Dir == eDirection::RIGHT)
				animator->PlayAnimation(L"DefaultKirby_Right_Jump", false);
			else
				animator->PlayAnimation(L"DefaultKirby_Left_Jump", false);

			mState = eDefaultKirbyState::Jump;
		}


		// 이동
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (Dir == eDirection::RIGHT)
				pos.x += 150.f * Time::DeltaTime();
			else
				pos.x -= 150.f * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}

	void DefaultKirby::Jump()
	{
		// 애니메이션
		Animator* animator = GetAnimator();
		eDirection Dir = GetDirection();

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			SetDirection(eDirection::RIGHT);
			animator->PlayAnimation(L"DefaultKirby_Right_Jump", true);
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			SetDirection(eDirection::LEFT);
			animator->PlayAnimation(L"DefaultKirby_Left_Jump", true);
		}

		// 키 동시 입력 예외처리
		if (Input::GetKeyPressed(eKeyCode::RIGHT) && Input::GetKeyUp(eKeyCode::LEFT))
		{
			SetDirection(eDirection::RIGHT);
			animator->PlayAnimation(L"DefaultKirby_Right_Jump", true);
		}
		if (Input::GetKeyPressed(eKeyCode::LEFT) && Input::GetKeyUp(eKeyCode::RIGHT))
		{
			SetDirection(eDirection::LEFT);
			animator->PlayAnimation(L"DefaultKirby_Left_Jump", true);
		}

		// 키를 누른시간에 따라서 Jump상태 지속
		static float JumpTime = 0.0f;
		JumpTime += Time::DeltaTime();

		if (Input::GetKeyUp(eKeyCode::A) || Input::GetKeyUp(eKeyCode::D) || JumpTime > 0.5f)
		{
			if (Dir == eDirection::RIGHT)
				animator->PlayAnimation(L"DefaultKirby_Right_Turn", false);
			else
				animator->PlayAnimation(L"DefaultKirby_Left_Turn", false);

			mState = eDefaultKirbyState::Turn;
			JumpTime = 0.0f; // 상태를 벗어나는경우 초기화 필요
		}

		// 이동
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (Dir == eDirection::RIGHT)
				pos.x += 50.f * Time::DeltaTime();
			else
				pos.x -= 50.f * Time::DeltaTime();
		}

		pos.y -= 300.f * Time::DeltaTime();

		tr->SetPosition(pos);
	}

	void DefaultKirby::Turn()
	{
		// 애니메이션
		Animator* animator = GetAnimator();
		eDirection Dir = GetDirection();

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			animator->PlayAnimation(L"DefaultKirby_Right_Turn", false);
		}

		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			animator->PlayAnimation(L"DefaultKirby_Left_Turn", false);
		}

		// 애니메이션이 끝나면 Idle 상태로 변경
		if (animator->IsActiveAnimationComplete())
		{
			if (Dir == eDirection::RIGHT)
				animator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				animator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}

		// 이동
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (Dir == eDirection::RIGHT)
				pos.x += 50.f * Time::DeltaTime();
			else
				pos.x -= 50.f * Time::DeltaTime();
		}

		pos.y += 150.f * Time::DeltaTime();

		tr->SetPosition(pos);
	}

	void DefaultKirby::Damage()
	{
		// 애니메이션
		Animator* animator = GetAnimator();
		eDirection Dir = GetDirection();

		// 애니메이션이 끝나면 Idle 상태로 변경
		if (animator->IsActiveAnimationComplete())
		{
			if (Dir == eDirection::RIGHT)
				animator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				animator->PlayAnimation(L"DefaultKirby_Left_Idle", true);

			mState = eDefaultKirbyState::Idle;
		}

		//Transform* tr = GetComponent<Transform>();
		//Vector2 pos = tr->GetPosition();

		//tr->SetPosition(pos);
	}
}
