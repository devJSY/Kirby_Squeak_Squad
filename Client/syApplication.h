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
		virtual ~Application();

		static void Initialize(HWND hwnd, POINT Resolution);
		static void Run();
		static void Update();
		static void Render();

	public:
		static HWND GetHwnd() { return mHwnd; }
		static POINT GetResolution() { return mResolution; }

	private:
		static HWND mHwnd;
		static HDC mHdc;
		static POINT mResolution;
		
		static HDC mBackHdc;
		static HBITMAP mBackBuffer;
	};
}
