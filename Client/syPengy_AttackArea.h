#pragma once
#include "syEffects.h"

namespace sy
{
    using namespace math;

    class Pengy;
    class Pengy_AttackArea : public Effects
    {
        friend class Pengy;
    private:
        Pengy_AttackArea(class Pengy* owner, Vector2 ColliderSize);
        virtual ~Pengy_AttackArea();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);

    private:
        Pengy* mOwner;
    };
}
