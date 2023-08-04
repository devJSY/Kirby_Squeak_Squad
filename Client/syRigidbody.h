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
		float mMass;				// ����

		float mFriction;			// ������ 

		Vector2 mForce;				// ��
		Vector2 mAccelation;		// ���ӵ�
		Vector2 mVelocity;			// �ӵ� = �ӷ� * ����
		Vector2 mGravity;			// �߷�
		Vector2 mLimitedVelocty;	// �ִ� �ӵ� ����

		bool mbGround;				// ���� ���� �������� üũ
		bool mbfloat;				// ���߿� ���ٴϴ� �������� üũ
	};
}
