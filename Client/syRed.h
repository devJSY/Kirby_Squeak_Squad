#pragma once
#include "syEnemy.h"

namespace sy
{
    class Red : public Enemy
    {
    public:
        Red();
        virtual ~Red();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
    };

}


