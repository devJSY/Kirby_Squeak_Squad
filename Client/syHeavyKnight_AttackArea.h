#pragma once
#include "syEffects.h"

namespace sy
{
    using namespace math;

    class HeavyKnight;
    class HeavyKnight_AttackArea : public Effects
    {
        friend class HeavyKnight;
    private:
        HeavyKnight_AttackArea(class HeavyKnight* owner);
        virtual ~HeavyKnight_AttackArea();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);

    private:
        HeavyKnight* mOwner;
    };
}
