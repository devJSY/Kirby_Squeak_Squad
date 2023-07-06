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

		// ������ ũ�� ����
		mResolution = Resolution;

		RECT rect = { 0, 0, mResolution.x, mResolution.y };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, true);
		SetWindowPos(mHwnd, nullptr, 100, 100, rect.right - rect.left, rect.bottom - rect.top, 0);

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
		// �׵θ� ���ſ� 1����
		Rectangle(mBackHdc, -1, -1, mResolution.x + 1, mResolution.y + 1);

		Time::Render(mBackHdc);

		mScene->Render(mBackHdc);

		// Back ���� ��Ʈ���� Front ���� �����쿡 ������
		BitBlt(mHdc, 0, 0, mResolution.x, mResolution.y,
			mBackHdc, 0, 0, SRCCOPY);
	}
}
