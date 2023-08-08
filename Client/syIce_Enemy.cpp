#include "syIce_Enemy.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTime.h"
#include "syPlayer.h"
#include "syEnemy.h"
#include "syTransform.h"
#include "sySceneManager.h"

namespace sy
{
	Ice_Enemy::Ice_Enemy(eIceEnemyType type)
		: Enemy(eAbilityType::Ice)
		, mState(eIceEnemyState::Idle)
		, mTransform(nullptr)
		, mDuration(0.f)
	{
		mTransform = GetComponent<Transform>();

		Texture* Monster_Ice = ResourceManager::Load<Texture>(L"Monster_Ice_Tex", L"..\\Resources\\Enemy\\Monster_Ice.bmp");
		Texture* Monster_Death_Tex = ResourceManager::Load<Texture>(L"Monster_Death_Tex", L"..\\Resources\\Effect\\Monster_Death.bmp");

		mAnimator = GetComponent<Animator>();

		Vector2 Animationoffset = Vector2(-1.f, -5.f);
		mAnimator->CreateAnimation(Monster_Ice, L"BigIce", Vector2(0.f, 0.f), Vector2(29.f, 29.f), Vector2(29.f, 5.f), 1.f, 1);
		mAnimator->CreateAnimation(Monster_Ice, L"SmallIce", Vector2(30.f, 0.f), Vector2(21.f, 29.f), Vector2(21.f, 5.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(Monster_Death_Tex, L"Ice_Death", Vector2(0.f, 0.f), Vector2(102.f, 102.f), Vector2(102.f, 0.f), 0.05f, 14);


		if (type == eIceEnemyType::Small)
		{
			mAnimator->PlayAnimation(L"SmallIce");
			GetComponent<Collider>()->SetSize(Vector2(15.f, 15.f)); // Small
		}
		else if (type == eIceEnemyType::Big)
		{
			mAnimator->PlayAnimation(L"BigIce");
			GetComponent<Collider>()->SetSize(Vector2(25.f, 25.f)); // Big
		}	
	}

	Ice_Enemy::~Ice_Enemy()
	{
	}

	void Ice_Enemy::Initialize()
	{
		Enemy::Initialize();
	}

	void Ice_Enemy::Update()
	{
		mDuration += Time::DeltaTime();

		switch (mState)
		{
		case eIceEnemyState::Idle:
			Idle();
			break;
		case eIceEnemyState::Move:
			Move();
			break;
		case eIceEnemyState::Dead:
			Dead();
			break;
		default:
			break;
		}

		Enemy::Update();
	}

	void Ice_Enemy::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void Ice_Enemy::OnCollisionEnter(Collider* other)
	{
		if (mState == eIceEnemyState::Dead)
			return;

		// IceEnemy끼리의 충돌은 적용하지않음
		Ice_Enemy* IceEnemy = dynamic_cast<Ice_Enemy*>(other->GetOwner());
		if (IceEnemy != nullptr)
			return;

		// player 충돌 처리
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player != nullptr)
		{
			mState = eIceEnemyState::Move;

			Vector2 pos = mTransform->GetPosition();
			Vector2 playerpos = player->GetComponent<Transform>()->GetPosition();

			Vector2 Dir = pos - playerpos;
			Dir.Normalize();
			
			if (Dir.x > 0.f)
				mTransform->SetDirection(eDirection::RIGHT);
			else
				mTransform->SetDirection(eDirection::LEFT);
		}

		// Enemy 충돌 처리
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (enemy != nullptr)
		{
			// 스킬 → 몬스터 방향
			Vector2 Dir = enemy->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

			SceneManager::GetPlayer()->SetHitEnemy(enemy);
			enemy->TakeHit(50, Dir);
			enemy->SetHPBarUIRenderTrig(true);
		}
	}

	void Ice_Enemy::OnCollisionStay(Collider* other)
	{
	}

	void Ice_Enemy::OnCollisionExit(Collider* other)
	{
	}

	void Ice_Enemy::Idle()
	{
		if (mDuration > 5.f)
		{
			mState = eIceEnemyState::Dead;
			mAnimator->PlayAnimation(L"Ice_Death", false);
		}
	}

	void Ice_Enemy::Move()
	{
		if (mDuration > 5.f)
		{
			mState = eIceEnemyState::Dead;
			mAnimator->PlayAnimation(L"Ice_Death", false);
		}

		Vector2 pos = mTransform->GetPosition();
		if (mTransform->GetDirection() == eDirection::RIGHT)
			pos.x += 200.f * Time::DeltaTime();
		else
			pos.x -= 200.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void Ice_Enemy::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}
}