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
		: mState(eDefaultKirbyState::Idle)
		, mDir(eDirection::RIGHT)
	{
		// �ؽ��� �ε�
		Texture* DefaultKirby_Right = ResourceManager::Load<Texture>(L"DefaultKirby_Right", L"..\\Resources\\Kirby\\DefaultKirby\\DefaultKirby_Right.bmp");
		Texture* DefaultKirby_Left = ResourceManager::Load<Texture>(L"DefaultKirby_Left", L"..\\Resources\\Kirby\\DefaultKirby\\DefaultKirby_Left.bmp");

		// �ִϸ��̼� ����
		mAnimator->CreateAnimation(DefaultKirby_Right, L"Choice", Vector2(309.f, 324.f), Vector2(22.f, 28.f), Vector2(22.f, 0.f), 0.04f, 9);
		mAnimator->CreateAnimation(DefaultKirby_Right, L"Enter", Vector2(738.f, 7.f), Vector2(19.f, 22.f), Vector2(19.f, 0.f), 0.6f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Idle", Vector2(8.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Idle", Vector2(972.f, 11.f), Vector2(20.f, 18.f), Vector2(20.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Walk", Vector2(253.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.07f, 10);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Walk", Vector2(726.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.07f, 10);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Run", Vector2(569.f, 306.f), Vector2(24.f, 19.f), Vector2(24.f, 0.f), 0.043f, 8);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Run", Vector2(407.f, 306.f), Vector2(24.f, 19.f), Vector2(-24.f, 0.f), 0.043f, 8);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Jump", Vector2(716.f, 9.f), Vector2(20.f, 20.f), Vector2(20.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Jump", Vector2(264.f, 9.f), Vector2(20.f, 20.f), Vector2(-20.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Turn", Vector2(759.f, 9.f), Vector2(22.f, 20.f), Vector2(22.f, 0.f), 0.035f, 6);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Turn", Vector2(219.f, 9.f), Vector2(22.f, 20.f), Vector2(-22.f, 0.f), 0.035f, 6);

		mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Damage", Vector2(0.f, 179.f), Vector2(22.f, 22.f), Vector2(22.f, 0.f), 0.04f, 10);
		mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Damage", Vector2(978.f, 179.f), Vector2(22.f, 22.f), Vector2(-22.f, 0.f), 0.04f, 10);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Drop", Vector2(892.f, 10.f), Vector2(21.f, 19.f), Vector2(21.f, 0.f), 0.05f, 2);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Drop", Vector2(87.f, 10.f), Vector2(21.f, 19.f), Vector2(-21.f, 0.f), 0.05f, 2);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_Down", Vector2(31.f, 19.f), Vector2(25.f, 10.f), Vector2(25.f, 0.f), 1.f, 1);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_Down", Vector2(944.f, 19.f), Vector2(25.f, 10.f), Vector2(-25.f, 0.f), 1.f, 1);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyStart", Vector2(642.f, 37.f), Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.05f, 4);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyStart", Vector2(337.f, 37.f), Vector2(21.f, 24.f), Vector2(-21.f, 0.f), 0.05f, 4);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyEnd", Vector2(705.f, 37.f), Vector2(21.f, 24.f), Vector2(-21.f, 0.f), 0.05f, 4);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyEnd", Vector2(274.f, 37.f), Vector2(21.f, 24.f), Vector2(21.f, 0.f), 0.05f, 4);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyDown", Vector2(733.f, 36.f), Vector2(24.f, 25.f), Vector2(24.f, 0.f), 0.15f, 2);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyDown", Vector2(243.f, 36.f), Vector2(24.f, 25.f), Vector2(-24.f, 0.f), 0.15f, 2);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_FlyUp", Vector2(785.f, 36.f), Vector2(26.f, 25.f), Vector2(26.f, 0.f), 0.07f, 4);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_FlyUp", Vector2(189.f, 36.f), Vector2(26.f, 25.f), Vector2(-26.f, 0.f), 0.07f, 4);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_B_1", Vector2(796.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_B_1", Vector2(181.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);
		//mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_B_2", Vector2(842.f, 179.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.08f, 2);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_B_2", Vector2(135.f, 179.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.08f, 2);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"DefaultKirby_Right_B_3", Vector2(896.f, 184.f), Vector2(26.f, 17.f), Vector2(26.f, 0.f), 0.1f, 4);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"DefaultKirby_Left_B_3", Vector2(78.f, 184.f), Vector2(26.f, 17.f), Vector2(-26.f, 0.f), 0.1f, 4);

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

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Inhale", Vector2(738.f, 68.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.05f, 4);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Inhale", Vector2(237.f, 68.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.05f, 4);

		//mAnimator->CreateAnimation(DefaultKirby_Right, L"iDefaultKirby_Right_Skill", Vector2(764.f, 305.f), Vector2(25.f, 22.f), Vector2(25.f, 0.f), 0.07f, 5);
		//mAnimator->CreateAnimation(DefaultKirby_Left, L"iDefaultKirby_Left_Skill", Vector2(211.f, 305.f), Vector2(25.f, 22.f), Vector2(-25.f, 0.f), 0.07f, 5);

		mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
	}

	DefaultKirby::~DefaultKirby()
	{
	}

	void DefaultKirby::Initialize()
	{
		Player::Initialize();
	}

	void DefaultKirby::Update()
	{
		Update_State();
		Update_Move();
		Update_Animation();

		Player::Update();
	}

	void DefaultKirby::Render(HDC hdc)
	{
		Player::Render(hdc);
	}

	void DefaultKirby::Update_State()
	{
		//////////////////////// ���� ���� /////////////////////////////////////////////// 
		// �Է� üũ
		if (Input::GetKeyDown(eKeyCode::RIGHT))
		{
			mDir = eDirection::RIGHT;
		}

		if (Input::GetKeyDown(eKeyCode::LEFT))
		{
			mDir = eDirection::LEFT;
		}

		// ����ó�� ���� Ű�� �������¿��� �ݴ���Ű�� ���ȴٸ� ���⺯��
		if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
		{
			if (Input::GetKeyUp(eKeyCode::RIGHT))
			{
				mDir = eDirection::LEFT;
			}
			
			if (Input::GetKeyUp(eKeyCode::LEFT))
			{
				mDir = eDirection::RIGHT;
			}
		}

		//////////////////////// �ൿ�� ���� ���¼��� /////////////////////////////////////////////// 
		switch (mState)
		{
		case eDefaultKirbyState::Idle:
		{
			if (Input::GetKeyDown(eKeyCode::RIGHT) || Input::GetKeyDown(eKeyCode::LEFT)
				|| Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				mState = eDefaultKirbyState::Walk;
			}

			if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT) || Input::IsDoubleKeyPressed(eKeyCode::LEFT))
			{
				mState = eDefaultKirbyState::Run;
			}

			if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
			{
				mState = eDefaultKirbyState::Jump;
			}

			if (Input::GetKeyDown(eKeyCode::W))
			{
				mState = eDefaultKirbyState::Damage;
			}
		}
		break;

		case eDefaultKirbyState::Walk:
		{
			if (Input::IsDoubleKeyPressed(eKeyCode::RIGHT) || Input::IsDoubleKeyPressed(eKeyCode::LEFT))
			{
				mState = eDefaultKirbyState::Run;
			}

			// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
			if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
			{
				mState = eDefaultKirbyState::Idle;
			}

			if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
			{
				mState = eDefaultKirbyState::Jump;
			}
		}

		break;

		case eDefaultKirbyState::Run:
		{
			// �¿� ��� Ű�Էµ� ������ Idle ���·� ����
			if (!Input::GetKeyPressed(eKeyCode::RIGHT) && !Input::GetKeyPressed(eKeyCode::LEFT))
			{
				mState = eDefaultKirbyState::Idle;
			}

			if (Input::GetKeyDown(eKeyCode::A) || Input::GetKeyDown(eKeyCode::D))
			{
				mState = eDefaultKirbyState::Jump;
			}
		}
		break;

		case eDefaultKirbyState::Jump:
		{
			// Ű�� �����ð��� ���� Jump���� ����
			static float JumpTime = 0.0f; 
			JumpTime += Time::DeltaTime();

			if (Input::GetKeyUp(eKeyCode::A) || Input::GetKeyUp(eKeyCode::D) || JumpTime > 0.5f)
			{
				mState = eDefaultKirbyState::Turn;
				JumpTime = 0.0f; // ���¸� ����°�� �ʱ�ȭ �ʿ�
			}
		}
		break;

		case eDefaultKirbyState::Turn:
		{
			if (mAnimator->IsActiveAniComplete())
			{
				mState = eDefaultKirbyState::Idle;
			}
		}

		case eDefaultKirbyState::Damage:
		{
			if (mAnimator->IsActiveAniComplete())
			{
				mState = eDefaultKirbyState::Idle;
			}
		}
		break;

		break;
		}
	}

	void DefaultKirby::Update_Move()
	{
		Transform* tr = GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		switch (mState)
		{
		case eDefaultKirbyState::Idle:
		{
		}
		break;

		case eDefaultKirbyState::Walk:
		{
			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 50.f * Time::DeltaTime();
				else
					pos.x -= 50.f * Time::DeltaTime();
			}
		}
		break;

		case eDefaultKirbyState::Run:
		{
			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 150.f * Time::DeltaTime();
				else
					pos.x -= 150.f * Time::DeltaTime();
			}
		}
		break;

		case eDefaultKirbyState::Jump:
		{
			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 50.f * Time::DeltaTime();
				else
					pos.x -= 50.f * Time::DeltaTime();
			}

			pos.y -= 300.f * Time::DeltaTime();

		}
		break;

		case eDefaultKirbyState::Turn:
		{
			if (Input::GetKeyPressed(eKeyCode::RIGHT) || Input::GetKeyPressed(eKeyCode::LEFT))
			{
				if (mDir == eDirection::RIGHT)
					pos.x += 50.f * Time::DeltaTime();
				else
					pos.x -= 50.f * Time::DeltaTime();
			}

			pos.y += 150.f * Time::DeltaTime();
		}

		case eDefaultKirbyState::Damage:
		{
		}
		break;

		}

		tr->SetPosition(pos);
	}

	void DefaultKirby::Update_Animation()
	{
		// ���¿� ���� �ൿ ����
		switch (mState)
		{
		case eDefaultKirbyState::Idle:
		{
			if (mDir == eDirection::RIGHT)	
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else 	
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Idle", true);
		}
		break;

		case eDefaultKirbyState::Walk:
		{
			if (mDir == eDirection::RIGHT)		
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Walk", true);
			else		
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Walk", true);
		}
		break;

		case eDefaultKirbyState::Run:
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Run", true);
			else	
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Run", true);
		}
		break;

		case eDefaultKirbyState::Jump:
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Jump", false);
	
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Jump", false);
		}
		break;

		case eDefaultKirbyState::Turn:
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Turn", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Turn", false);			
		}
		break;

		case eDefaultKirbyState::Damage:
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"DefaultKirby_Right_Damage", false);
			else
				mAnimator->PlayAnimation(L"DefaultKirby_Left_Damage", false);
		}
		break;

		}
	}
}
