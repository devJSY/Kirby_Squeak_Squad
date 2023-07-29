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
	HMENU		Application::mhMenu	 = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT)); // �޴��� ����

	Vector2 Application::mScreenSize = Vector2::Zero;
	Vector2 Application::mScreenRenderPos = Vector2::Zero;
	float	Application::mMinScreenRatio = 0.f;

	Application::Application()
	{
	}

	void Application::Release()
	{
		// �Ŵ��� Ŭ�������� ��ü�� ������ �����ʱ� ������ �Ҹ��ڰ� ȣ��������� ���� �Լ��� ���� ���� ó���ؾ���
		// 
		// �������ڵ�, DC ����
		ReleaseDC(mHwnd, mHdc);

		DeleteDC(mBackHdc);
		DeleteObject(mBackBuffer);

		DestroyMenu(mhMenu);
	}

	void Application::Initialize(HWND hwnd, POINT Resolution)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);
		// ������ ũ�� ����
		mResolution = Resolution;

		// �ػ󵵿� �°� ������ ũ�� ����
		ChangeWindowSize(mResolution, false);

		// �޴��� ����Ʈ off
		DividMenu();

		// ������ �ػ󵵿� ������ ��Ʈ�� ����
		mBackBuffer = CreateCompatibleBitmap(mHdc, mResolution.x, mResolution.y);

		// ���� ������ ��Ʈ���� ����Ű�� DC ����
		mBackHdc = CreateCompatibleDC(mHdc);

		// ���� ������ ��Ʈ�ʰ� DC�� ���� ����
		HBITMAP defaultBitmap =
			(HBITMAP)SelectObject(mBackHdc, mBackBuffer);

		// mBackHdc �� �⺻ ��Ʈ�� ����
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
		// �׵θ� ���ſ� 1����
		Rectangle(mBackHdc, -1, -1, mResolution.x + 1, mResolution.y + 1);

		Time::Render(mBackHdc);

		CollisionManager::Render(mBackHdc);
		SceneManager::Render(mBackHdc);		
		Camera::Render(mBackHdc);

		// ȭ�� ���� ���߱�
		SetWindowRatio();

		// Back ���� ��Ʈ���� Front ���� �����쿡 ������
		BitBlt(mHdc, 0, 0, mResolution.x, mResolution.y,
			mBackHdc, 0, 0, SRCCOPY);
	}

	void Application::DockMenu()
	{
		SetMenu(mHwnd, mhMenu); // �޴��� On
		ChangeWindowSize(mResolution, true);
	}

	void Application::DividMenu()
	{
		SetMenu(mHwnd, nullptr); // �޴��� Off
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
		// ���� ������ ����� �����´� 
		RECT rect;
		GetClientRect(mHwnd, &rect);

		// float ��������� Vector2�� ��ȯ
		Vector2 rectVec;
		rectVec.x = (float)rect.right;
		rectVec.y = (float)rect.bottom;

		// ���� �ػ󵵿� ���� �ػ��� ������
		float Xratio = rectVec.x / mResolution.x;
		float Yratio = rectVec.y / mResolution.y; 
					
		// MM_ISOTROPIC ����̹Ƿ� ���������� �þ�⶧���� ���� ������������ ȭ��ũ�Ⱑ ������
		if (Xratio < Yratio)
			mMinScreenRatio = Xratio;
		else 
			mMinScreenRatio = Yratio;
		
		// ������ ������ ���� 1920, 1080 ���� 720, 1080 ������� ������
		mScreenSize.x = mResolution.x * mMinScreenRatio;
		mScreenSize.y = mResolution.y * mMinScreenRatio;
		
		mScreenRenderPos.x = (rectVec.x / 2.f) - (mScreenSize.x / 2.f);
		mScreenRenderPos.y = 0.f;

		SetMapMode(mHdc, MM_ISOTROPIC); // MM_ISOTROPIC ���� �׸��� ������ ���� ��� ��ȭ�� ���� ���������(���μ��� ����)
		// ������ �����ǥ�� ����Ʈ�� ��ȯ�ϴ� ��� ����

		SetViewportOrgEx(mHdc, (int)mScreenRenderPos.x, (int)mScreenRenderPos.y, NULL); // ����Ʈ�� ��������
		SetWindowExtEx(mHdc, mResolution.x, mResolution.y, NULL); // ���� ��ǥ ����
		SetViewportExtEx(mHdc, rect.right, rect.bottom, NULL);  // ����Ʈ ũ�� ����
	}
}
