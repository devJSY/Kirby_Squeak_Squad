#pragma once
#include "syEnemy.h"

namespace sy
{
    enum class eSirKibbleState
    {
        Idle,
        Attack,
        Jump,
        Damage,
        Dead,
        End,
    };

	class SirKibble : public Enemy
	{
    public:
        SirKibble();
        virtual ~SirKibble();

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
        void Attack();
        void Jump();
        void Damage();
        void Dead();
        void Inhaled();

    private:
        eSirKibbleState	    mState;
        class Animator*     mAnimator;
        class Transform*    mTransform;
        class Rigidbody*    mRigidBody;
        eDirection			mDir;

        EnemyHPbarUI*       mHPbarUI;
	};
}

