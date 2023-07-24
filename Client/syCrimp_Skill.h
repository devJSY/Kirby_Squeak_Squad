#pragma once
#include "syEffects.h"

namespace sy
{
    class CrimpSkill : public Effects
    {
    public:
        CrimpSkill();
        virtual ~CrimpSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);

    private:

    };
}

