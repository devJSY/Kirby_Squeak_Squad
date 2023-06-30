#include "syApplication.h"
#include "syInput.h"
#include "syTime.h"

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
			mPos.y -= 300.0f * Time::DeltaTime();
		}

		if (Input::GetKeyPressed(eKeyCode::A))
		{
			mPos.x -= 300.0f * Time::DeltaTime();
		}

		if (Input::GetKeyPressed(eKeyCode::S))
		{
			mPos.y += 300.0f * Time::DeltaTime();
		}

		if (Input::GetKeyPressed(eKeyCode::D))
		{
			mPos.x += 300.0f * Time::DeltaTime();
		}
	}

	void Application::Render()
	{
		Time::Render(mHdc);

		Ellipse(mHdc
			, int(100 + mPos.x), int(100 + mPos.y)
			, int(200 + mPos.x), int(200 + mPos.y));
	}
}
