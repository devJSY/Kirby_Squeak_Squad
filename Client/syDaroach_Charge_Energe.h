#pragma once
#include "syEffects.h"

namespace sy
{
    class Daroach;

	class Daroach_Charge_Energe : public Effects
	{
        // Daroach 에서만 생성가능
        friend class Daroach;

    private:
        Daroach_Charge_Energe(Daroach* owner);
        virtual ~Daroach_Charge_Energe();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
        eDirection          mDir;
        class Transform*    mTransform;
	};
}

