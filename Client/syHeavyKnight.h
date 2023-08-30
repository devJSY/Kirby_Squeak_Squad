#pragma once
#include "syEnemy.h"

namespace sy
{
    enum class eHeavyKnightState
    {
        Idle,
        Walk,
        SlashReady,
        Slash,
        Damage,
        Dead,
        Inhaled,
        End,
    };

    // Sword
    class HeavyKnight : public Enemy
    {
    public:
        HeavyKnight();
        virtual ~HeavyKnight();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);

        virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;
        virtual void TakeInhaled(math::Vector2 InhaleDir) override;
        virtual bool IsDamagedState() const { return mState == eHeavyKnightState::Damage; }
        virtual bool IsDeadState() const { return mState == eHeavyKnightState::Dead; }

        eHeavyKnightState GetHeavyKnightState() const { return mState; }

    private:
        void CheckPixelCollision();

    private:
        void Idle();
        void Walk();
        void SlashReady();
        void Slash();
        void Damage();
        void Dead();
        void Inhaled();

    private:
        eHeavyKnightState	    mState;
        class Animator*         mAnimator;
        class Transform*        mTransform;
        class Rigidbody*        mRigidBody;
        eDirection			    mDir;

        float                   mDirDuration;
        float                   mAttackDelay;
        float				    mStateChangeDelay;
        UINT					mSlashCount;
    };
}

