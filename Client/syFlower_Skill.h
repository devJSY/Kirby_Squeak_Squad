#pragma once
#include "syEffects.h"

namespace sy
{
    class FlowerSkill : public Effects
    {
    public:
        FlowerSkill();
        virtual ~FlowerSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:

    };
}

