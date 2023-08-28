#pragma once
#include "syEffects.h"

namespace sy
{
    class MetaKnight;
    class MetaKnight_SlashSkill : public Effects
    {
        friend class MetaKnight;
    private:
        MetaKnight_SlashSkill(MetaKnight* owner);
        virtual ~MetaKnight_SlashSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
    };
}

