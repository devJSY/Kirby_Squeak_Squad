#include "syTime.h"
#include "syApplication.h"
#include "Resource.h"

namespace sy
{
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.0f;

	void Time::Initialize()
	{
		// CPU 고유 진동수를 가져온다.
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 시작 됐을때 진동수를 가져온다.
		QueryPerformanceCounter(&mPrevFrequency);
	}
	void Time::Update()
	{
		QueryPerformanceCounter(&mCurFrequency);

		float differenceFrequency 
			= static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

		mDeltaTime = differenceFrequency / static_cast<float>(mCpuFrequency.QuadPart);
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		static float timeCheck = 0.0f;

		timeCheck += mDeltaTime;

		if (timeCheck >= 1.f)
		{
			float fps = 1.f / mDeltaTime;

			// 윈도우 이름 값 받아오기
			wchar_t strBuffer[255] = {};
			LoadString(nullptr, IDC_CLIENT, strBuffer, 255);

			wchar_t szBuffer[255] = {};
			swprintf_s(szBuffer, L"%s FPS : %f", strBuffer, fps);
			SetWindowText(Application::GetHwnd(), szBuffer);

			timeCheck = 0.0f;
		}
	}
}
