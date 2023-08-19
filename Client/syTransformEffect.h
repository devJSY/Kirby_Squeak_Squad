#pragma once
#include "syEffects.h"

namespace sy
{
    class Player;
	class TransformEffect : public Effects
	{
        friend class Player;
    private:
        TransformEffect(Player* owner);
        virtual ~TransformEffect();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
        class Animator* mAnimator;
	};
}
