#pragma once
#include "syEffects.h"

namespace sy
{
	class SirKibble_Skill : public Effects
	{
    public:
        SirKibble_Skill(GameObject* owner);
        virtual ~SirKibble_Skill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);
    
    private:
	};
}


