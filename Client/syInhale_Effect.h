#pragma once
#include "syEffects.h"

namespace sy
{
    using namespace math;

	class Inhale_Effect : public Effects
	{
    public:
        Inhale_Effect(GameObject* owner);
        virtual ~Inhale_Effect();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;
        virtual void OnCollisionStay(class Collider* other) override;
        virtual void OnCollisionExit(class Collider* other) override;

    private:
        eDirection  mDir;
	};
}

