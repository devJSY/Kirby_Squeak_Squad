#pragma once
#include "syEnemy.h"

namespace sy
{
	enum class eKingDededeState
	{
		Idle,
		Walk,
		JumpReady,
		Jump,
		Drop,
		AttackReady,
		AttackRun,
		Attack,
		FlyReady,
		FlyUp,
		Fly,
		FlyDrop,
		MonsterSummonReady,
		MonsterSummonJump,
		MonsterSummonDrop,
		MonsterSummon,
		Damage,
		DeathJump,
		Death,
		End,
	};

	class KingDedede : public Enemy
	{
	public:
		KingDedede(eAbilityType type);
		virtual ~KingDedede();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other) {};
		virtual void OnCollisionStay(class Collider* other) {};
		virtual void OnCollisionExit(class Collider* other) {};

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir);
		virtual bool IsDamagedState() { return mState == eKingDededeState::Damage; }

	private:
		void CheckPixelCollision();

	private:
		void Idle();
		void Walk();
		void JumpReady();
		void Jump();
		void Drop();
		void AttackReady();
		void AttackRun();
		void Attack();
		void FlyReady();
		void FlyUp();
		void Fly();
		void FlyDrop();
		void MonsterSummonReady();
		void MonsterSummonJump();
		void MonsterSummonDrop();
		void MonsterSummon();
		void Damage();
		void DeathJump();
		void Death();

	private:
		eKingDededeState	    mState;
		class Animator*			mAnimator;
		class Transform*		mTransform;
		class Rigidbody*		mRigidBody;
		eDirection				mDir;
	};
}
