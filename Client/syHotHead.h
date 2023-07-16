#pragma once
#include "syEnemy.h"

namespace sy
{
    class HotHead : public Enemy
    {
    public:
        HotHead();
        virtual ~HotHead();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
    };
}

