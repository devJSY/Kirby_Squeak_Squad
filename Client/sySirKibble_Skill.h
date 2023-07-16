#pragma once
#include "syEffects.h"

namespace sy
{
	class SirKibble_Skill : public Effects
	{
    public:
        SirKibble_Skill();
        virtual ~SirKibble_Skill();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);
    
    private:
	};
}


