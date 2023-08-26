#pragma once
#include "syEffects.h"

namespace sy
{
    using namespace math;

    class SwordKirby_AttackArea : public Effects
    {
    public:
        SwordKirby_AttackArea(class Player* owner, Vector2 ColliderSize);
        virtual ~SwordKirby_AttackArea();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
    };
}
