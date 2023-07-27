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
	Vector2 Camera::mCameraLimit = {};

	void Camera::Initalize()
	{
		mResolution = Application::GetResolution();
		// 전체 해상도의 위쪽 화면기준으로 설정
		mResolution.y /= 2.f;

		mLookPosition = mResolution / 2.0f;
		
		// 기본제한 0.f, 0.f
		mCameraLimit.x = mResolution.x;
		mCameraLimit.y = mResolution.y;
	}

	void Camera::Update()
	{
		// 카메라 이동
		//if (Input::GetKeyPressed(eKeyCode::UP))
		//{
		//	mLookPosition.y -= 300.0f * Time::DeltaTime();
		//}
		//if (Input::GetKeyPressed(eKeyCode::LEFT))
		//{
		//	mLookPosition.x -= 300.0f * Time::DeltaTime();
		//}
		//if (Input::GetKeyPressed(eKeyCode::DOWN))
		//{
		//	mLookPosition.y += 300.0f * Time::DeltaTime();
		//}
		//if (Input::GetKeyPressed(eKeyCode::RIGHT))
		//{
		//	mLookPosition.x += 300.0f * Time::DeltaTime();
		//}

		if (mTarget)
		{
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();			
		}

		mDistance = mLookPosition - (mResolution / 2.0f);


		// 카메라 이동제한
		if (mDistance.x < 0)
		{
			mDistance.x = 0;
		}

		if (mDistance.y < 0)
		{
			mDistance.y = 0;
		}

		if (mDistance.x > mCameraLimit.x - mResolution.x)
		{
			mDistance.x = mCameraLimit.x - mResolution.x;
		}

		if (mDistance.y > mCameraLimit.y - mResolution.y)
		{
			mDistance.y = mCameraLimit.y - mResolution.y;
		}
	}
}
