#pragma once
#include "syEffects.h"

namespace sy
{
	using namespace math;

	class DarkNebula;
	class DarkNebula_SparkSkill : public Effects
	{
		friend class DarkNebula;

	private:
		DarkNebula_SparkSkill(DarkNebula* owner);
		virtual ~DarkNebula_SparkSkill();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
		class DarkNebula_SparkSkill_Collider*	mCollider[4];
		class Transform*						mTransform;
		float									mDuration;
	};
}
