#include "syApplication.h"
#include "syInput.h"

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

		Input::Initailize();
	}

	void Application::Run()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		Input::Update();

		if (Input::GetKeyPressed(eKeyCode::W))
		{
			mPos.y -= 0.01f;
		}

		if (Input::GetKeyPressed(eKeyCode::A))
		{
			mPos.x -= 0.01f;
		}

		if (Input::GetKeyPressed(eKeyCode::S))
		{
			mPos.y += 0.01f;
		}

		if (Input::GetKeyPressed(eKeyCode::D))
		{
			mPos.x += 0.01f;
		}
	}

	void Application::Render()
	{
		Ellipse(mHdc
			, int(100 + mPos.x), int(100 + mPos.y)
			, int(200 + mPos.x), int(200 + mPos.y));
	}
}
