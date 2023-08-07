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
        AbilityStar(math::Vector2 Dir);
        virtual ~AbilityStar();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);

    private:
        void CheckPixelCollision();

    private:
        void Move();
        void Dead();

    private:
        eAbilityStarState	mState;
        class Animator*     mAnimator;
        class Transform*    mTransform;
        class Collider*     mCollider;
        float				mDuration;

	};
}
