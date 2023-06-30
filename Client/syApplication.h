#pragma once
#include "CommonInclude.h"

namespace sy
{
	using namespace math;

	class Application
	{
		struct Ball
		{
			Vector2 Pos;
			Vector2 Scale;
			Vector2 Speed;
			bool DirectionX;
			bool DirectionY;
		};

	public:
		Application();
		~Application();

		void Initialize(HWND hwnd, POINT Resolution);
		void Run();
		void Update();
		void Render();

		void BallsMove();
		void BallsDirectionCheck();
		void CreateBall();

	private:
		HWND mHwnd;
		HDC mHdc;

		POINT mResolution;
		static std::vector<Ball> Balls;
	};
}
