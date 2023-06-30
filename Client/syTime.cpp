#include "syTime.h"

namespace sy
{
	LARGE_INTEGER Time::mCpuFrequency = {};
	LARGE_INTEGER Time::mPrevFrequency = {};
	LARGE_INTEGER Time::mCurFrequency = {};
	float Time::mDeltaTime = 0.0f;

	void Time::Initailize()
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
			wchar_t szFloat[50] = {};
			float fps = 1.f / mDeltaTime;

			swprintf_s(szFloat, 50, L"fps : %f", fps);
			int strLen = (int)wcsnlen_s(szFloat, 50);

			TextOut(hdc, 10, 10, szFloat, strLen);

			timeCheck = 0.0f;

		}
	}
}
