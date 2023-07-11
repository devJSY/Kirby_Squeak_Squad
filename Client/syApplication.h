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

		static HWND GetHwnd() { return mHwnd; }
		static HDC GetHdc() { return mHdc; }
		static POINT GetResolution() { return mResolution; }

	public:
		static void DockMenu();
		static void DividMenu();
		static void ChangeWindowSize(POINT Resolution, bool bMenu);

	private:
		static HWND mHwnd;
		static HDC mHdc;
		static POINT mResolution;
		
		static HDC mBackHdc;
		static HBITMAP mBackBuffer;

		static HMENU	m_hMenu;
	};
}
