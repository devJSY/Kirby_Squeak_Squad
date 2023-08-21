#include "syPlayer.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syRigidbody.h"
#include "syInventory.h"
#include "sySceneManager.h"
#include "syTransform.h"
#include "syKirby.h"
#include "syDefaultKirby.h"
#include "syFireKirby.h"
#include "syIceKirby.h"
#include "syCutterKirby.h"
#include "syTornadoKirby.h"
#include "sySound.h"
#include "sySoundManager.h"
#include "syResourceManager.h"
#include "syNinjaKirby.h"
#include "sySparkKirby.h"
#include "syWheelKirby.h"
#include "syTime.h"
#include "syTransformEffect.h"
#include "syObject.h"
#include "syCamera.h"

namespace sy
{
	Player::Player(eAbilityType type, ePlayerMode mode)
		: mKirbyType()
		, mAbilityType(type)
		, mMode(ePlayerMode::LevelMode)
		, mbLevelEnter(false)
		, mMaxHp(100)
		, mCurHp(mMaxHp)
		, mLife(9)
		, mHitEnemy(nullptr)
		, mbDamaged(false)
		, mDamageDelay(0.f)
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
		// �ִϸ����� ����
		AddComponent<Animator>();
		AddComponent<Rigidbody>();
		AddComponent<Collider>()->SetSize(Vector2(15.f, 15.f));

		mKirbyType.resize((UINT)eAbilityType::End);

		mKirbyType[(UINT)eAbilityType::Normal] = new DefaultKirby(this);
		mKirbyType[(UINT)eAbilityType::Fire] = new FireKirby(this);
		mKirbyType[(UINT)eAbilityType::Ice] = new IceKirby(this);
		mKirbyType[(UINT)eAbilityType::Cutter] = new CutterKirby(this);
		mKirbyType[(UINT)eAbilityType::Tornado] = new TornadoKirby(this);
		mKirbyType[(UINT)eAbilityType::Ninja] = new NinjaKirby(this);
		mKirbyType[(UINT)eAbilityType::Spark] = new SparkKirby(this);
		//mKirbyType[(UINT)eAbilityType::Wheel] = new WheelKirby(this);
	

		for (UINT i = 0; i < (UINT)eAbilityType::End; i++)
		{
			if (mKirbyType[i] != nullptr)
			{
				mKirbyType[i]->Initialize();
			}			
		}


		ResourceManager::Load<Sound>(L"Transform_Sound", L"..\\Resources\\Sound\\Effect\\Transform.wav");

		GameObject::Initialize();
	}

	void Player::Update()
	{
		// ���� Ŀ���� ������Ʈ ���������
		mKirbyType[(UINT)mAbilityType]->Update();

		GameObject::Update();		

		// �ӽ� ü�� ������ó��
		if (mCurHp <= 0.f)
		{
			mCurHp = 100;

			if (mLife > 0)
			{
				mLife -= 1;
			}		
		}

		if (mbDamaged)
		{
			mDamageDelay += Time::DeltaTime();

			if (mDamageDelay > 2.f)
			{
				mbDamaged = false;
				GetComponent<Animator>()->SetBlink(false);
				mDamageDelay = 0.f;
			}
		}

		if (mMode == ePlayerMode::LevelMode)
		{
			GetComponent<Animator>()->SetBlink(false);
		}
	}

	void Player::Render(HDC hdc)
	{
		// ���� �� ���� Ŀ���� �������� �׷���
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
		// ���� Ŀ���� TakeHit ȣ��
		if (!mbDamaged)
		{
			mbDamaged = true;
			GetComponent<Animator>()->SetBlink(true);
			mKirbyType[(UINT)mAbilityType]->TakeHit(DamageAmount, HitDir);
		}
	}

	void Player::PlayerTransformations(eAbilityType type)
	{
		// ������ �Ұ����� ���¸� return
		if (!mKirbyType[(UINT)mAbilityType]->IsTransformableCheck())
			return;

		GetComponent<Rigidbody>()->SetLimitVelocity(Vector2(300.f, 300.f));
		GetComponent<Rigidbody>()->SetVelocity(Vector2(0.f, 0.f));

		if (mAbilityType != type)
		{
			mKirbyType[(UINT)mAbilityType]->Exit();
			mAbilityType = type;
			mKirbyType[(UINT)mAbilityType]->Enter();

			if (type != eAbilityType::Normal)
			{
				ResourceManager::Find<Sound>(L"Transform_Sound")->Play(false);

				TransformEffect* effect = new TransformEffect(this);
				object::ActiveSceneAddGameObject(eLayerType::TransformEffect, effect);

				// ī�޶�ȿ��
				if (mMode == ePlayerMode::PlayMode)
				{
					Camera::Transformations(1.f, RGB(0, 0, 0));
				}
			}
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
		else if (type == eAbilityType::Ninja)
		{
			SceneManager::GetInventory()->GetComponent<Animator>()->PlayAnimation(L"Inventory_Transform_Ninja", false);
		}
		else if (type == eAbilityType::Spark)
		{
			SceneManager::GetInventory()->GetComponent<Animator>()->PlayAnimation(L"Inventory_Transform_Spark", false);
		}
	}

	void Player::ReleaseTransformations(eDefaultKirbyState state)
	{
		mAbilityType = eAbilityType::Normal;
		Kirby* kirby = mKirbyType[(UINT)mAbilityType];
		DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(kirby);
		defaultKirby->SetKirbyState(state);
		GetComponent<Rigidbody>()->SetLimitVelocity(Vector2(300.f, 300.f));
		GetComponent<Rigidbody>()->SetVelocity(Vector2(0.f, 0.f));
		
		if (state == eDefaultKirbyState::Idle)
		{
			if (GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
				GetComponent<Animator>()->PlayAnimation(L"DefaultKirby_Right_Idle", true);
			else
				GetComponent<Animator>()->PlayAnimation(L"DefaultKirby_Left_Idle", true);
		}
		else if (state == eDefaultKirbyState::Walk)
		{
			if (GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
				GetComponent<Animator>()->PlayAnimation(L"DefaultKirby_Right_Walk", true);
			else
				GetComponent<Animator>()->PlayAnimation(L"DefaultKirby_Left_Walk", true);

		}
		else if (state == eDefaultKirbyState::Run)
		{
			if (GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
				GetComponent<Animator>()->PlayAnimation(L"DefaultKirby_Right_Run", true);
			else
				GetComponent<Animator>()->PlayAnimation(L"DefaultKirby_Left_Run", true);
		}
		else if (state == eDefaultKirbyState::Down)
		{
			if (GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
				GetComponent<Animator>()->PlayAnimation(L"DefaultKirby_Right_Down", true);
			else
				GetComponent<Animator>()->PlayAnimation(L"DefaultKirby_Left_Down", true);
		}
		else
		{
			if (GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
				GetComponent<Animator>()->PlayAnimation(L"DefaultKirby_Right_Drop");
			else
				GetComponent<Animator>()->PlayAnimation(L"DefaultKirby_Left_Drop");
		}
	}

	void Player::SetKirbyType(eAbilityType type)
	{
		// ������ ���ڷε���Ÿ������ �����ϴ� �Լ� �����Ͽ� ���
		mKirbyType[(UINT)mAbilityType]->Exit();
		mAbilityType = type;
		mKirbyType[(UINT)mAbilityType]->Enter();

		GetComponent<Rigidbody>()->SetLimitVelocity(Vector2(300.f, 300.f));
		GetComponent<Rigidbody>()->SetVelocity(Vector2(0.f, 0.f));
	}
}