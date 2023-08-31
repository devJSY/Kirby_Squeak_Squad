#pragma once
#include "syEffects.h"

namespace sy
{
    using namespace math;

    class BioSpark;
    class BioSpark_AttackArea : public Effects
    {
        friend class BioSpark;
    private:
        BioSpark_AttackArea(class BioSpark* owner);
        virtual ~BioSpark_AttackArea();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);

    private:
        BioSpark* mOwner;
    };
}
