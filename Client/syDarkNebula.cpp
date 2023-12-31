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
#include "syCamera.h"
#include "syDarkNebula_Star.h"
#include "syObject.h"
#include "syDarkNebula_IceSkill.h"
#include "syDarkNebula_FireBall.h"
#include "syDarkNebula_SparkBolt.h"
#include "syDarkNebula_SparkSkill.h"
#include "syDarkNebula_DeadStar.h"

namespace sy
{
	DarkNebula::DarkNebula(eAbilityType type)
		: BossEnemy(type)
		, mState(eDarkNebulaState::Idle)
		, mMode(eDarkNebulaMode::Fire)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mDir(eDirection::RIGHT)
		, mStateChangeDelay(-3.f)
		, mModeChangeDelay(0.f)
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
		mFixedPos[4].y = 71.f;

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
		// 체력 설정
		SetHP(1000);

		// 텍스쳐 로드
		Texture* DarkNebula_Body_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Body_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Body.bmp");
		Texture* DarkNebula_Dead_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Dead_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Dead.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		Collider* col = GetComponent<Collider>();
		col->SetSize(Vector2(40.f, 40.f));
		col->SetOffset(Vector2(0.f, 3.f));

		mTransform->SetPosition(mFixedPos[1]);

		// 애니메이션 생성
		std::vector<Vector2> Daroach_StarAttack_offset = { Vector2(0.f,5.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,21.f), Vector2(0.f,26.f), Vector2(0.f, 26.f) };

		mAnimator->CreateAnimation(DarkNebula_Body_Tex, L"DarkNebula_Body_Ice", Vector2::Zero, Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(DarkNebula_Body_Tex, L"DarkNebula_Body_Fire", Vector2(224.f, 0.f), Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(DarkNebula_Body_Tex, L"DarkNebula_Body_Spark", Vector2(448.f, 0.f), Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(DarkNebula_Dead_Tex, L"DarkNebula_Dead", Vector2::Zero, Vector2(60.f, 65.f), Vector2(60.f, 0.f), 0.5f, 10);

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
		mDir = mTransform->GetDirection();

		// 데미지 딜레이 설정
		static float DamageDelayTime = 0.f;
		if (mbDamaged)
			DamageDelayTime += Time::DeltaTime();

		if (DamageDelayTime > 1.f)
		{
			mbDamaged = false;
			DamageDelayTime = 0.f;
		}

		// 모드 변환 Idle에서 적용
		mModeChangeDelay += Time::DeltaTime();

		// 테스트용 상태변경
		SetBossState();
		
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
		case eDarkNebulaState::ZigzagMoveReady:
			ZigzagMoveReady();
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
		case eDarkNebulaState::ModeChangeReady:
			ModeChangeReady();
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
		if (mState == eDarkNebulaState::Dead)
			return;

		// 특정 조건 에서만 충돌처리
		if (mState != eDarkNebulaState::Move 
			&& mState != eDarkNebulaState::RotationalMove
			&& mState != eDarkNebulaState::ZigzagMoveReady
			&& mState != eDarkNebulaState::ZigzagMove)
			return;

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr)
			return;

		// 몬스터 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

		player->TakeHit(10, Dir);
	}

	void DarkNebula::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		Damaged(DamageAmount);

		// 이미 데미지 상태면 애니메이션, 피격 넉백 처리하지않음
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
			mEye->GetComponent<Animator>()->PlayAnimation(L"DarkNebula_Eye_Flash", true);
		}

