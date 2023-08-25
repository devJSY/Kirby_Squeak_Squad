#pragma once
#include "syGameObject.h"

namespace sy
{
	class MetaKnight;
	class SwordItem : public GameObject
	{
	public:
		SwordItem(MetaKnight* owner);
		virtual ~SwordItem();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);

	private:
		MetaKnight* mOwner;
	};
}

