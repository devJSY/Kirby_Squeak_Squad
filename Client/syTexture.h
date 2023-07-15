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

		static Texture* Create(const std::wstring& name, UINT width, UINT height);

		virtual HRESULT Load(const std::wstring& path) override;

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
		eTextureType mType;		// Ȯ���� Ÿ��
		Gdiplus::Image* mImage;	// png ��ü

		HBITMAP mBitmap;	// ���ҽ� ��Ʈ��
		HDC mHdc;			// ���ҽ� ��Ʈ���� dc
		UINT mWidth;		// ���ҽ� ����
		UINT mHeight;		// ���ҽ� ����
	};
}
