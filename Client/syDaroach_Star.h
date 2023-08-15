#pragma once
#include "syEffects.h"

namespace sy
{
    class Daroach;
    class Daroach_Star : public Effects
    {
        // Daroach 에서만 생성가능
        friend class Daroach;

    private:
        Daroach_Star(Daroach* owner, Vector2 Dir);
        virtual ~Daroach_Star();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);

    private:
        void CheckPixelCollision();

    private:
        class Transform*    mTransform;
        class Animator*     mAnimator;
        class Collider*     mCollider;
        class Rigidbody*    mRigidBody;
        float               mDuration;
    };
}

