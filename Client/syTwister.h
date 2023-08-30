#pragma once
#include "syEnemy.h"

namespace sy
{
    enum class eTwisterState
    {
        Idle,
        Skill,
        Damage,
        Dead,
        Inhaled,
        End,
    };

    class Twister : public Enemy
    {
    public:
        Twister();
        virtual ~Twister();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);

        virtual void TakeHit(int DamageAmount, math::Vector2 HitDir) override;
        virtual void TakeInhaled(math::Vector2 InhaleDir) override;
        virtual bool IsDamagedState() const { return mState == eTwisterState::Damage; }
        virtual bool IsDeadState() const { return mState == eTwisterState::Dead; }

        eTwisterState GetTwisterState() const { return mState; }

    private:
        void CheckPixelCollision();

    private:
        void Idle();
        void Skill();
        void Damage();
        void Dead();
        void Inhaled();

    private:
        eTwisterState	     mState;
        class Animator*      mAnimator;
        class Transform*     mTransform;
        class Rigidbody*     mRigidBody;
        eDirection			 mDir;

        Vector2             mSkillDir;
        float               mAttackDelay;
        float				mStateChangeDelay;
    };
}

