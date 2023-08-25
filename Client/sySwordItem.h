#pragma once
#include "syGameObject.h"

namespace sy
{
	class SwordItem : public GameObject
	{
	public:
		SwordItem();
		virtual ~SwordItem();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);
	};
}

