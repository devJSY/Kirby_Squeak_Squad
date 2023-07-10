#pragma once
#include "syResource.h"

namespace sy
{
	class Image : public Resource
	{
	public:
		Image();
		virtual ~Image();

		virtual HRESULT Load(const std::wstring& path) override;

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() { return mHdc; }

	private:
		HBITMAP mBitmap;	// 리소스 비트맵
		HDC mHdc;			// 리소스 비트맵의 dc
		UINT mWidth;		// 리소스 가로
		UINT mHeight;		// 리소스 세로
	};
}
