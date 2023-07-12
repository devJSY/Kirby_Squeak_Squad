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
		// CPU ���� �������� �����´�.
		QueryPerformanceFrequency(&mCpuFrequency);

		// ���α׷��� ���� ������ �������� �����´�.
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

			// ������ �̸� �� �޾ƿ���
			wchar_t strBuffer[255] = {};
			LoadString(nullptr, IDC_CLIENT, strBuffer, 255);

			wchar_t szBuffer[255] = {};
			swprintf_s(szBuffer, L"%s FPS : %f", strBuffer, fps);
			SetWindowText(Application::GetHwnd(), szBuffer);

			timeCheck = 0.0f;
		}
	}
}
