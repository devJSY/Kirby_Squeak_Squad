#pragma once
#include "syEnemy.h"

namespace sy
{
    class Yellow : public Enemy
    {
    public:
        Yellow();
        virtual ~Yellow();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
    };


}

