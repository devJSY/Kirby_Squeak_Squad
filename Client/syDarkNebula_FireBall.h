#pragma once
#include "syEffects.h"

namespace sy
{
    enum class eDarkNebulaFireBallState
    {
        FireBall,
        Exploded,
        End,
    };

    class DarkNebula;
	class DarkNebula_FireBall : public Effects
	{
        friend class DarkNebula;

    private:
        DarkNebula_FireBall(DarkNebula* owner);
        virtual ~DarkNebula_FireBall();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);

    private:
        void CheckPixelCollision();

    private:
        void FireBall();
        void Exploded();

    private:
        eDarkNebulaFireBallState    mState;
        class Transform*            mTransform;
        class Animator*             mAnimator;
        class Collider*             mCollider;
        float                       mDuration;
        Vector2                     mGroundPos;
        bool                        mbActive[5];
	};
}
