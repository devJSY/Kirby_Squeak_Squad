#pragma once
#include "syEffects.h"

namespace sy
{
    class CrimpSkill : public Effects
    {
        // Crimp ������ ��������
        friend class Crimp;

    private:
        CrimpSkill(Crimp* owner);
        virtual ~CrimpSkill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);

    private:
        class Transform*    mTransform;
        float               mDuration;
    };
}

