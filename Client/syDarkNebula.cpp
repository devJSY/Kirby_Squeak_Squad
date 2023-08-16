#include "syDarkNebula.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "sySceneManager.h"
#include "syPlayer.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syCollider.h"
#include "sySound.h"

namespace sy
{
	DarkNebula::DarkNebula(eAbilityType type)
		: BossEnemy(type)
		, mState(eDarkNebulaState::Idle)
		, mMode(eDarkNebulaMode::Fire)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mStateChangeDelay(0.f)
		, FixedPos{}
		, mbDamaged(false)
	{
		FixedPos[0].x = 40.f;
		FixedPos[0].y = 40.f;

		FixedPos[1].x = 128.f;
		FixedPos[1].y = 40.f;

		FixedPos[2].x = 200.f;
		FixedPos[2].y = 40.f;

		FixedPos[3].x = 40.f;
		FixedPos[3].y = 110.f;

		FixedPos[4].x = 128.f;
		FixedPos[4].y = 96.f;

		FixedPos[5].x = 200.f;
		FixedPos[5].y = 110.f;
	}

	DarkNebula::~DarkNebula()
	{
	}

	void DarkNebula::Initialize()
	{
		// 체력 설정
		SetHP(500);

		// 텍스쳐 로드
		Texture* DarkNebula_Body_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Body_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Body.bmp");
		Texture* DarkNebula_Dead_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Dead_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Dead.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		Collider* col = GetComponent<Collider>();
		col->SetSize(Vector2(40.f, 40.f));

		mTransform->SetPosition(FixedPos[1]);

		// 애니메이션 생성
		std::vector<Vector2> Daroach_StarAttack_offset = { Vector2(0.f,5.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,21.f), Vector2(0.f,26.f), Vector2(0.f, 26.f) };

		mAnimator->CreateAnimation(DarkNebula_Body_Tex, L"DarkNebula_Body_Ice", Vector2::Zero, Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(DarkNebula_Body_Tex, L"DarkNebula_Body_Fire", Vector2(224.f, 0.f), Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(DarkNebula_Body_Tex, L"DarkNebula_Body_Spark", Vector2(448.f, 0.f), Vector2(56.f, 60.f), Vector2(56.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(DarkNebula_Dead_Tex, L"DarkNebula_Dead", Vector2(757.f, 15.f), Vector2(55.f, 56.f), Vector2(-55.f, 0.f), 0.15f, 4);

		mAnimator->PlayAnimation(L"DarkNebula_Body_Ice", true);

		ResourceManager::Load<Sound>(L"BlinkSound", L"..\\Resources\\Sound\\Effect\\Blink.wav");
		ResourceManager::Load<Sound>(L"DN_ChangeSound", L"..\\Resources\\Sound\\Effect\\DN_Change.wav");
		ResourceManager::Load<Sound>(L"DN_DeathSound", L"..\\Resources\\Sound\\Effect\\DN_Death.wav");
		ResourceManager::Load<Sound>(L"DN_MoveSound", L"..\\Resources\\Sound\\Effect\\DN_Move.wav");

		BossEnemy::Initialize();
	}

	void DarkNebula::Update()
	{
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
	}

	void DarkNebula::Render(HDC hdc)
	{
		BossEnemy::Render(hdc);
	}

	void DarkNebula::OnCollisionEnter(Collider* other)
	{
	}

	void DarkNebula::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void DarkNebula::Idle()
	{
	}

	void DarkNebula::Move()
	{
	}

	void DarkNebula::RotationalMove()
	{
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