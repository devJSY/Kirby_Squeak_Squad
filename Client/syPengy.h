#pragma once
#include "syEnemy.h"

namespace sy
{
    enum class ePengyState
    {
        Idle,
        Walk,
        AttackReady,
        Attack,
        Damage,
        Dead,
        Inhaled,
        End,
    };

    class Pengy : public Enemy
    {
    public:
        Pengy();
        virtual ~Pengy();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);

        virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;
        virtual void TakeInhaled(math::Vector2 InhaleDir) override;
        virtual bool IsDamagedState() const { return mState == ePengyState::Damage; }
        virtual bool IsDeadState() const { return mState == ePengyState::Dead; }

        ePengyState GetPengyState() const { return mState; }

    private:
        void CheckPixelCollision();

    private:
        void Idle();
        void Walk();
        void AttackReady();
        void Attack();
        void Damage();
        void Dead();
        void Inhaled();

    private:
        ePengyState     	mState;
        class Animator*     mAnimator;
        class Transform*    mTransform;
        class Rigidbody*    mRigidBody;
        eDirection			mDir;

        float               mAttackDelay;
        float               mDirDuration;
        float				mStateChangeDelay;
    };
}

