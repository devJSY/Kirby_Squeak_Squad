#pragma once
#include "syEffects.h"

namespace sy
{
    class Daroach;

    class Daroach_Energe : public Effects
    {
        // Daroach 에서만 생성가능
        friend class Daroach;

    private:
        Daroach_Energe(Daroach* owner);
        virtual ~Daroach_Energe();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other) {};
        virtual void OnCollisionExit(class Collider* other) {};

    private:
        eDirection          mDir;
        class Transform*    mTransform;
    };
}

