#pragma once
#include "syEffects.h"

namespace sy
{
    class NinjaKirby_Fire : public Effects
    {
    public:
        NinjaKirby_Fire(class Player* owner, Vector2 pos);
        virtual ~NinjaKirby_Fire();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;
        virtual void OnCollisionStay(class Collider* other) override;

    private:
        class Animator*     mAnimator;
        class Collider*     mCollider;
        float               mTime;
    };
}
