#pragma once
#include "syEnemy.h"

namespace sy
{
	enum class eWaddleDeeState
	{
        Walk,
        Damage,
		End,
	};

    class WaddleDee : public Enemy
    {
    public:
        WaddleDee();
        virtual ~WaddleDee();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);

    private:
        void CheckPixelCollision();

    public:
        void Walk();
        void Damage();

    private:
        eWaddleDeeState	mState;
        class Animator* mAnimator;
        class Transform* mTransform;
        class Rigidbody* mRigidBody;
        eDirection			mDir;

        float       mDirDuration;

    };
}


