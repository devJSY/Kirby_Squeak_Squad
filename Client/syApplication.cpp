#include "syApplication.h"
#include "syInput.h"
#include "syTime.h"
#include "sySceneManager.h"
#include "resource.h"	// LoadMenu()

namespace sy
{
	HWND		Application::mHwnd		 = NULL;
	HDC			Application::mHdc		 = NULL;
	POINT		Application::mResolution = POINT{};

	HDC			Application::mBackHdc	 = NULL;
	HBITMAP		Application::mBackBuffer = NULL;
	HMENU		Application::m_hMenu	 = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT)); // 메뉴바 생성

	Application::Application()
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

		// 해상도에 맞게 윈도우 크기 조정
		ChangeWindowSize(mResolution, false);

		// 메뉴바 디폴트 off
		DividMenu();

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
		SceneManager::Initialize();		
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
		SceneManager::Update();
	}

	void Application::Render()
	{
		// 테두리 제거용 1증감
		Rectangle(mBackHdc, -1, -1, mResolution.x + 1, mResolution.y + 1);

		//Time::Render(mBackHdc);
		SceneManager::Render(mBackHdc);		


		// 화면 비율 맞추기
		RECT rect;
		SetMapMode(mHdc, MM_ISOTROPIC); // MM_ISOTROPIC 원본 그림이 비율에 따다 모양 변화가 없이 사용자정의(가로세로 동일)

		GetClientRect(mHwnd, &rect);
		SetViewportOrgEx(mHdc, rect.right / 2 - ((rect.bottom / mResolution.y * mResolution.x) / 2), 0, NULL);
		SetWindowExtEx(mHdc, mResolution.x, mResolution.y, NULL);
		SetViewportExtEx(mHdc, rect.right, rect.bottom, NULL);


		// Back 버퍼 비트맵을 Front 버퍼 윈도우에 덮어씌운다
		BitBlt(mHdc, 0, 0, mResolution.x, mResolution.y,
			mBackHdc, 0, 0, SRCCOPY);
	}

	void Application::DockMenu()
	{
		SetMenu(mHwnd, m_hMenu); // 메뉴바 On
		ChangeWindowSize(mResolution, true);
	}

	void Application::DividMenu()
	{
		SetMenu(mHwnd, nullptr); // 메뉴바 Off
		ChangeWindowSize(mResolution, false);
	}

	void Application::ChangeWindowSize(POINT Resolution, bool bMenu)
	{
		RECT rect = { 0, 0, Resolution.x, Resolution.y};
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, bMenu);
		SetWindowPos(mHwnd, nullptr, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0);
	}
}
