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
		void SetGround(bool ground) { mbGround = ground; }
		bool IsGround() { return mbGround; }
		Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }
		void SetLimitVelocity(Vector2 velocity) { mLimitedVelocty = velocity; }

		void SetFloat(bool _float) { mbfloat = _float; }
		bool Float() { return mbfloat; }

	private:
		float mMass;				// 질량

		float mFriction;			// 마찰력 

		Vector2 mForce;				// 힘
		Vector2 mAccelation;		// 가속도
		Vector2 mVelocity;			// 속도 = 속력 * 방향
		Vector2 mGravity;			// 중력
		Vector2 mLimitedVelocty;	// 최대 속도 제한

		bool mbGround;				// 땅에 닿은 상태인지 체크
		bool mbfloat;				// 공중에 떠다니는 상태인지 체크
	};
}
