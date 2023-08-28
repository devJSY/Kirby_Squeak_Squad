#pragma once
#include "syEnemy.h"

namespace sy
{
    enum class eHotHeadState
    {
        Walk,
        Attack,
        Damage,
        Dead,
        Inhaled,
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
        virtual void TakeInhaled(math::Vector2 InhaleDir) override;
        virtual bool IsDamagedState() const { return mState == eHotHeadState::Damage; }
        virtual bool IsDeadState() const { return mState == eHotHeadState::Dead; }

        eHotHeadState GetHotHeadState() const { return mState; }

    private:
        void CheckPixelCollision();

    private:
        void Walk();
        void Attack();
        void Damage();
        void Dead();
        void Inhaled();

    private:
        eHotHeadState	    mState;
        class Animator*     mAnimator;
        class Transform*    mTransform;
        class Rigidbody*    mRigidBody;
        eDirection			mDir;

        float               mDirDuration;
        float               mAttackDelay;
    };
}

