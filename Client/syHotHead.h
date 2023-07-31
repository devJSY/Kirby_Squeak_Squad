#pragma once
#include "syEnemy.h"

namespace sy
{
    enum class eHotHeadState
    {
        Walk,
        Attack,
        Damage,
        End,
    };


    class HotHead : public Enemy
    {
    public:
        HotHead();
        virtual ~HotHead();

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
        void Walk();
        void Attack();
        void Damage();

    private:
        eHotHeadState	    mState;
        class Animator*     mAnimator;
        class Transform*    mTransform;
        class Rigidbody*    mRigidBody;
        eDirection			mDir;

        float               mDirDuration;
    };
}

