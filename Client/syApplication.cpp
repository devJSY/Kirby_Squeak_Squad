#include "syApplication.h"
#include "syInput.h"
#include "syTime.h"
#include "sySceneManager.h"
#include "resource.h"	// LoadMenu()
#include "syCamera.h"
#include "syCollisionManager.h"
#include "sySoundManager.h"

namespace sy
{
	HWND		Application::mHwnd		 = NULL;
	HDC			Application::mHdc		 = NULL;
	POINT		Application::mResolution = POINT{};

	HDC			Application::mBackHdc	 = NULL;
	HBITMAP		Application::mBackBuffer = NULL;
	HMENU		Application::mhMenu	 = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT)); // 메뉴바 생성

	Vector2 Application::mScreenSize = Vector2::Zero;
	Vector2 Application::mScreenRenderPos = Vector2::Zero;
	float	Application::mMinScreenRatio = 0.f;

	Application::Application()
	{
	}

	void Application::Release()
	{
		// 매니저 클래스들은 객체가 생성이 되지않기 때문에 소멸자가 호출되지않음 해제 함수를 따로 만들어서 처리해야함
		// 
		// 윈도우핸들, DC 삭제
		ReleaseDC(mHwnd, mHdc);

		DeleteDC(mBackHdc);
		DeleteObject(mBackBuffer);

		DestroyMenu(mhMenu);
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
		SoundManager::Initialize();
		Camera::Initalize();

		CollisionManager::Initialize();
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
		Camera::Update();

		CollisionManager::Update();
		SceneManager::Update();
	}

	void Application::Render()
	{
		// 테두리 제거용 1증감
		Rectangle(mBackHdc, -1, -1, mResolution.x + 1, mResolution.y + 1);

		Time::Render(mBackHdc);

		CollisionManager::Render(mBackHdc);
		SceneManager::Render(mBackHdc);		
		Camera::Render(mBackHdc);

		// 화면 비율 맞추기
		SetWindowRatio();

		// Back 버퍼 비트맵을 Front 버퍼 윈도우에 덮어씌운다
		BitBlt(mHdc, 0, 0, mResolution.x, mResolution.y,
			mBackHdc, 0, 0, SRCCOPY);
	}

	void Application::DockMenu()
	{
		SetMenu(mHwnd, mhMenu); // 메뉴바 On
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

	void Application::SetWindowRatio()
	{		
		// 현재 윈도우 사이즈를 가져온다 
		RECT rect;
		GetClientRect(mHwnd, &rect);

		// float 계산을위해 Vector2로 변환
		Vector2 rectVec;
		rectVec.x = (float)rect.right;
		rectVec.y = (float)rect.bottom;

		// 원본 해상도와 현재 해상도의 비율값
		float Xratio = rectVec.x / mResolution.x;
		float Yratio = rectVec.y / mResolution.y; 
					
		// MM_ISOTROPIC 모드이므로 같은비율로 늘어나기때문에 작은 비율기준으로 화면크기가 결정됨
		if (Xratio < Yratio)
			mMinScreenRatio = Xratio;
		else 
			mMinScreenRatio = Yratio;
		
		// 동일한 비율로 증가 1920, 1080 기준 720, 1080 사이즈로 렌더링
		mScreenSize.x = mResolution.x * mMinScreenRatio;
		mScreenSize.y = mResolution.y * mMinScreenRatio;
		
		mScreenRenderPos.x = (rectVec.x / 2.f) - (mScreenSize.x / 2.f);
		mScreenRenderPos.y = 0.f;

		SetMapMode(mHdc, MM_ISOTROPIC); // MM_ISOTROPIC 원본 그림이 비율에 따다 모양 변화가 없이 사용자정의(가로세로 동일)
		// 논리적인 출력좌표를 뷰포트로 변환하는 방식 설정

		SetViewportOrgEx(mHdc, (int)mScreenRenderPos.x, (int)mScreenRenderPos.y, NULL); // 뷰포트의 원점설정
		SetWindowExtEx(mHdc, mResolution.x, mResolution.y, NULL); // 논리적 좌표 설정
		SetViewportExtEx(mHdc, rect.right, rect.bottom, NULL);  // 뷰포트 크기 설정
	}
}
