#include "syApplication.h"
#include "syInput.h"
#include "syTime.h"

namespace sy
{
	std::vector<Application::Ball> Application::Balls = {};

	Application::Application()
		: mHwnd(NULL)
		, mHdc(NULL)
		, mResolution(POINT{})
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

		Time::Initailize();
		Input::Initailize();

		// 랜덤함수 초기화
		srand(unsigned(time(NULL)));

		CreateBall();
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

		static float fTime = 0.0f;
		fTime += Time::DeltaTime();

		// 2초에 한번씩 생성
		if (fTime >= 2.f)
		{
			CreateBall();
			fTime = 0.0f;
		}

		BallsDirectionCheck();
		BallsMove();
	}

	void Application::Render()
	{
		Time::Render(mHdc);

		for (int i = 0; i < Balls.size(); i++)
		{
			Ellipse(mHdc,
				  int(Balls[i].Pos.x - Balls[i].Scale.x / 2)
				, int(Balls[i].Pos.y - Balls[i].Scale.y / 2)
				, int(Balls[i].Pos.x + Balls[i].Scale.x / 2)
				, int(Balls[i].Pos.y + Balls[i].Scale.y / 2));
		}
	}

	void Application::BallsMove()
	{
		// Balls 이동
		for (int i = 0; i < Balls.size(); i++)
		{
			if (Balls[i].DirectionX)
				Balls[i].Pos.x += Balls[i].Speed.x * Time::DeltaTime();
			else
				Balls[i].Pos.x -= Balls[i].Speed.x * Time::DeltaTime();

			if (Balls[i].DirectionY)
				Balls[i].Pos.y += Balls[i].Speed.y * Time::DeltaTime();
			else
				Balls[i].Pos.y -= Balls[i].Speed.y * Time::DeltaTime();
		}
	}

	void Application::BallsDirectionCheck()
	{
		// Balls 방향 체크
		for (int i = 0; i < Balls.size(); i++)
		{
			// 좌측 X
			if (Balls[i].Pos.x - (Balls[i].Scale.x / 2) <= 0)
			{
				Balls[i].DirectionX = true;
			}

			// 우측 X
			if (Balls[i].Pos.x + (Balls[i].Scale.x / 2) >= mResolution.x)
			{
				Balls[i].DirectionX = false;
			}

			// 상단 Y
			if (Balls[i].Pos.y - (Balls[i].Scale.y / 2) <= 0)
			{
				Balls[i].DirectionY = true;
			}

			// 하단 Y
			if (Balls[i].Pos.y + (Balls[i].Scale.y / 2) >= mResolution.y)
			{
				Balls[i].DirectionY = false;
			}
		}
	}

	void Application::CreateBall()
	{
		Ball ball = {};

		// ball 크기 설정
		ball.Scale.x = 100.f;
		ball.Scale.y = 100.f;

		// mResolution 범위 내의 랜덤위치 생성
		ball.Pos.x = float(rand() % int(mResolution.x - ball.Scale.x) + int(ball.Scale.x / 2));
		ball.Pos.y = float(rand() % int(mResolution.y - ball.Scale.y) + int(ball.Scale.y / 2));

		ball.Speed.x = 300;
		ball.Speed.y = 300;

		//// 100 ~ 500 random speed set
		//ball.Speed.x = float(rand() % 400) + 100;
		//ball.Speed.y = float(rand() % 400) + 100;

		// 랜덤 방향 설정
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0, 1);
		ball.DirectionX = dis(gen) < 0.5;
		ball.DirectionY = dis(gen) < 0.5;

		Balls.push_back(ball);
	}
}
