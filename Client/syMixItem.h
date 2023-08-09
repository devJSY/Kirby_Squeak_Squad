#pragma once
#include "syGameObject.h"

namespace sy
{
	class MixItem : public GameObject
	{
		// Inventory에서만 접근가능
		friend class Inventory;

	private:
		MixItem();
		virtual ~MixItem();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Animator* mAnimator;
		float			mDuration;
	};
}

