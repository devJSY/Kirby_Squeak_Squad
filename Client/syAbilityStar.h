#pragma once
#include "syGameObject.h"

namespace sy
{
    enum class eAbilityStarState
    {
        Move,
        Dead,
        End,
    };

	class AbilityStar : public GameObject
	{
    public:
        AbilityStar(class Player* owner, math::Vector2 Dir);
        virtual ~AbilityStar();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
        void CheckPixelCollision();

    private:
        void Move();
        void Dead();

    private:
        class Player*       mOwner;
        eAbilityStarState	mState;
        class Animator*     mAnimator;
        class Transform*    mTransform;
        class Collider*     mCollider;
        float				mDuration;

	};
}
