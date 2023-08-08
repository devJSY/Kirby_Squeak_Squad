#pragma once
#include "syEffects.h"

namespace sy
{
	class NinjaKirby_ChargeEffect : public Effects
	{
    public:
        NinjaKirby_ChargeEffect(class Player* owner);
        virtual ~NinjaKirby_ChargeEffect();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

	};
}
