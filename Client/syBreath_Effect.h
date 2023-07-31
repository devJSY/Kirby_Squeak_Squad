#pragma once
#include "syEffects.h"

namespace sy
{
	class Breath_Effect : public Effects
	{
    public:
        Breath_Effect(GameObject* owner);
        virtual ~Breath_Effect();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;
        virtual void OnCollisionStay(class Collider* other) {};
        virtual void OnCollisionExit(class Collider* other) {};

    private:
        eDirection mDir;
        float      mColOffset;

	};

}