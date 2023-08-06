#include "syPlayer.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syRigidbody.h"
#include "syDefaultKirby.h"
#include "syIceKirby.h"
#include "syInventory.h"
#include "sySceneManager.h"

namespace sy
{
	Player::Player(eAbilityType type, ePlayerMode mode)
		: mKirbyType()
		, mAbilityType(type)
		, mMode(ePlayerMode::LevelMode)
		, mbLevelEnter(false)
		, mHP(100)
		, mLife(3)
		, mHitEnemy(nullptr)
	{
	}

	Player::~Player()
	{
		for (UINT i = 0; i < (UINT)eAbilityType::End; i++)
		{
			if (mKirbyType[i] != nullptr)
			{
				delete mKirbyType[i];
				mKirbyType[i] = nullptr;
			}
		}
	}

	void Player::Initialize()
	{
		// 애니메이터 생성
		AddComponent<Animator>();
		AddComponent<Rigidbody>();
		AddComponent<Collider>()->SetSize(Vector2(15.f, 15.f));

		mKirbyType.resize((UINT)eAbilityType::End);

		mKirbyType[(UINT)eAbilityType::Normal] = new DefaultKirby(this);

		mKirbyType[(UINT)eAbilityType::Fire] = new DefaultKirby(this);



		mKirbyType[(UINT)eAbilityType::Ice] = new IceKirby(this);



		mKirbyType[(UINT)eAbilityType::Cutter] = new DefaultKirby(this);
		mKirbyType[(UINT)eAbilityType::Tornado] = new DefaultKirby(this);
		mKirbyType[(UINT)eAbilityType::Ninja] = new DefaultKirby(this);
	

		for (UINT i = 0; i < (UINT)eAbilityType::End; i++)
		{
			if (mKirbyType[i] != nullptr)
			{
				mKirbyType[i]->Initialize();
			}			
		}

		GameObject::Initialize();
	}

	void Player::Update()
	{
		// 현재 커비의 업데이트 돌려줘야함
		mKirbyType[(UINT)mAbilityType]->Update();

		GameObject::Update();		
	}

	void Player::Render(HDC hdc)
	{
		// 씬에 들어간 현재 커비의 렌더링이 그려짐
		GameObject::Render(hdc);
	}

	void Player::OnCollisionEnter(Collider* other)
	{
		mKirbyType[(UINT)mAbilityType]->OnCollisionEnter(other);
	}

	void Player::OnCollisionStay(Collider* other)
	{
		mKirbyType[(UINT)mAbilityType]->OnCollisionStay(other);
	}

	void Player::OnCollisionExit(Collider* other)
	{
		mKirbyType[(UINT)mAbilityType]->OnCollisionExit(other);
	}

	void Player::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		// 현재 커비의 TakeHit 호출
		mKirbyType[(UINT)mAbilityType]->TakeHit(DamageAmount, HitDir);
	}

	void Player::PlayerTransform(eAbilityType type)
	{
		if (mAbilityType != type)
		{
			mKirbyType[(UINT)mAbilityType]->Exit();
			mAbilityType = type;
			mKirbyType[(UINT)mAbilityType]->Enter();
		}

		if (type == eAbilityType::Normal)
		{
			SceneManager::GetInventory()->GetComponent<Animator>()->PlayAnimation(L"Inventory_Transform_Non", false);
		}
		else if (type == eAbilityType::Fire)
		{
			SceneManager::GetInventory()->GetComponent<Animator>()->PlayAnimation(L"Inventory_Transform_Fire", false);
		}
		else if (type == eAbilityType::Ice)
		{
			SceneManager::GetInventory()->GetComponent<Animator>()->PlayAnimation(L"Inventory_Transform_Ice", false);
		}
		else if (type == eAbilityType::Cutter)
		{
			SceneManager::GetInventory()->GetComponent<Animator>()->PlayAnimation(L"Inventory_Transform_Cutter", false);
		}
		else if (type == eAbilityType::Tornado)
		{
			SceneManager::GetInventory()->GetComponent<Animator>()->PlayAnimation(L"Inventory_Transform_Tornado", false);
		}
	}
}