#pragma once
#include "syResource.h"

namespace sy
{
	using namespace enums;
	using namespace math;
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		static Texture* Create(const std::wstring& name, UINT width, UINT height);

		virtual HRESULT Load(const std::wstring& path) override;

		void Render(HDC hdc
			, Vector2 pos
			, Vector2 size
			, Vector2 LeftTop
			, Vector2 RightBottom
			, bool AffectedCamera
			, Vector2 scale = Vector2::One
			, float Alpha = 1.0f
			, COLORREF rgb = RGB(255,0,255)
			, float rotate = 0.0f);

		UINT GetWidth() { return mWidth; }
		void SetWidth(UINT width) { mWidth = width; }
		UINT GetHeight() { return mHeight; }
		void SetHeight(UINT height) { mHeight = height; }

		HDC GetHdc() { return mHdc; }
		eTextureType GetType() { return mType; }
		void SetType(eTextureType type) { mType = type; }
		Gdiplus::Image* GetImage() { return mImage; }
		void SetHBitmap(HBITMAP bitmap) { mBitmap = bitmap; }
		HBITMAP GetBitmap() { return mBitmap; }
		void SetHdc(HDC hdc) { mHdc = hdc; }

	private:
		eTextureType mType;		// 확장자 타입
		Gdiplus::Image* mImage;	// png 객체

		HBITMAP mBitmap;	 // 리소스 비트맵
		HDC mHdc;			 // 리소스 비트맵의 dc
		UINT mWidth;		 // 리소스 가로
		UINT mHeight;		 // 리소스 세로
	};
}
