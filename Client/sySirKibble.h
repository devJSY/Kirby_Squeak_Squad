#pragma once
#include "syEnemy.h"

namespace sy
{
	class SirKibble : public Enemy
	{
    public:
        SirKibble();
        virtual ~SirKibble();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);

    private:
	};
}

