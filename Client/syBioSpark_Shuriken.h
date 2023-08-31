#pragma once
#include "syEffects.h"

namespace sy
{
    using namespace math;

    class BioSpark;
    class BioSpark_Shuriken : public Effects
    {
         friend class BioSpark;
    private:
        BioSpark_Shuriken(class BioSpark* owner);
        virtual ~BioSpark_Shuriken();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;

    private:
        eDirection              mDir;
        class Animator*         mAnimator;
        class Transform*        mTransform;

        float                   mDuration;
    };
}
