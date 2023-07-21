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

		void AddForce(Vector2 force) { mForce += force; }
		void SetMass(float mass) { mMass = mass; }

	private:
		float mMass; // 질량

		float mFriction;			// 마찰력 
		float mStaticFriction;		// 정지 마찰력
		float mKineticFrction;		// 운동 마찰력
		float mCoefficentFrction;	// 마찰계수

		Vector2 mForce;			// 힘
		Vector2 mAccelation;	// 가속도
		Vector2 mVelocity;		// 속도 = 속력 * 방향
		Vector2 mGravity;		// 중력
	};
}
