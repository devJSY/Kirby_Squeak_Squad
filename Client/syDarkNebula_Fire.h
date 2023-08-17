#pragma once
#include "syEffects.h"

namespace sy
{
    using namespace math;

    class DarkNebula;
    class DarkNebula_FireBall;

	class DarkNebula_Fire : public Effects
	{
        friend class DarkNebula;
        friend class DarkNebula_FireBall;

    private:
        DarkNebula_Fire(DarkNebula* owner, Vector2 pos);
        virtual ~DarkNebula_Fire();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);

    private:
        float mDuration;
	};
}
