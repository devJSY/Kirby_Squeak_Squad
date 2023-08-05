#include "syCamera.h"
#include "syApplication.h"
#include "syTransform.h"
#include "syInput.h"
#include "syTime.h"
#include "syTexture.h"

namespace sy
{
	Vector2					Camera::mResolution = Vector2::Zero;
	Vector2					Camera::mLookPosition = Vector2::Zero;
	Vector2					Camera::mDistance = Vector2::Zero;
	GameObject*				Camera::mTarget = nullptr;
	Vector2					Camera::mCameraLimit = {};
	std::list<tCamEffect>	Camera::m_listCamEffect = {};
	Texture*				Camera::mWhiteTex = nullptr;				
	Texture*				Camera::mBlackTex = nullptr;

	bool					Camera::mbColliderRenderTrig = false;

	void Camera::Initalize()
	{
		mResolution = Application::GetResolution();
		// 전체 해상도의 위쪽 화면기준으로 설정
		mResolution.y /= 2.f;

		mLookPosition = mResolution / 2.0f;
		
		// 기본제한 0.f, 0.f
		mCameraLimit.x = mResolution.x;
		mCameraLimit.y = mResolution.y;

		// 상단화면 크기의 카메라 효과용 텍스쳐 생성
		mWhiteTex = Texture::Create(L"WhiteTex", (UINT)mResolution.x, (UINT)mResolution.y, RGB(255, 255, 255));
		mBlackTex = Texture::Create(L"BlackTex", (UINT)mResolution.x, (UINT)mResolution.y, RGB(0, 0, 0));
	}

	void Camera::Update()
	{
		if (Input::GetKeyDown(eKeyCode::C))
		{
			mbColliderRenderTrig = !mbColliderRenderTrig;
		}


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

	void Camera::Render(HDC hdc)
	{
		// 이벤트가 없다면 리턴
		if (m_listCamEffect.empty())
			return;

		tCamEffect& effect = m_listCamEffect.front();

		effect.fCurTime += Time::DeltaTime();
	
		float fRatio = effect.fCurTime / effect.fDuration;

		if (fRatio < 0.f)
			fRatio = 0.f;
		if (fRatio > 1.f)
			fRatio = 1.f;

		int iAlpha = 0;

		// 이벤트에 따라 알파값 설정
		if (effect.eEffect == CAM_EFFECT::FADE_OUT)
		{
			iAlpha = (int)(255.f * fRatio);
		}
		else if (effect.eEffect == CAM_EFFECT::FADE_IN)
		{
			iAlpha = (int)(255.f * (1.f - fRatio));
		}
		else if (effect.eEffect == CAM_EFFECT::Pause)
		{
			iAlpha = (int)255.f;
		}

		// AlphaBlend 셋팅값 설정
		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER; // 원본과 대상 이미지를 합친다는 의미
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = iAlpha; // 고정 알파값 설정

		if (effect.TexColor == RGB(255, 255, 255))
		{
			AlphaBlend(hdc,
				0, 0
				, (int)mWhiteTex->GetWidth()
				, (int)mWhiteTex->GetHeight()
				, mWhiteTex->GetHdc()
				, 0, 0
				, (int)mWhiteTex->GetWidth()
				, (int)mWhiteTex->GetHeight()
				, bf);
		}
		else if(effect.TexColor == RGB(0, 0, 0))
		{
			AlphaBlend(hdc,
				0, 0
				, (int)mBlackTex->GetWidth()
				, (int)mBlackTex->GetHeight()
				, mBlackTex->GetHdc()
				, 0, 0
				, (int)mBlackTex->GetWidth()
				, (int)mBlackTex->GetHeight()
				, bf);
		}


		if (effect.fCurTime > effect.fDuration)
		{
			effect.eEffect = CAM_EFFECT::NONE;
			m_listCamEffect.pop_front();
		}
	}
}
