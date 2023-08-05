#pragma once
#include "syEffects.h"

namespace sy
{
	class Zoom_Effect :	public Effects
	{
    public:
        Zoom_Effect(GameObject* owner);
        virtual ~Zoom_Effect();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
        class Animator* mAnimator;
	};
}

