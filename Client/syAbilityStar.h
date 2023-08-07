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

    using namespace enums;

	class AbilityStar : public GameObject
	{
    public:
        AbilityStar(class Player* owner, eAbilityType type);
        virtual ~AbilityStar();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        eAbilityType GetAbilityType() { return mType; }

    private:
        void CheckPixelCollision();

    private:
        void Move();
        void Dead();

    private:
        class Player*       mOwner;
        eAbilityStarState	mState;
        eAbilityType        mType;
        class Animator*     mAnimator;
        class Transform*    mTransform;
        class Collider*     mCollider;
        class Rigidbody*    mRigidBody;
        float				mDuration;

	};
}
