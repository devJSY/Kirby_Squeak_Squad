#include "syRigidbody.h"
#include "syTime.h"
#include "syGameObject.h"
#include "syTransform.h"

namespace sy
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mGravity(64.f * 2.4f)
		, mGravityRatio(1.f)
		, mbGround(false)
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
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		// 현재위치 = 위치 * 속도
			// 공중에 있을 때
		if (!mbGround)
			pos.y += (mGravity * mGravityRatio) * Time::DeltaTime();

		tr->SetPosition(pos);
	}

	void Rigidbody::Render(HDC hdc)
	{
	}
}