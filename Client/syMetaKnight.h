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
		Slash,
		SlashSkill,
		Jump,
		Turn,
		Drop,
		SpinAttack,
		SpinAttackEnd,
		JumpDownAttack,
		TornadoSkillCharge,
		TornadoSkill,
		Dead1,
		Dead2,
		Dead3,
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
		virtual bool IsDamagedState() const { return mbDamaged; }
		virtual bool IsDeadState() const { return mState == eMetaKnightState::Dead3; }

		eMetaKnightState GeteMetaKnightState() const { return mState; }

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

		void SetBossState();

	private:
		void Appear();
		void Idle();
		void Walk();
		void Dash();
		void DashAttack();
		void Slash();
		void SlashSkill();
		void Jump();
		void Turn();
		void Drop();
		void SpinAttack();
		void SpinAttackEnd();
		void JumpDownAttack();
		void TornadoSkillCharge();
		void TornadoSkill();
		void Dead1();
		void Dead2();
		void Dead3();

	private:
		eMetaKnightState	    mState;
		class Animator*			mAnimator;
		class Transform*		mTransform;
		class Rigidbody*		mRigidBody;
		class Collider*			mCollider;
		eDirection				mDir;


		float					mStateChangeDelay;
		bool					mbDamaged; // 연속 피격 방지
		eDirection				mWalkDir;
		UINT					mSlashCount;
	};
}




