#pragma once
#include "syGameObject.h"

namespace sy
{
	class DarkNebula_SparkSkill_Collider : public GameObject
	{
	public:
        DarkNebula_SparkSkill_Collider(Vector2 pos, Vector2 Size);
        virtual ~DarkNebula_SparkSkill_Collider();

        virtual void Initialize();
        virtual void Update();
        virtual void Render(HDC hdc);

        virtual void OnCollisionEnter(class Collider* other);
        virtual void OnCollisionStay(class Collider* other);
	};
}

