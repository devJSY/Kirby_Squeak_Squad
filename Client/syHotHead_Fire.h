#pragma once
#include "syEffects.h"

namespace sy
{
	class HotHead_Fire : public Effects
	{
    public:
        HotHead_Fire();
        virtual ~HotHead_Fire();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
        
	};

}

