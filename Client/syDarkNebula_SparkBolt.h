#pragma once
#include "syEffects.h"

namespace sy
{
	using namespace math;

	class DarkNebula;
	class DarkNebula_SparkBolt : public Effects
	{
		friend class DarkNebula;

	private:
		DarkNebula_SparkBolt(DarkNebula* owner, eCornerDirection dir);
		virtual ~DarkNebula_SparkBolt();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(class Collider* other);

	private:
		eCornerDirection	mDir;
		class Transform*	mTransform;
		float				mDuration;
	};
}
