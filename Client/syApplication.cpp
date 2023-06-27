#include "syApplication.h"

namespace sy
{
	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, mPos(Vector2())
	{
	}

	Application::~Application()
	{
	}

	void Application::Initialize(HWND hwnd)
	{
		mHwnd = hwnd;
		mHdc = GetDC(mHwnd);
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			mPos.x -= 0.01f;
		}

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			mPos.x += 0.01f;
		}

		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			mPos.y -= 0.01f;
		}

		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			mPos.y += 0.01f;
		}
	}

	void Application::Render()
	{
		Ellipse(mHdc
			, int(100 + mPos.x), int(100 + mPos.y)
			, int(200 + mPos.x), int(200 + mPos.y));
	}
}
