#include "syNinjaKirby_Fire.h"
#include "syPlayer.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "sySound.h"
#include "syTransform.h"
#include "syTime.h"
#include "syEnemy.h"
#include "syIce_Enemy.h"
#include "sySceneManager.h"
#include "syRigidbody.h"
#include "syBossEnemy.h"

namespace sy
{
	NinjaKirby_Fire::NinjaKirby_Fire(Player* owner, Vector2 pos)
		: Effects(owner)
		, mAnimator(nullptr)
		, mCollider(nullptr)
		, mTime(0.f)
	{
		GetComponent<Transform>()->SetPosition(pos);

		mAnimator = AddComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(60.f, 20.f));

		Texture* Ninja_Fire = ResourceManager::Load<Texture>(L"Ninja_Fire_Tex", L"..\\Resources\\Effect\\Ninja_Fire.bmp");

		mAnimator->CreateAnimation(Ninja_Fire, L"Ninja_Fire", Vector2(0.f, 0.f), Vector2(60.f, 100.f), Vector2(60.f, 0.f), 0.035f, 19, Vector2(0.f, -40.f));

		mAnimator->PlayAnimation(L"Ninja_Fire", false);

		ResourceManager::Load<Sound>(L"NinjaFireSound", L"..\\Resources\\Sound\\Effect\\NinjaFire.wav")->Play(false);
	}

	NinjaKirby_Fire::~NinjaKirby_Fire()
	{
	}

	void NinjaKirby_Fire::Initialize()
	{
		Effects::Initialize();
	}

	void NinjaKirby_Fire::Update()
	{
		if (mTime >= 0.51f)
		{
			if (mAnimator->IsActiveAnimationComplete())
			{
				Destroy(this);
			}

			mCollider->SetSize(Vector2::Zero);
		}
		else
		{
			mTime += (float)Time::DeltaTime();

			Vector2 size = { 60.f, 20.f };

			size.y += mTime * 150.f;
			float offset = mTime * 150.f / 2.f;

			if (size.y >= 80.f)
			{
				size.y = 80.f;
				offset = 30.f;
			}
			
			mCollider->SetSize(size);
			mCollider->SetOffset(Vector2(0.f, -offset));
		}

		Effects::Update();
	}

	void NinjaKirby_Fire::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void NinjaKirby_Fire::OnCollisionEnter(Collider* other)
	{
		// Plyaer는 무시
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
			return;

		// Ice_Enemy 는 무시
		Ice_Enemy* IceEnemy = dynamic_cast<Ice_Enemy*>(other->GetOwner());
		if (IceEnemy != nullptr)
			return;

		// Dead상태는 무시
		if (other->GetOwner()->GetGameObjectState() == eGameObjectState::Dead)
			return;

		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		if (enemy == nullptr)
			return;

		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
	
		SceneManager::GetPlayer()->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);		
	}

	void NinjaKirby_Fire::OnCollisionStay(Collider* other)
	{
		// Plyaer는 무시
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
			return;

		// Ice_Enemy 는 무시
		Ice_Enemy* IceEnemy = dynamic_cast<Ice_Enemy*>(other->GetOwner());
		if (IceEnemy != nullptr)
			return;

		// Dead상태는 무시
		if (other->GetOwner()->GetGameObjectState() == eGameObjectState::Dead)
			return;

		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		if (enemy == nullptr)
			return;

		// Stay상태에서 Damage 상태면 TakeHit 적용하지않음
		if (!enemy->IsDamagedState())
		{
			Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();

			SceneManager::GetPlayer()->SetHitEnemy(enemy);
			enemy->TakeHit(50, Dir);
			enemy->SetHPBarUIRenderTrig(true);
		}

		// BossEnemy는 이동 적용하지않음
		BossEnemy* bossEnemy = dynamic_cast<BossEnemy*>(other->GetOwner());
		if (bossEnemy != nullptr)
			return;

		// 이동
		Transform* transform = enemy->GetComponent<Transform>();
		Vector2 pos = transform->GetPosition();
		pos.y -= 150.f * Time::DeltaTime();
		transform->SetPosition(pos);

	}
}