#pragma once
#include "syEffects.h"

namespace sy
{
	class HotHead_Fire : public Effects
	{
        // HotHead 에서만 생성가능
        friend class HotHead;

    private:
        HotHead_Fire(HotHead* owner);
        virtual ~HotHead_Fire();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);

    private:
        HotHead*            mOwner;
        class Transform*    mTransform;
        eDirection          mDir;
    };

}

