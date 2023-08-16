#pragma once
#include "syEffects.h"

namespace sy
{
    enum class eDaroachTimeBombState
    {
        Idle,
        Fire,
        FireEnd,
        End,
    };

    class Daroach;

    class Daroach_TimeBomb : public Effects
    {
        // Daroach ������ ��������
        friend class Daroach;

    private:
        Daroach_TimeBomb(Daroach* owner);
        virtual ~Daroach_TimeBomb();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);

    private:
        void CheckPixelCollision();

    public:
        eDaroachTimeBombState GetDaroachTimeBombState() { return mState; }

    private:
        void Idle();
        void Fire();
        void FireEnd();

    private:
        eDaroachTimeBombState   mState;
        class Transform*        mTransform;
        class Animator*         mAnimator;
        class Collider*         mCollider;
        class Rigidbody*        mRigidBody;
        float                   mDuration;
    };
}

