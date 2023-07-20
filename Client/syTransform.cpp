#include "syTransform.h"
#include "syInput.h"
#include "syTime.h"

namespace sy
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mPosition(Vector2::Zero)
		, mRotation(0.f)
		, mScale(Vector2::One)
		, mDir(eDirection::RIGHT)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::Render(HDC hdc)
	{
	}
}