#pragma once
#include "syEffects.h"

namespace sy
{
    class DarkNebula;

	class DarkNebula_IceSkill : public Effects
	{
        friend class DarkNebula;

    private:
        DarkNebula_IceSkill(DarkNebula* owner);
        virtual ~DarkNebula_IceSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);

    private:
        class Transform* mTransform;

	};
}
