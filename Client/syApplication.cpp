#include "syApplication.h"
#include "syInput.h"
#include "syTime.h"

namespace sy
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, mResolution(POINT{})
		, mBackHdc(NULL)
		, mBackBuffer(NULL)
		, mPos(Vector2())
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hwnd, POINT Resolution)
	{
		mPos.x = 100.f;
		mPos.y = 100.f;

		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);

		// 윈도우 크기 지정
		mResolution = Resolution;

		RECT rect = { 0, 0, mResolution.x, mResolution.y };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);
		SetWindowPos(mHwnd, nullptr, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0);

		// 윈도우 해상도와 동일한 비트맵 생성
		mBackBuffer = CreateCompatibleBitmap(mHdc, mResolution.x, mResolution.y);

		// 새로 생성한 비트맵을 가리키는 DC 생성
		mBackHdc = CreateCompatibleDC(mHdc);

		// 새로 생성한 비트맵과 DC를 서로 연결
		HBITMAP defaultBitmap =
			(HBITMAP)SelectObject(mBackHdc, mBackBuffer);

		// mBackHdc 의 기본 비트맵 삭제
		DeleteObject(defaultBitmap);

		Time::Initailize();
		Input::Initailize();
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();		

		if (Input::GetKeyPressed(eKeyCode::W))
		{
			mPos.y -= 500.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::A))
		{
			mPos.x -= 500.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::S))
		{
			mPos.y += 500.0f * Time::DeltaTime();
		}
		if (Input::GetKeyPressed(eKeyCode::D))
		{
			mPos.x += 500.0f * Time::DeltaTime();
		}
	}

	void Application::Render()
	{
		Time::Render(mHdc);

		// 테두리 제거용 1증감
		Rectangle(mBackHdc, -1, -1, mResolution.x + 1, mResolution.y + 1);

		Ellipse(mBackHdc
			, int(mPos.x - 50)
			, int(mPos.y - 50)
			, int(mPos.x + 50)
			, int(mPos.y + 50.f));

		// Back 버퍼 비트맵을 front 버퍼 윈도우에 덮어씌운다
		BitBlt(mHdc, 0, 0, mResolution.x, mResolution.y,
			mBackHdc, 0, 0, SRCCOPY);
	}
}
