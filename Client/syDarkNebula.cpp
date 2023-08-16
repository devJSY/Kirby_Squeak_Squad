#include "syDarkNebula.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "sySceneManager.h"
#include "syPlayer.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syCollider.h"
#include "sySound.h"
#include "syDarkNebula_Border.h"
#include "syDarkNebula_Eye.h"
#include "syTime.h"
#include "syInput.h"

namespace sy
{
	DarkNebula::DarkNebula(eAbilityType type)
		: BossEnemy(type)
		, mState(eDarkNebulaState::Idle)
		, mMode(eDarkNebulaMode::Fire)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mStateChangeDelay(0.f)
		, mFixedPos{}
		, mTargetPos(Vector2::Zero)
		, mbDamaged(false)
		, mBorder(nullptr)
		, mEye(nullptr)
	{
		mFixedPos[0].x = 40.f;
		mFixedPos[0].y = 40.f;

		mFixedPos[1].x = 128.f;
		mFixedPos[1].y = 40.f;

		mFixedPos[2].x = 200.f;
		mFixedPos[2].y = 40.f;

		mFixedPos[3].x = 40.f;
		mFixedPos[3].y = 110.f;

		mFixedPos[4].x = 128.f;
		mFixedPos[4].y = 96.f;

		mFixedPos[5].x = 200.f;
		mFixedPos[5].y = 110.f;

		mBorder = new DarkNebula_Border(this);
		mEye = new DarkNebula_Eye(this);
	}

	DarkNebula::~DarkNebula()
	{
		if (mBorder != nullptr)
		{
			delete mBorder;
			mBorder = nullptr;
		}

		if (mEye != nullptr)
		{
			delete mEye;
			mEye = nullptr;
		}		
	}

