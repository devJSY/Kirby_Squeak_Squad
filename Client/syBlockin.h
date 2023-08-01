#pragma once
#include "syEnemy.h"

namespace sy
{
	enum class eBlockinState
	{
		Idle,
		Appear,
		Walk,
		Damage,
		Dead,
		End,
	};

	class Blockin : public Enemy
	{
	public:
		Blockin();
		virtual ~Blockin();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
		virtual void OnCollisionStay(class Collider* other);
		virtual void OnCollisionExit(class Collider* other);

		virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;

	private:
		void CheckPixelCollision();

	private:
		void Idle();
		void Appear();
		void Walk();
		void Damage();
		void Dead();

	private:
		eBlockinState	    mState;
		class Animator*		mAnimator;
		class Transform*	mTransform;
		class Rigidbody*	mRigidBody;
		eDirection			mDir;

		float               mDirDuration;
	};
}
