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

		static Texture* Create(const std::wstring& name, UINT width, UINT height, COLORREF rgb = RGB(255, 255, 255));

		virtual HRESULT Load(const std::wstring& path) override;

		void Render(HDC hdc
			, Vector2 pos
			, Vector2 size
			, Vector2 TexLeftTop
			, Vector2 TexSize
			, bool AffectedCamera
			, Vector2 CameraSpeedRatio
			, float Alpha = 1.0f
			, COLORREF rgb = RGB(255,0,255)
			, float rotate = 0.0f
			, bool blink = false);

		UINT GetWidth() const { return mWidth; }
		void SetWidth(UINT width) { mWidth = width; }
		UINT GetHeight() const { return mHeight; }
		void SetHeight(UINT height) { mHeight = height; }

		eTextureType GetType() const { return mType; }
		void SetType(eTextureType type) { mType = type; }

		HDC GetHdc() const { return mHdc; }
		Gdiplus::Image* GetImage() const { return mImage; }
		void SetHBitmap(HBITMAP bitmap) { mBitmap = bitmap; }
		HBITMAP GetBitmap() const  { return mBitmap; }
		void SetHdc(HDC hdc) { mHdc = hdc; }

		COLORREF GetTexturePixel(int x, int y) const { return GetPixel(mHdc, x, y); }

		void SetScale(Vector2 scale) { mScale = scale; }

	private:
		eTextureType mType;				// 확장자 타입
		Gdiplus::Image* mImage;			// png 객체
		Gdiplus::Bitmap* m_pBitGdi;		// GDI 용 비트맵

		HBITMAP mBitmap;	 // 리소스 비트맵
		HDC mHdc;			 // 리소스 비트맵의 dc
		UINT mWidth;		 // 리소스 가로
		UINT mHeight;		 // 리소스 세로

		Vector2 mScale;
		float mblinkTime;
		float mblinkAlpha;

	};
}
