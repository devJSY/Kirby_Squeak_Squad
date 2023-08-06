#pragma once
#include "syEffects.h"

namespace sy
{
	class Dash_Effect :	public Effects
	{
    public:
        Dash_Effect(class Player* owner);
        virtual ~Dash_Effect();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) {};
        virtual void OnCollisionStay(class Collider* other) {};
        virtual void OnCollisionExit(class Collider* other) {};

    private:
        class Animator* mAnimator;
	};
}
