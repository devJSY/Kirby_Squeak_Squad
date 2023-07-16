#pragma once
#include "syEnemy.h"

namespace sy
{
    class WaddleDee : public Enemy
    {
    public:
        WaddleDee();
        virtual ~WaddleDee();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
    };

}


