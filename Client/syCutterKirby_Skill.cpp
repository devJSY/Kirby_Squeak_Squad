#include "syCutterKirby_Skill.h"
#include "syPlayer.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syAnimator.h"
#include "syFireKirby.h"
#include "syObject.h"
#include "syIce_Enemy.h"
#include "sySound.h"
#include "sySoundManager.h"
#include "syCutterKirby.h"
#include "syTime.h"
#include "syInput.h"
#include "syRigidbody.h"

namespace sy
{
	CutterKirby_Skill::CutterKirby_Skill(Player* owner)
		: Effects(owner)
		, mDir()
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mDuration(0.f)
	{
		// Transform
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();
		mTransform = GetComponent<Transform>();

		Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		pos.y -= 10.f;
		mTransform->SetPosition(pos);

		// Collider
		AddComponent<Collider>()->SetSize(Vector2(42.f, 32.f));

		// Rigidbody
		mRigidbody = AddComponent<Rigidbody>();
		if (mDir == eDirection::RIGHT)
			mRigidbody->SetVelocity(Vector2(250.f, 0.f));
		else
			mRigidbody->SetVelocity(Vector2(-250.f, 0.f));

		mRigidbody->SetFloat(true);

		// Animator
		// 텍스쳐 로드
		Texture* CutterKirby_Right = ResourceManager::Load<Texture>(L"CutterKirby_Right_Tex", L"..\\Resources\\Kirby\\CutterKirby\\CutterKirby_Right.bmp");
		Texture* CutterKirby_Left = ResourceManager::Load<Texture>(L"CutterKirby_Left_Tex", L"..\\Resources\\Kirby\\CutterKirby\\CutterKirby_Left.bmp");
		
		Animator* animator = AddComponent<Animator>();

		animator->CreateAnimation(CutterKirby_Right, L"CutterKirby_Right_Skill_Animation", Vector2(200.f, 411.f), Vector2(42.f, 32.f), Vector2(42.f, 0.f), 0.01f, 4);
		animator->CreateAnimation(CutterKirby_Left, L"CutterKirby_Left_Skill_Animation", Vector2(347.f, 411.f), Vector2(42.f, 32.f), Vector2(-42.f, 0.f), 0.01f, 4);

		if (mDir == eDirection::RIGHT)
			animator->PlayAnimation(L"CutterKirby_Right_Skill_Animation", true);
		else
			animator->PlayAnimation(L"CutterKirby_Left_Skill_Animation", true);

		ResourceManager::Load<Sound>(L"CutterKirby_Skill_HitSound", L"..\\Resources\\Sound\\Effect\\CutterSkill.wav");
		ResourceManager::Load<Sound>(L"CutterKirby_Skill_Sound", L"..\\Resources\\Sound\\Effect\\CutterSkill2.wav");
		ResourceManager::Find<Sound>(L"CutterKirby_Skill_Sound")->Play(false);
	
	}

	CutterKirby_Skill::~CutterKirby_Skill()
	{
	}

	void CutterKirby_Skill::Initialize()
	{
		Effects::Initialize();
	}

	void CutterKirby_Skill::Update()
	{
		mDuration += Time::DeltaTime();

		// 일정시간뒤 자동삭제
		if (mDuration > 10.f)
		{
			ResourceManager::Find<Sound>(L"CutterKirby_Skill_Sound")->Stop(true);
			ResourceManager::Find<Sound>(L"CutterKirby_Skill_HitSound")->Play(false);
			Destroy(this);
		}

		Player* player = dynamic_cast<Player*>(GetOwner());
		CutterKirby* cutterKirby = dynamic_cast<CutterKirby*>(player->GetActiveKirby());

		// Cutter 커비의 Skill 인 상태에서만 키입력 적용
		if (cutterKirby != nullptr && cutterKirby->GetKirbyState() == eCutterKirbyState::Skill)
		{
			// 상하 이동
			Vector2 pos = mTransform->GetPosition();

			if (Input::GetKeyPressed(eKeyCode::UP))
				pos.y -= 80.f * Time::DeltaTime();
			else if(Input::GetKeyPressed(eKeyCode::DOWN))
				pos.y += 80.f * Time::DeltaTime();

			mTransform->SetPosition(pos);
		}

		// 이동
		if (mDir == eDirection::RIGHT)
			mRigidbody->AddForce(Vector2(-250.f, 0.f));
		else
			mRigidbody->AddForce(Vector2(250.f, 0.f));

		Effects::Update();
	}

	void CutterKirby_Skill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void CutterKirby_Skill::OnCollisionEnter(Collider* other)
	{
		// 플레이어와 충돌한경우 삭제
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			if (mDuration > 1.f)
			{
				ResourceManager::Find<Sound>(L"CutterKirby_Skill_Sound")->Stop(true);
				ResourceManager::Find<Sound>(L"CutterKirby_Skill_HitSound")->Play(false);
				Destroy(this);
				return;
			}
			else
				return;
		}

		// Ice_Enemy 는 무시
		Ice_Enemy* IceEnemy = dynamic_cast<Ice_Enemy*>(other->GetOwner());
		if (IceEnemy != nullptr)
			return;

		// Dead상태는 무시
		if (other->GetOwner()->GetGameObjectState() == eGameObjectState::Dead)
			return;

		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();

		SceneManager::GetPlayer()->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	}

	void CutterKirby_Skill::OnCollisionStay(Collider* other)
	{
		// 플레이어와 충돌한경우 삭제
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
		{
			if (mDuration > 1.f)
			{
				ResourceManager::Find<Sound>(L"CutterKirby_Skill_Sound")->Stop(true);
				ResourceManager::Find<Sound>(L"CutterKirby_Skill_HitSound")->Play(false);
				Destroy(this);
				return;
			}
			else
				return;
		}

		// Ice_Enemy 는 무시
		Ice_Enemy* IceEnemy = dynamic_cast<Ice_Enemy*>(other->GetOwner());
		if (IceEnemy != nullptr)
			return;

		// Dead상태는 무시
		if (other->GetOwner()->GetGameObjectState() == eGameObjectState::Dead)
			return;

		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();

		SceneManager::GetPlayer()->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	}
}