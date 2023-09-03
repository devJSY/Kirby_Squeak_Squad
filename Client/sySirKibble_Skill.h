#pragma once
#include "syEffects.h"

namespace sy
{
	class SirKibble_Skill : public Effects
	{
        // SirKibble 에서만 생성가능
        friend class SirKibble;

    private:
        SirKibble_Skill(SirKibble* owner);
        virtual ~SirKibble_Skill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
    
    private:
        eDirection          mDir;
        class Transform*    mTransform;
        class Rigidbody*    mRigidbody;
        float               mDuration;    
	};
}


