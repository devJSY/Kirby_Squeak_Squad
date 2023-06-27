#pragma once
#include "CommonInclude.h"

namespace sy
{
	using namespace math;

	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd);
		void Run();
		void Update();
		void Render();

	private:
		HWND mHwnd;
		HDC mHdc;

		math::Vector2 mPos;
	};

}
