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
		ball.Pos.x = float(mResolution.x / 2);
		ball.Pos.y = float(mResolution.y / 2);

		// 100 ~ 500 random speed set
		ball.Speed.x = float(rand() % 400) + 100;
		ball.Speed.y = float(rand() % 400) + 100;

		ball.Scale.x = 100.f;
		ball.Scale.y = 100.f;

		// 시드 값을 설정하여 난수 생성기 초기화
		std::random_device rd;
		std::mt19937 gen(rd());

		// 균일 분포를 사용하여 0과 1 사이의 실수값 생성
		std::uniform_real_distribution<> dis(0, 1);

		// 첫 번째 bool 값 생성
		ball.DirectionX = dis(gen) < 0.5;

		// 두 번째 bool 값 생성
		ball.DirectionY = dis(gen) < 0.5;

		Balls.push_back(ball);
	}
}
