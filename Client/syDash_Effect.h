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

    private:
        class Animator* mAnimator;
	};
}
