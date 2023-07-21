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
		//f(힘) = m(질량)a 가속도
		mAccelation = mForce / mMass;

		// 속도에 가속도를 더해줘야 총 속도가 나온다
		mVelocity += mAccelation * Time::DeltaTime();

		// 속도가 존재하는경우에만 계산
		if (!(mVelocity == Vector2::Zero))
		{
			// 속도에 반대 방향으로 마찰력 적용
			Vector2 friction = -mVelocity;

			// 마찰력 = 속도의 반대 방향 * 마찰계수 * 질량 
			friction = friction.Normalize() * mFriction * mMass * Time::DeltaTime();

			// 마찰력으로 의한 속도 감소량이 현재 속도보다 큰 경우
			if (mVelocity.Length() < friction.Length())
			{
				// 속도보다 마찰력이 더 큰경우 정지
				mVelocity = Vector2::Zero;
			}
			else
			{
				// 속도에 마찰력 추가
				mVelocity += friction;
			}
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		// 현재위치 = 위치 * 속도
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPosition(pos);

		// 이번프레임 힘 초기화
		mForce.clear();
	}

	void Rigidbody::Render(HDC hdc)
	{
	}
}