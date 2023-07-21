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
		float mMass; // ����

		float mFriction;			// ������ 
		float mStaticFriction;		// ���� ������
		float mKineticFrction;		// � ������
		float mCoefficentFrction;	// �������

		Vector2 mForce;			// ��
		Vector2 mAccelation;	// ���ӵ�
		Vector2 mVelocity;		// �ӵ� = �ӷ� * ����
		Vector2 mGravity;		// �߷�
	};
}
