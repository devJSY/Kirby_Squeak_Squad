#pragma once
#include "syEnemy.h"

namespace sy
{
	enum class eWaddleDeeState
	{
        Walk,
        Damage,
        Dead,
        Inhaled,
		End,
	};

    class WaddleDee : public Enemy
    {
    public:
        WaddleDee();
        virtual ~WaddleDee();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);

        virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;
        virtual void TakeInhaled(math::Vector2 InhaleDir) override;
        virtual bool IsDamagedState() { return mState == eWaddleDeeState::Damage; }
        virtual bool IsDeadState() { return mState == eWaddleDeeState::Dead; }

    private:
        void CheckPixelCollision();

    private:
        void Walk();
        void Damage();
        void Dead();
        void Inhaled();

    private:
        eWaddleDeeState	    mState;
        class Animator*     mAnimator;
        class Transform*    mTransform;
        class Rigidbody*    mRigidBody;
        eDirection			mDir;

        float               mDirDuration;
    };
}


