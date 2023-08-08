#pragma once
#include "syEffects.h"

namespace sy
{
    class NinjaKirby_Shuriken : public Effects
    {
    public:
        NinjaKirby_Shuriken(class Player* owner);
        virtual ~NinjaKirby_Shuriken();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;
        virtual void OnCollisionStay(class Collider* other) override;

    private:
        eDirection mDir;

    };
}
