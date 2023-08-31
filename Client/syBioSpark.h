#pragma once
#include "syEnemy.h"

namespace sy
{
    enum class eBioSparkState
    {
        Idle,
        ThrowShuriken,
        Hide,
        Appear,
        Hiding,
        Attack,
        Damage,
        Dead,
        Inhaled,
        End,
    };

    // Cutter
    class BioSpark : public Enemy
    {
    public:
        BioSpark();
        virtual ~BioSpark();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);

        virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;
        virtual void TakeInhaled(math::Vector2 InhaleDir) override;
        virtual bool IsDamagedState() const { return mState == eBioSparkState::Damage; }
        virtual bool IsDeadState() const { return mState == eBioSparkState::Dead; }
      
        eBioSparkState GetBioSparkState() const { return mState; }

    private:
        void CheckPixelCollision();

    private:
        void Idle();
        void ThrowShuriken();
        void Hide();
        void Appear();
        void Hiding();
        void Attack();
        void Damage();
        void Dead();
        void Inhaled();

    private:
        eBioSparkState	    mState;
        class Animator*     mAnimator;
        class Transform*    mTransform;
        class Rigidbody*    mRigidBody;
        class Collider*     mCollider;
        eDirection			mDir;

        float				mStateChangeDelay;
    };
}

