#pragma once
#include "syResource.h"

namespace sy
{
	using namespace enums;
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& path) override;

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() { return mHdc; }
		eTextureType GetType() { return mType; }
		Gdiplus::Image* GetImage() { return mImage; }

	private:
		eTextureType mType;	// 확장자 타입
		Gdiplus::Image* mImage;		// png 객체

		HBITMAP mBitmap;	// 리소스 비트맵
		HDC mHdc;			// 리소스 비트맵의 dc
		UINT mWidth;		// 리소스 가로
		UINT mHeight;		// 리소스 세로
	};
}
