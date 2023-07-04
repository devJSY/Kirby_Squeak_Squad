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

		// �׵θ� ���ſ� 1����
		Rectangle(mBackHdc, -1, -1, mResolution.x + 1, mResolution.y + 1);

		Ellipse(mBackHdc
			, int(mPos.x - 50)
			, int(mPos.y - 50)
			, int(mPos.x + 50)
			, int(mPos.y + 50.f));

		// Back ���� ��Ʈ���� front ���� �����쿡 ������
		BitBlt(mHdc, 0, 0, mResolution.x, mResolution.y,
			mBackHdc, 0, 0, SRCCOPY);
	}
}
