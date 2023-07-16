#pragma once
#include "syEnemy.h"

namespace sy
{
    class Flower : public Enemy
    {
    public:
        Flower();
        virtual ~Flower();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

    private:
    };


}

