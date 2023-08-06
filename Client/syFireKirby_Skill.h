#pragma once
#include "syEffects.h"

namespace sy
{
    class FireKirby_Skill : public Effects
    {
    public:
        FireKirby_Skill(class Player* owner);
        virtual ~FireKirby_Skill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;
        virtual void OnCollisionStay(class Collider* other) override;
        virtual void OnCollisionExit(class Collider* other) override;

    private:
        eDirection mDir;

    };
}
