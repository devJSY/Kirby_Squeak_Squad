#pragma once
#include "syGameObject.h"

namespace sy
{
	class AbilityStar : public GameObject
	{
    public:
        AbilityStar();
        virtual ~AbilityStar();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);

    private:

	};
}
