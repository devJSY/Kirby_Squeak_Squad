#pragma once
#include "syEffects.h"

namespace sy
{
    class Daroach;

	class Daroach_Charge_Energe : public Effects
	{
        // Daroach ������ ��������
        friend class Daroach;

    private:
        Daroach_Charge_Energe(Daroach* owner);
        virtual ~Daroach_Charge_Energe();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);
	};
}