		mbDamaged = true;
	}

	void DarkNebula::SetBossState()
	{
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

			// 방향 랜덤 설정
			int randomDir = std::rand() % 100;
			if (randomDir % 2 == 0)
				mTransform->SetDirection(eDirection::RIGHT);
			else
				mTransform->SetDirection(eDirection::LEFT);

			mDir = mTransform->GetDirection();
		}

		if (Input::GetKeyDown(eKeyCode::Three))
		{
			mState = eDarkNebulaState::ZigzagMoveReady;
			mStateChangeDelay = 0.f;
			int idx = std::rand() % 6;
			mTargetPos = mFixedPos[idx];

			// 방향 랜덤 설정
			int randomDir = std::rand() % 100;
			if (randomDir % 2 == 0)
				mTransform->SetDirection(eDirection::RIGHT);
			else
				mTransform->SetDirection(eDirection::LEFT);

			mDir = mTransform->GetDirection();

			if (mDir == eDirection::RIGHT)
				mTargetPos = mFixedPos[3];
			else
				mTargetPos = mFixedPos[5];
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

			if (mMode == eDarkNebulaMode::Fire)
			{
				mTargetPos = mFixedPos[1];
			}
			else if (mMode == eDarkNebulaMode::Ice)
			{
				if (mDir == eDirection::RIGHT)
					mTargetPos = mFixedPos[0];
				else
					mTargetPos = mFixedPos[2];
			}
			else if (mMode == eDarkNebulaMode::Spark)
			{
				mTargetPos = mFixedPos[4];
			}
		}

		if (Input::GetKeyDown(eKeyCode::Six))
		{
			mState = eDarkNebulaState::ModeChangeReady;
			mModeChangeDelay = 0.f;
			mTargetPos = mFixedPos[1];
		}
	}

	void DarkNebula::Idle()
	{
		// 상태처리
		mStateChangeDelay += Time::DeltaTime();

		if (mModeChangeDelay > 20.f)
		{
			mState = eDarkNebulaState::ModeChangeReady;
			mTargetPos = mFixedPos[1];
			mModeChangeDelay = 0.f;
		}
		else
		{
			if (mStateChangeDelay >= 0.5f)
			{
				mStateChangeDelay = 0.f;

				// 방향 랜덤 설정
				int randomDir = std::rand() % 100;
				if (randomDir % 2 == 0)
					mTransform->SetDirection(eDirection::RIGHT);
				else
					mTransform->SetDirection(eDirection::LEFT);

				mDir = mTransform->GetDirection();

				int randomNumber = std::rand() % 5;
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
					mState = eDarkNebulaState::ZigzagMoveReady;
					int idx = std::rand() % 6;
					mTargetPos = mFixedPos[idx];

					if (mDir == eDirection::RIGHT)
						mTargetPos = mFixedPos[3];
					else
						mTargetPos = mFixedPos[5];
				}
				else if (randomNumber == 3)
				{
					mState = eDarkNebulaState::StarAttack;
				}
				else if (randomNumber == 4)
				{
					mState = eDarkNebulaState::SkillReady;
					mEye->GetComponent<Animator>()->PlayAnimation(L"DarkNebula_Eye_Flash", true);
					
					if (mMode == eDarkNebulaMode::Fire)
					{
						mTargetPos = mFixedPos[1];
					}
					else if (mMode == eDarkNebulaMode::Ice)
					{
						if(mDir == eDirection::RIGHT)
							mTargetPos = mFixedPos[0];
						else
							mTargetPos = mFixedPos[2];
					}
					else if (mMode == eDarkNebulaMode::Spark)
					{
						mTargetPos = mFixedPos[4];
					}
				}
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
		static float t = 0.f;	// 0 ~ 1값 곡선상에서 비율
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
			// 곡선을 따라 이동할 거리 양수면 오른쪽커브, 음수면 왼쪽커브
			float radius = 5.f;

			if(mTransform->GetDirection() == eDirection::RIGHT)
				radius = 5.f;
			else
				radius = -5.f;

			mTransform->SetPosition(moveAlongCurve(pos, mTargetPos, radius, t));
		}
	}

	void DarkNebula::ZigzagMoveReady()
	{
		Vector2 pos = mTransform->GetPosition();

		Vector2 Diff = mTargetPos - pos;

		if (Diff.Length() <= 1.f)
		{
			mState = eDarkNebulaState::ZigzagMove;
		}
		else
		{
			Diff.Normalize();
			Diff *= 200.f * Time::DeltaTime();
			pos += Diff;
			mTransform->SetPosition(pos);
		}
	}


	void DarkNebula::ZigzagMove()
	{
		mStateChangeDelay += Time::DeltaTime();
		static float angle = 0.f;

		if (mStateChangeDelay > 3.f)
		{
			if (mDir == eDirection::RIGHT)
				mTargetPos = mFixedPos[5];
			else
				mTargetPos = mFixedPos[3];

			mState = eDarkNebulaState::Move;
			mStateChangeDelay = 0.f;
			angle = 0.f;
		}

		Vector2 pos = mTransform->GetPosition();

		if (mDir == eDirection::RIGHT)
			pos.x += 50.f * Time::DeltaTime();
		else
			pos.x -= 50.f * Time::DeltaTime();
		
		// 초당 5도
		angle += 5.f * (float)Time::DeltaTime();
		// 2π (2.0f * 3.1415f)는 한 바퀴(360도)에 해당하는 각도
		if (angle > 2.0f * 3.1415f)
		{
			angle -= 2.0f * 3.1415f;
		}

		pos.y += std::cos(angle) * 300.f * Time::DeltaTime();

		mTransform->SetPosition(pos);
	}

	void DarkNebula::StarAttack()
	{
		static int cnt = 5;
		mStateChangeDelay += Time::DeltaTime();

		if (cnt <= 0.f)
		{
			mState = eDarkNebulaState::Idle;
			cnt = 5;
			mStateChangeDelay = 0.f;
		}
		else
		{
			if (mStateChangeDelay > 0.2f)
			{
				Vector2 Dir = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();
				DarkNebula_Star* star = new DarkNebula_Star(this, Dir);
				object::ActiveSceneAddGameObject(eLayerType::Effect, star);

				mStateChangeDelay = 0.f;
				--cnt;
			}
		}
	}

	void DarkNebula::SkillReady()
	{
		Vector2 pos = mTransform->GetPosition();

		Vector2 Diff = mTargetPos - pos;

		if (Diff.Length() <= 1.f)
		{		
			mStateChangeDelay = 0.f;
			mEye->GetComponent<Animator>()->PlayAnimation(L"DarkNebula_Eye", true);

			if (mMode == eDarkNebulaMode::Fire)
			{
				mState = eDarkNebulaState::FireSkill;

				DarkNebula_FireBall* skill = new DarkNebula_FireBall(this);
				object::ActiveSceneAddGameObject(eLayerType::Effect, skill);
			}
			else if (mMode == eDarkNebulaMode::Ice)
			{
				if (mDir == eDirection::RIGHT)
					mTargetPos = mFixedPos[2];
				else
					mTargetPos = mFixedPos[0];

				mState = eDarkNebulaState::IceSkill;
				DarkNebula_IceSkill* skill = new DarkNebula_IceSkill(this);
				object::ActiveSceneAddGameObject(eLayerType::Effect, skill);
			}
			else if (mMode == eDarkNebulaMode::Spark)
			{
				mState = eDarkNebulaState::SparkSkill;

				DarkNebula_SparkBolt* RT = new DarkNebula_SparkBolt(this, eCornerDirection::RightTop);
				object::ActiveSceneAddGameObject(eLayerType::Effect, RT);

				DarkNebula_SparkBolt* LT = new DarkNebula_SparkBolt(this, eCornerDirection::LeftTop);
				object::ActiveSceneAddGameObject(eLayerType::Effect, LT);

				DarkNebula_SparkBolt* RB = new DarkNebula_SparkBolt(this, eCornerDirection::RightBottom);
				object::ActiveSceneAddGameObject(eLayerType::Effect, RB);

				DarkNebula_SparkBolt* LB = new DarkNebula_SparkBolt(this, eCornerDirection::LeftBottom);
				object::ActiveSceneAddGameObject(eLayerType::Effect, LB);
			}
		}
		else
		{
			Diff.Normalize();
			Diff *= 200.f * Time::DeltaTime();
			pos += Diff;
			mTransform->SetPosition(pos);
		}
	}

	void DarkNebula::FireSkill()
	{
		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 5.f)
		{
			mState = eDarkNebulaState::Idle;
			mStateChangeDelay = 0.f;
		}
	}

	void DarkNebula::IceSkill()
	{
		Vector2 pos = mTransform->GetPosition();

		Vector2 Diff = mTargetPos - pos;

		if (Diff.Length() <= 1.f)
		{
			mState = eDarkNebulaState::Idle;
		}
		else
		{
			Diff.Normalize();
			Diff *= 30.f * Time::DeltaTime();
			pos += Diff;
			mTransform->SetPosition(pos);
		}
	}

	void DarkNebula::SparkSkill()
	{
		static bool bActive = true;
		mStateChangeDelay += Time::DeltaTime();

		if (bActive && mStateChangeDelay > 2.f)
		{
			DarkNebula_SparkSkill* skill = new DarkNebula_SparkSkill(this);
			object::ActiveSceneAddGameObject(eLayerType::Effect, skill);			
			bActive = false;
		}

		if (mStateChangeDelay > 5.f)
		{
			mState = eDarkNebulaState::Idle;
			mStateChangeDelay = 0.f;
			bActive = true;
		}
	}

	void DarkNebula::ModeChangeReady()
	{
		Vector2 pos = mTransform->GetPosition();

		Vector2 Diff = mTargetPos - pos;

		if (Diff.Length() <= 1.f)
		{
			Camera::fadeOut(1.f, RGB(255, 255, 255));
			

			int randomMode = std::rand() % 100;

			if (mMode == eDarkNebulaMode::Fire)
			{
				if (randomMode % 2 == 0)
					mMode = eDarkNebulaMode::Ice;
				else
					mMode = eDarkNebulaMode::Spark;
			}
			else if (mMode == eDarkNebulaMode::Ice)
			{
				if (randomMode % 2 == 0)
					mMode = eDarkNebulaMode::Fire;
				else
					mMode = eDarkNebulaMode::Spark;
			}
			else if (mMode == eDarkNebulaMode::Spark)
			{
				if (randomMode % 2 == 0)
					mMode = eDarkNebulaMode::Fire;
				else
					mMode = eDarkNebulaMode::Ice;
			}

			mState = eDarkNebulaState::ModeChange;
			mEye->GetComponent<Animator>()->PlayAnimation(L"DarkNebula_Eye_ModeChange", false);
		}
		else
		{
			Diff.Normalize();
			Diff *= 200.f * Time::DeltaTime();
			pos += Diff;
			mTransform->SetPosition(pos);
		}
	}

	void DarkNebula::ModeChange()
	{
		if (Camera::IsEmptyCamEffect())
		{
			if (mMode == eDarkNebulaMode::Fire)
				mAnimator->PlayAnimation(L"DarkNebula_Body_Fire", true);
			else if (mMode == eDarkNebulaMode::Ice)
				mAnimator->PlayAnimation(L"DarkNebula_Body_Ice", true);
			else if (mMode == eDarkNebulaMode::Spark)
				mAnimator->PlayAnimation(L"DarkNebula_Body_Spark", true);
			Camera::fadeIn(1.f, RGB(255, 255, 255));
			mState = eDarkNebulaState::Idle;
			mModeChangeDelay = 0.f;
			mEye->GetComponent<Animator>()->PlayAnimation(L"DarkNebula_Eye", true);
		}
	}

	void DarkNebula::Dead()
	{
		static float eyeDeadTime = 0.f;
		eyeDeadTime += Time::DeltaTime();

		static bool trig = true;

		if (trig)
		{
			if (eyeDeadTime > 9.f)
			{
				if (mEye != nullptr)
				{
					mEye->GetComponent<Animator>()->PlayAnimation(L"DarkNebula_Eye_ModeChange", false);
					trig = false;
				}
			}
			else
			{
				static float DeadStarTime = 0.f;
				DeadStarTime += Time::DeltaTime();

				if (DeadStarTime > 0.1f)
				{
					// 데스스타 생성
					DarkNebula_DeadStar* deadStar = new DarkNebula_DeadStar(this, eDirection::RIGHT);
					object::ActiveSceneAddGameObject(eLayerType::Effect, deadStar);
					DarkNebula_DeadStar* deadStar2 = new DarkNebula_DeadStar(this, eDirection::LEFT);
					object::ActiveSceneAddGameObject(eLayerType::Effect, deadStar2);
					DeadStarTime = 0.f;
				}
			}
		}

		if (mEye != nullptr)
		{
			if (mEye->GetComponent<Animator>()->IsActiveAnimationComplete())
			{
				delete mEye;
				mEye = nullptr;
			}
		}
	}
}