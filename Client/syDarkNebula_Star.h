#pragma once
#include "syEffects.h"

namespace sy
{
    using namespace math;
    class DarkNebula;

    class DarkNebula_Star : public Effects
    {
        friend class DarkNebula;

    private:
        DarkNebula_Star(DarkNebula* owner, Vector2 Dir);
        virtual ~DarkNebula_Star();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);

    private:
        class Transform*    mTransform;
        Vector2             mDir;
        float               mDuration;
    };
}
