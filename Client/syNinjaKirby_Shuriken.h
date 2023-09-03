#pragma once
#include "syEffects.h"

namespace sy
{
	enum class eShurikenState
	{
		Move,
        Stuck,
        Blink,
        Dead,
		End,
	};

    class NinjaKirby_Shuriken : public Effects
    {
    public:
        NinjaKirby_Shuriken(class Player* owner);
        virtual ~NinjaKirby_Shuriken();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;

    private:
        void CheckPixelCollision();

    private:
        void Move();
        void Stuck();
        void Blink();
        void Dead();

    private:
        eShurikenState          mState;
        eDirection              mDir;
        class Animator*         mAnimator;
        class Transform*        mTransform;
        class Collider*         mCollider;
        class GameObject*       mStuckTarget;
        math::Vector2           mStuckOffset;
        float                   mDuration;
    };
}
