#pragma once
#include "syEffects.h"

namespace sy
{
	class DarkNebula;

	class DarkNebula_DeadStar : public Effects
	{
		friend class DarkNebula;

	private:
		DarkNebula_DeadStar(DarkNebula* owner, eDirection Dir);
		virtual ~DarkNebula_DeadStar();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class Transform*	mTransform;
		class Rigidbody*	mRigidbody;		
		float				mDuration;

	};
}

