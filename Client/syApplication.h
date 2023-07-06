#pragma once
#include "CommonInclude.h"
#include "syScene.h"

namespace sy
{
	using namespace math;

	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd, POINT Resolution);
		void Run();
		void Update();
		void Render();

	private:
		HWND mHwnd;
		HDC mHdc;
		POINT mResolution;
		
		HDC mBackHdc;
		HBITMAP mBackBuffer;
	};
}
