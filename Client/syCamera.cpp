#include "syCamera.h"
#include "syApplication.h"
#include "syTransform.h"
#include "syInput.h"
#include "syTime.h"

namespace sy
{
	Vector2 Camera::mResolution = Vector2::Zero;
	Vector2 Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	void Camera::Initalize()
	{
		mResolution = Application::GetResolution();
	}

	void Camera::Update()
	{
		if (mTarget)
		{
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();			
		}

		mDistance = mLookPosition - (mResolution / 2.0f);
	}
}
