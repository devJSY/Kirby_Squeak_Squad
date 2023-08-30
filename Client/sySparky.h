#pragma once
#include "syEnemy.h"

namespace sy
{
    enum class eSparkyState
    {
        Idle,
        Jump,
        Drop,
        AttackReady,
        Attack,
        Damage,
        Dead,
        Inhaled,
        End,
    };

    // Spark
    class Sparky : public Enemy
    {
    public:
        Sparky();
        virtual ~Sparky();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);

        virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;
        virtual void TakeInhaled(math::Vector2 InhaleDir) override;
        virtual bool IsDamagedState() const { return mState == eSparkyState::Damage; }
        virtual bool IsDeadState() const { return mState == eSparkyState::Dead; }

        eSparkyState GetSparkyState() const { return mState; }

    private:
        void CheckPixelCollision();

    private:
        void Idle();
        void Jump();
        void Drop();
        void AttackReady();
        void Attack();
        void Damage();
        void Dead();
        void Inhaled();

    private:
        eSparkyState	     mState;
        class Animator*      mAnimator;
        class Transform*     mTransform;
        class Rigidbody*     mRigidBody;
        eDirection			 mDir;

        float               mAttackDelay;
        float				mStateChangeDelay;
    };
}

