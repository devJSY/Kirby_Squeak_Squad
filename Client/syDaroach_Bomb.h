#pragma once
#include "syEffects.h"

namespace sy
{
    enum class eDaroachBombState
    {
        Idle,
        Fire,
        End,
    };

    class Daroach;

    class Daroach_Bomb : public Effects
    {
        // Daroach 에서만 생성가능
        friend class Daroach;

    private:
        Daroach_Bomb(Daroach* owner);
        virtual ~Daroach_Bomb();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);      

    private:
        void CheckPixelCollision();

    public:
        eDaroachBombState GetDaroachBombState() const { return mState; }
        void TakeInhaled() { mInhaled = true; }
 
    private:
        void Idle();
        void Fire();

    private:
        eDaroachBombState   mState;
        class Transform*    mTransform;
        class Animator*     mAnimator;
        class Collider*     mCollider;
        class Rigidbody*    mRigidBody;
        float               mDuration;
        bool		    	mInhaled;
    };
}

