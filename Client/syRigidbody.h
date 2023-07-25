#pragma once
#include "syComponent.h"

namespace sy
{
	using namespace math;
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		virtual ~Rigidbody();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		void SetGround(bool ground) { mbGround = ground; }
		float GetmGravityRatio() { return mGravityRatio; }
		void SetmGravityRatio(float ratio) { mGravityRatio = ratio; }

	private:
		float mGravity;			// 중력
		float mGravityRatio;	// 0 ~ 1값
		bool mbGround;			// 땅에 닿은 상태인지 체크
	};
}
