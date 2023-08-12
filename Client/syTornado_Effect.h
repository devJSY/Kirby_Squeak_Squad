#pragma once
#include "syEffects.h"

namespace sy
{
	class Tornado_Effect : public Effects
	{
    public:
        Tornado_Effect(GameObject* owner);
        virtual ~Tornado_Effect();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
        class Animator* mAnimator;
	};
}
