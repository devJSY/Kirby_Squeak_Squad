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
		, mScene(nullptr)
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hwnd, POINT Resolution)
	{
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

		Time::Initialize();
		Input::Initialize();

		mScene = new Scene();
		mScene->Initialize();
		std::wstring str = L"Test Scene";
		mScene->SetName(str);
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
		mScene->Update();
	}

	void Application::Render()
	{
		// 테두리 제거용 1증감
		Rectangle(mBackHdc, -1, -1, mResolution.x + 1, mResolution.y + 1);

		Time::Render(mBackHdc);

		mScene->Render(mBackHdc);

		// Back 버퍼 비트맵을 Front 버퍼 윈도우에 덮어씌운다
		BitBlt(mHdc, 0, 0, mResolution.x, mResolution.y,
			mBackHdc, 0, 0, SRCCOPY);
	}
}
