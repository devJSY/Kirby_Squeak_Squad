#pragma once
#include "syEffects.h"

namespace sy
{
    class MetaKnight;
    class MetaKnight_TornadoSkill : public Effects
    {
        friend class MetaKnight;
    private:
        MetaKnight_TornadoSkill(MetaKnight* owner);
        virtual ~MetaKnight_TornadoSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
    };
}

