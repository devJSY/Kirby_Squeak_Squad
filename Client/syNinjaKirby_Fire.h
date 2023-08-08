#pragma once
#include "syEffects.h"

namespace sy
{
    class NinjaKirby_Fire : public Effects
    {
    public:
        NinjaKirby_Fire(class Player* owner);
        virtual ~NinjaKirby_Fire();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;
        virtual void OnCollisionStay(class Collider* other) override;

    private:
        class Collider*     mCollider;
        float               mTime;
    };
}
