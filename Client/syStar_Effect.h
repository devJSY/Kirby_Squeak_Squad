#pragma once
#include "syEffects.h"

namespace sy
{
    enum class eStarState
    {
        Active,
        Dead,
    };

    using namespace math;

	class Star_Effect :	public Effects
	{
    public:
        Star_Effect(GameObject* owner, Vector2 pos);
        virtual ~Star_Effect();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);

        eStarState GetStarState() { return mState; }

    private:
        void Active();
        void Dead();

    private:
        eStarState      mState;
        class Animator* mAnimator;
        float           mDuration;
	};
}
