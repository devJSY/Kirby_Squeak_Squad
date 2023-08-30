#pragma once
#include "syEffects.h"

namespace sy
{
    using namespace math;

    class Sparky;
    class Sparky_AttackArea : public Effects
    {
        friend class Sparky;
    private:
        Sparky_AttackArea(class Sparky* owner);
        virtual ~Sparky_AttackArea();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);

    private:
        Sparky* mOwner;
    };
}
