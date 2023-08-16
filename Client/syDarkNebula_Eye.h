#pragma once
#include "syGameObject.h"

namespace sy
{
	class DarkNebula;

	class DarkNebula_Eye : public GameObject
	{
		friend class DarkNebula;

	private:
		DarkNebula_Eye(DarkNebula* owner);
		virtual ~DarkNebula_Eye();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		DarkNebula*			mOwner;
		class Transform*	mTransform;
		class Animator*		mAnimator;

	};
}

