#include "syImage.h"
#include "syApplication.h"

namespace sy
{
	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{
	}

	Image::~Image()
	{
	}

	HRESULT Image::Load(const std::wstring& path)
	{
		// 인자로 들어온 경로로 부터 이미지파일을 Load 한다
		mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0
			, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (mBitmap == nullptr)
			return E_FAIL;

		// 받아온 mBitmap의 정보를 info 에 저장
		BITMAP info = {};
		GetObject(mBitmap, sizeof(BITMAP), &info);

		mWidth = info.bmWidth;
		mHeight = info.bmHeight;
		
		HDC mainDC = Application::GetHdc();
		mHdc = CreateCompatibleDC(mainDC); // mainDC로부터 새로운 DC생성하여 멤버변수로 저장

		// 비트맵과 DC를 연결
		HBITMAP deafultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(deafultBitmap);

		return S_OK;
	}
}