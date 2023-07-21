#include "syRigidbody.h"
#include "syTime.h"
#include "syGameObject.h"
#include "syTransform.h"

namespace sy
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(10.0f)
	{
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{
		//f(��) = m(����)a ���ӵ�
		mAccelation = mForce / mMass;

		// �ӵ��� ���ӵ��� ������� �� �ӵ��� ���´�
		mVelocity += mAccelation * Time::DeltaTime();

		// �ӵ��� �����ϴ°�쿡�� ���
		if (!(mVelocity == Vector2::Zero))
		{
			// �ӵ��� �ݴ� �������� ������ ����
			Vector2 friction = -mVelocity;

			// ������ = �ӵ��� �ݴ� ���� * ������� * ���� 
			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

			// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� ū ���
			if (mVelocity.Length() < friction.Length())
			{
				// �ӵ����� �������� �� ū��� ����
				mVelocity = Vector2::Zero;
			}
			else
			{
				// �ӵ��� ������ �߰�
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		// ������ġ = ��ġ * �ӵ�
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPosition(pos);

		// �̹������� �� �ʱ�ȭ
		mForce.clear();
	}

	void Rigidbody::Render(HDC hdc)
	{
	}
}