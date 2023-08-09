#pragma once
#include "syEffects.h"

namespace sy
{
	class Breath_Effect : public Effects
	{
    public:
        Breath_Effect(class Player* owner);
        virtual ~Breath_Effect();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other) override;

    private:
        eDirection mDir;
        float      mColOffset;

	};

}