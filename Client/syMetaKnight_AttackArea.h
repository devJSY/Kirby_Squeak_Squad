#pragma once
#include "syEffects.h"

namespace sy
{
    using namespace math;

    class MetaKnight;
    class MetaKnight_AttackArea : public Effects
    {
        friend class MetaKnight;
    private:
        MetaKnight_AttackArea(class MetaKnight* owner, Vector2 ColliderSize);
        virtual ~MetaKnight_AttackArea();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);

    private:
        MetaKnight* mOwner;
    };
}
