#include "syTransform.h"
#include "syInput.h"
#include "syTime.h"

namespace sy
{
	Transform::Transform()
		: Component(eComponentType::Transform)
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
		if (Input::GetKeyPressed(eKeyCode::W))
		{
			mPosition.y -= 500.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::A))
		{
			mPosition.x -= 500.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::S))
		{
			mPosition.y += 500.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::D))
		{
			mPosition.x += 500.0f * Time::DeltaTime();
		}
	}
	void Transform::Render(HDC hdc)
	{
	}
}