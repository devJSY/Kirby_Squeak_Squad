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
		, mForce(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, mGravity(Vector2(0.0f, 300.0f))
		, mLimitedVelocty(Vector2(300.f, 300.f))
		, mbGround(false)
		, mbfloat(false)
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

		if (mbGround)
		{
			// 땅위에 있을때
			Vector2 gravity = mGravity;
			gravity.Normalize();
			float dot = math::Dot(mVelocity, gravity);	// 플레이어 방향 과 중력사이의 CosΘ 값
			mVelocity -= gravity * dot;	// 중력의 방향을 플레이어의 진행방향으로 변경한다
		}
		else if (mbfloat)
		{
			// 중력영향 X
		}
		else
		{
			// 공중에 있을 때
			mVelocity += mGravity * Time::DeltaTime();
		}

		// 최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity = gravity * dot;	// 중력의 방향을 플레이어의 진행방향으로 변경한다

		Vector2 sideVelocity = mVelocity - gravity; // 중력이 적용된후 수평방향으로의 속도
		if (mLimitedVelocty.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitedVelocty.y;
		}

		if (mLimitedVelocty.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocty.x;
		}
		// 제한된 중력과 수평속도를 합하여 속도 결정
		mVelocity = gravity + sideVelocity;

		//마찰력 조건 ( 적용된 힘이 없고, 속도가 0 이 아닐때 )
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