#pragma once
#include "syBossEnemy.h"

namespace sy
{
	enum class eMetaKnightState
	{
		AppearReady,
		Appear,
		Idle,
		Walk,
		Dash,
		DashAttack,
		Slash1,
		Slash2,
		Jump,
		Turn,
		Drop,
		SpinAttack,
		SparkAttack,
		TornadoAttack,
		Dead,
		End,
	};

	class MetaKnight : public BossEnemy
	{
	public:
		MetaKnight(eAbilityType type);
		virtual ~MetaKnight();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir);
		virtual bool IsDamagedState() { return mbDamaged; }
		virtual bool IsDeadState() { return mState == eMetaKnightState::Dead; }

		eMetaKnightState GeteMetaKnightState() { return mState; }

	private:
		friend class SwordItem;

		void SetAppear() 
		{ 
			if (mState == eMetaKnightState::AppearReady)
			{
				mState = eMetaKnightState::Appear; 
				mAnimator->PlayAnimation(L"MetaKnight_Appear", false);
			}
		}

	private:
		void CheckPixelCollision();
		void AddStarEffect(eDirection dir);

	private:
		void AppearReady();
		void Appear();
		void Idle();
		void Walk();
		void Dash();
		void DashAttack();
		void Slash1();
		void Slash2();
		void Jump();
		void Turn();
		void Drop();
		void SpinAttack();
		void SparkAttack();
		void TornadoAttack();
		void Dead();

	private:
		eMetaKnightState	    mState;
		class Animator*			mAnimator;
		class Transform*		mTransform;
		class Rigidbody*		mRigidBody;
		class Collider*			mCollider;
		eDirection				mDir;

		float					mStateChangeDelay;
		bool					mbDamaged; // 연속 피격 방지
	};
}




