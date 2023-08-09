#pragma once
#include "syGameObject.h"

namespace sy
{
	class MixItem : public GameObject
	{
	
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