	void DarkNebula::Initialize()
	{
		// ü�� ����
		SetHP(500);

		// �ؽ��� �ε�
		Texture* DarkNebula_Body_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Body_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Body.bmp");
		Texture* DarkNebula_Dead_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Dead_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Dead.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		Collider* col = GetComponent<Collider>();
		col->SetSize(Vector2(40.f, 40.f));

		mTransform->SetPosition(mFixedPos[1]);

		// �ִϸ��̼� ����
		std::vector<Vector2> Daroach_StarAttack_offset = { Vector2(0.f,5.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,21.f), Vector2(0.f,26.f), Vector2(0.f, 26.f) };

		mAnimator->CreateAnimation(DarkNebula_Body_Tex, L"DarkNebula_Body_Ice", Vector2::Zero, Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(DarkNebula_Body_Tex, L"DarkNebula_Body_Fire", Vector2(224.f, 0.f), Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(DarkNebula_Body_Tex, L"DarkNebula_Body_Spark", Vector2(448.f, 0.f), Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(DarkNebula_Dead_Tex, L"DarkNebula_Dead", Vector2::Zero, Vector2(60.f, 65.f), Vector2(60.f, 0.f), 0.1f, 9);

		mAnimator->PlayAnimation(L"DarkNebula_Body_Fire", true);

		ResourceManager::Load<Sound>(L"BlinkSound", L"..\\Resources\\Sound\\Effect\\DarkNebula\\Blink.wav");
		ResourceManager::Load<Sound>(L"DarkNebula_MoveSound", L"..\\Resources\\Sound\\Effect\\DarkNebula\\DarkNebula_Move.wav");
		ResourceManager::Load<Sound>(L"DarkNebula_DeadSound", L"..\\Resources\\Sound\\Effect\\DarkNebula\\DarkNebula_Dead.wav");
		ResourceManager::Load<Sound>(L"DarkNebula_ChangeSound", L"..\\Resources\\Sound\\Effect\\DarkNebula\\DarkNebula_Change.wav");
	
		BossEnemy::Initialize();

		if (mBorder != nullptr)
			mBorder->Initialize();
		if (mEye != nullptr)
			mEye->Initialize();
	}

	void DarkNebula::Update()
	{
		// ������ ������ ����
		static float DamageDelayTime = 0.f;
		if (mbDamaged)
			DamageDelayTime += Time::DeltaTime();

		if (DamageDelayTime > 1.f)
		{
			mbDamaged = false;
			DamageDelayTime = 0.f;
		}

		// �׽�Ʈ�� ���º���
		if (Input::GetKeyDown(eKeyCode::One))
		{
			mState = eDarkNebulaState::Move;
			mStateChangeDelay = 0.f;
			int idx = std::rand() % 6;
			mTargetPos = mFixedPos[idx];
		}

		if (Input::GetKeyDown(eKeyCode::Two))
		{
			mState = eDarkNebulaState::RotationalMove;
			mStateChangeDelay = 0.f;
			int idx = std::rand() % 6;
			mTargetPos = mFixedPos[idx];

			// ���� ���� ����
			int randomDir = std::rand() % 100;
			if (randomDir % 2 == 0)
				mTransform->SetDirection(eDirection::RIGHT);
			else
				mTransform->SetDirection(eDirection::LEFT);
		}

		if (Input::GetKeyDown(eKeyCode::Three))
		{
			mState = eDarkNebulaState::ZigzagMove;
			mStateChangeDelay = 0.f;
			int idx = std::rand() % 6;
			mTargetPos = mFixedPos[idx];

			// ���� ���� ����
			int randomDir = std::rand() % 100;
			if (randomDir % 2 == 0)
				mTransform->SetDirection(eDirection::RIGHT);
			else
				mTransform->SetDirection(eDirection::LEFT);
		}

		if (Input::GetKeyDown(eKeyCode::Four))
		{
			mState = eDarkNebulaState::StarAttack;
			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Five))
		{
			mState = eDarkNebulaState::SkillReady;
			mStateChangeDelay = 0.f;
		}

		if (Input::GetKeyDown(eKeyCode::Six))
		{
			mState = eDarkNebulaState::ModeChange;
			mStateChangeDelay = 0.f;
		}
		
		switch (mState)
		{
		case eDarkNebulaState::Idle:
			Idle();
			break;
		case eDarkNebulaState::Move:
			Move();
			break;
		case eDarkNebulaState::RotationalMove:
			RotationalMove();
			break;
		case eDarkNebulaState::ZigzagMove:
			ZigzagMove();
			break;
		case eDarkNebulaState::StarAttack:
			StarAttack();
			break;
		case eDarkNebulaState::SkillReady:
			SkillReady();
			break;
		case eDarkNebulaState::FireSkill:
			FireSkill();
			break;
		case eDarkNebulaState::IceSkill:
			IceSkill();
			break;
		case eDarkNebulaState::SparkSkill:
			SparkSkill();
			break;
		case eDarkNebulaState::ModeChange:
			ModeChange();
			break;
		case eDarkNebulaState::Dead:
			Dead();
			break;
		default:
			break;
		}

		BossEnemy::Update();

		if (mBorder != nullptr)
			mBorder->Update();
		if (mEye != nullptr)
			mEye->Update();	
	}

	void DarkNebula::Render(HDC hdc)
	{
		BossEnemy::Render(hdc);

		if (mBorder != nullptr)
			mBorder->Render(hdc);
		if (mEye != nullptr)
			mEye->Render(hdc);
	}

	void DarkNebula::OnCollisionEnter(Collider* other)
	{
	}

	void DarkNebula::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		Damaged(DamageAmount);

		// �̹� ������ ���¸� �ִϸ��̼�, �ǰ� �˹� ó����������
		if (mbDamaged || mState == eDarkNebulaState::Dead)
			return;

		if (GetCurHP() <= 0.f)
		{
			mAnimator->PlayAnimation(L"DarkNebula_Dead", false);
			ResourceManager::Find<Sound>(L"DarkNebula_DeadSound")->Play(false);	

			if (mBorder != nullptr)
			{
				delete mBorder;
				mBorder = nullptr;
			}

			mState = eDarkNebulaState::Dead;
		}

		mbDamaged = true;
	}

	void DarkNebula::Idle()
	{
		// ����ó��
		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay >= 3.f)
		{
			mStateChangeDelay = 0.f;

			// ���� ���� ����
			int randomDir = std::rand() % 100;
			if (randomDir % 2 == 0)
				mTransform->SetDirection(eDirection::RIGHT);
			else
				mTransform->SetDirection(eDirection::LEFT);

			int randomNumber = std::rand() % 6;
			if (randomNumber == 0)
			{
				mState = eDarkNebulaState::Move;
				int idx = std::rand() % 6;
				mTargetPos = mFixedPos[idx];
			}
			else if (randomNumber == 1)
			{
				mState = eDarkNebulaState::RotationalMove;

				int idx = std::rand() % 6;
				mTargetPos = mFixedPos[idx];
			}
			else if (randomNumber == 2)
			{
				mState = eDarkNebulaState::ZigzagMove;
				int idx = std::rand() % 6;
				mTargetPos = mFixedPos[idx];
			}
			else if (randomNumber == 3)
			{
				mState = eDarkNebulaState::StarAttack;
			}
			else if (randomNumber == 4)
			{
				mState = eDarkNebulaState::SkillReady;
			}
			else if (randomNumber == 5)
			{
				mState = eDarkNebulaState::ModeChange;
			}
		}
	}

	void DarkNebula::Move()
	{
		Vector2 pos = mTransform->GetPosition();
		
		Vector2 Diff = mTargetPos - pos;

		if(Diff.Length() <= 1.f)
		{
			mState = eDarkNebulaState::Idle;
		}
		else
		{
			Diff.Normalize();
			Diff *= 200.f * Time::DeltaTime();
			pos += Diff;
			mTransform->SetPosition(pos);
		}
	}

	void DarkNebula::RotationalMove()
	{
		static float t = 0.f;	// 0 ~ 1�� ��󿡼� ����
		t += 0.3f * Time::DeltaTime(); 

		Vector2 pos = mTransform->GetPosition();
		Vector2 Diff = mTargetPos - pos;

		if (Diff.Length() <= 1.f)
		{
			t = 0.f;

			mState = eDarkNebulaState::Idle;
		}
		else
		{
			// ��� ���� �̵��� �Ÿ� ����� ������Ŀ��, ������ ����Ŀ��
			float radius = 5.f;

			if(mTransform->GetDirection() == eDirection::RIGHT)
				radius = 5.f;
			else
				radius = -5.f;

			mTransform->SetPosition(moveAlongCurve(pos, mTargetPos, radius, t));
		}
	}


	void DarkNebula::ZigzagMove()
	{

	}

	void DarkNebula::StarAttack()
	{

	}

	void DarkNebula::SkillReady()
	{

	}

	void DarkNebula::FireSkill()
	{
	}

	void DarkNebula::IceSkill()
	{
	}

	void DarkNebula::SparkSkill()
	{
	}

	void DarkNebula::ModeChange()
	{
	}

	void DarkNebula::Dead()
	{
	}
}