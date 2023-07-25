#pragma once
#include "syGameObject.h"

namespace sy
{
	class Ground : public GameObject
	{
    public:
        Ground();
        virtual ~Ground();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
        virtual void OnCollisionExit(class Collider* other);
	};
}
